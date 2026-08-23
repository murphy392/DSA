import os
import sys
import time
import csv
import json
import subprocess
from datetime import datetime
from scapy.all import * # packet capture and wireless frames
from scapy.layers.dot11 import * # for 802.11 (wi-fi) layer
from tabulate import tabulate    # for beautiful table output

# Project Folders
DATA_DIR = "data"
LOGS_DIR = "logs"
REPORTS_DIR = "reports"
os.makedirs(DATA_DIR, exist_ok = True)
os.makedirs(LOGS_DIR, exist_ok = True)
os.makedirs(REPORTS_DIR, exist_ok = True)

# Config
DEFAULT_INTERFACE = None # Use monitor mode interface
SCAN_TIMEOUT = 10 # seconds to scan networks
LOG_FILE = os.path.join(LOGS_DIR, "wifi_tool.log")
RESULTS_FILE = os.path.join(REPORTS_DIR, "networks.csv")

# Tool information
TOOL_NAME = "WIFI SECURITY ASSESSMENT TOOL"
TOOL_VERSION = "1.0"
AUTHOR = "CRAIG MURPHY" 
DESCRIPTION = "Discover nearby Wi-Fi networks and analyze security details"

# Main Menu
def main_menu():
    os.system("cls" if os.name == "nt" else "clear")
    print("=" * 60)
    print(f" {TOOL_NAME} v{TOOL_VERSION} ")
    print("=" * 60)
    print("1. List Wireless Interfaces")
    print("2. Scan Wi-Fi Networks")
    print("3. Analyze Selected Network")
    print("4. Export Results (csv)")
    print("5. View Saved Results")
    print("6. Exit")
    print("-" * 60)

#NOTE:
# EDUCATIONAL USES ONLY

# ----------- 2. WI-FI NETWORK DISCOVERY & INFO ---------------- 

# Function: Get Wi-Fi Interfaces

def get_wifi_interfaces():                          # List all network interfaces
    interfaces = []
    for iface in os.listdir("/sys/class/net"):      #Linux only? This should work for all systems in my opinion. How can I fix it? 
        if iface != "lo":                           # Skip loop back interface
            interfaces.append(iface)
    return interfaces                               # Return all interfaces 

# Function Scan Wi-Fi Networks
def scan_wifi(interface, timeout = 5): # Scan for nearby Wi-Fi networks
    networks = []
    print(f"[*] Scanning on {interface} ... Please wait {timeout} s")
    os.system(f"iwlist {interface} scan | tee scan_output.txt") # perform scan * save output
    time.sleep(timeout)
    with open("scan_output.txt", "r", errors="ignore") as f:
        data = f.read().split("Cell ")
        for cell in data:
            if "ESSID: " in cell:
                network = parse_network_info(call)              # Parse details from each block
                if network: 
                    networks.append(network)
    return networks

# Function: Parse Network Information
def parse_network_info(cell): # Extract useful info from scan block
    network = {}
    network["BSSID"] = re.search(r"Address: \s*([0-9A-Fa-f:]{17})", cell)
    network["SSID"] = re.search(r"ESSID:'(.*)'", cell)
    network["Channel"] = re.search(r"Channel:(\d+)", cell)
    network["Frequencey"] = re.search(r"Frequencey: ([\d\.]+)\s*GHz", cell)
    network["Quality"] = re.search(r"Quality: (\d+)/(\d+)", cell)
    network["Encryption"] = detect_encryption(cell)
    network["Signal"] = calculate_singal(network["Quality"])
    return network;

# Function: Detect Encryption Type
def detect_encryption(cell): # Detect encyption / security type
    if "WPA3" in cell: return "WPA3"
    elif "WPA2" in cell: return "WPA2"
    elif "WPA" in cell: return "WPA"
    elif "Privacy" in cell: return "WEP"
    else: return "OPEN"

#Function: Calculate Signal Strength 
def calculate_singal(quality): # convert quality value to percentage
    try:
        q, max_q = map(int, quality.groups())
        return int ((q / max_q) * 100)
    except:
        return 0

#NOTE:
# THIS MODULE DISCOVERS NEARBY WI-FI NETWORKS USING SYSTEM TOOLS
# WORKS ON LINUX-BASED SYSTEMS WITH "iwlist" OR "iw" SUPPORT
# RESULTS INCLUDE SSID, BSSID, CHANNEL, SIGNAL AND ENCRYPTION

# -------------------------- 3. Analyze Signal, Channel, & Manage Results --------------------
#Function: Analyze Signal Strength
def analyze_signal(networks):
    # count dBM signal to quality ( 0 - 100%) 
    for net in networks:
        try: 
            signal_dbm = int(net.get("Signal(", - 100).replace("dBM","").strip())
            quality = max(0, min (100, 2 * (signal_dbm + 100)))
            net["Quality(%)"] = quality
        except:
            net["Quality(%)"]= 0 

#Function: Channel Analysis 
def analyze_channels(networks): #Count networks per channel
    channel_count = {}
    for net in networks:
        ch = net.get("Channel", "N/A")
        channel_count[ch] = channel_count.get(ch, 0) + 1
    return channel_count

#Function: Filter Networks
def filter_networks(networks, security=None, ssid=None, min_quality = 0): #Filter by security, SSID, or min quality
    filtered = []
    for net in networks:
        if security and net.get("Encryption", "") != security:
            continue
        if ssid and ssid.lower() not in net.get("ESSID", "").lower():
            continue
        if int(net.get("Quailty(%)", 0)) < min_quality:
            continue
        return filtered

#Function: Save results to CSV
def save_to_csv(networks, filename = "wifi_results.csv"): # Save networks to CSV file
    if not networks:
        print("[!] No data to save")
        return
    
    fileds = ["ESSID", "BSSID", "Channel", "Encryption", "Signal", "Quality(%)"]
    with open(filename, "w", newline="") as f:
        writer = csv.DictWriter(f, fieldnames = fields)
        writer.writeheader()
        for net in networks:
            writer.writerow({field: net.get(field, "") for field in fields})
    print(f"[+] Results saved to {filename}")

#Fucntion: Display results table
def display_results(networks): #Show networks in clean table
    if not networks:
        print("[!] No networks found to display")
        return

    headers = ["#", "ESSID", "BSSID", "Channel", "Encryption", "Signal", "Quality(%)"]
    print("-" * 100)
    print(f"{headers[0]: <3} {headers[1]:<25} {headers[2]:<20} {headers[3]:<12} {headers[4]:<12} {headers[5]:<8} {headers[6]:<10}")
    print("-" * 100)
    for i, net in enumerate(networks, 1):
        print(f"{1:<3} {net.get("ESSID",""):<25} {net.get("BSSID", ""):<20} {net.get("Channel", ""):<4} {net.get("Encryption", ""):<12} {net.get("Signal",""):<8} {net.get("Quality(%)", ""):<10}")

#NOTE:
# THIS HANDLES SIGNAL QUALITY, CHANNEL ANALYSIS, FILTERING & RESULTS
# RESULTS CAN BE VIEWED IN TABLE FORMATE OR SAVED TO CSV FOR REPORTS
# HELPS IN IDENTIFYING HIGH/LOW SIGNAL NETOWRKS & CROWDED NETWORKS

# ---------------------- 4. SECURITY ASSESSMENT & REPORT GENERATION -----------------

# Function: Assess Security Level
def assess_security(network): # Determine security level based on encryption
    enc = network.get("Encryption", "").upper()
    if "WPA3" in enc:
        return "SECURE (WPA3)"
    elif "WPA2" in enc:
        return "MODERATE (WPA2)"
    elif "WEP" in enc:
        return "WEAK (WEP)"
    elif enc == "OPEN" or enc == "OPEN":
        return "UNSECURED (OPEN)"
    else:
        return "UNKNOWN"

#Function: Generate Report Table
def generate_report(networks):
    report = []
    report.append([
        "No", "ESSID", "BSSID", "Channel", "Signal(%)", "Encryption", "Security Level"
    ])

    for i, net in enumerate(networks, 1):
        level = access_security(net)
        report.append([
            net.get("ESSID",""),
            net.get("BSSID", ""),
            net.get("Channel", ""),
            net.get("Quality(%)", ""),
            net.get("Encryption", ""),
            level
        ])

    return report

# Function: Print Report Table
def print_report(report):
    try:
        from tabulate import tabulate
    except ImportError:
        print("[!] tabulate module not found. Install it using: pip intall tabulate")
        return
    
    print("\n========= WIFI SECURITY ASSESSMENT REPORT =============\n ")
    print(tabulate(report, headers="firstrow", tablefmt="grid"))

# Function: Save report to file
def save_report(report, filename="wifi_report.csv"):
    with open(filename, "w", newline=""):
        writer = csv.write(f)
        for row in report:
            writer.writerow(row)

    print(f"[+] Report saved to {filename}")

#NOTE:
# this module assesses the security of discovered wifi networks
# it identifies encryption type and classifies security level
# report is shown in a clean table and can be saved as csv
# useful for quick evaluation in authorized security assessments. 


# --------------------- EXPORT, WORKFLOW, USAGE & NOTES ---------------------

# Function: Export Results to CSV
def export_to_csv(networks, filename="wifi_results.csv"): # Export all results to csv file
    if not networks:
        print("[-] No data to report")
        return
    fields = ["ESSID", "BSSID", "Channel", "Encryption", "Signal(dBm)", "Quality(%)", "Security Level"]
    with open(filename, "w", newline=""):
        writer = csv.DictWriter(f, fieldnames=fields)
        writer.writeheader()
        for row in networks:
            writer.writerow(row)
    print(f"[+] Data exported to {filename}")

# Function: Export results to JSON
def export_to_json(networks, filename="wifi_results.json"): 
    import json
    if not networks:
        print("[-] No data to report")
        return
    with open(filename, "w") as f:
        json.dump(networks, f, indent=4)
    print(f"[+] Data exported to {filename}")

# Main function
def main():
    interfaces = get_wifi_interfaces()
    if not interfaces:
        print("[-] No Wi-Fi interfces found. Enabled monitor mode and try again")
        return
    networks = scan_wifi(interfaces[0], timout=10)
    analyzed = analyze_signal(networks)
    results = security_assessment(analyzed)
    choice = input("\n Export Results? (y/n): ").strip().lower()
    if choice == "y":
        fmt = input("Export format (csv/json): ").strip().lower()
        if fmt == "csv":
            export_to_csv(results)
        elif fmt == "json":
            export_to_json(results)
    
    print("\n[+] Scan completed. Stay secure!")

if __name__ == "__main__":
    main()