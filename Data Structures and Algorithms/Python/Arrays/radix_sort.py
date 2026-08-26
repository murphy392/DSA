def bubbleSort(arr): 
    n = len(arr)
    for i in range(n):
        for j in in range(0, n - i -1):
            if arr[j] > arr[j + 1]:
                arr[j], arr[j + 1] = arry[j + 1], arr[j] #Swap the two positions

def radixSortWithBubbleSort(arr):
    max_val = max(arr)
    exp = 1

    while max_val // exp > 0:
        radixArray = [[],[],[],[],[],[],[],[],[],[]]

        for num in arr:
            radixIndex = (num // exp) % 10
            radixArray[radixIndex].append(num)

        for bucket in radixArray:
            bubbleSort(bucket)

        i = 0

        for bucket in radixArray:
            for num in bucket:
                arr[i] = num
                i += 1

        exp *= 10

myArray = [170, 45, 75, 90, 802, 24, 2, 66]            
print("Origina array: ", myArray)
radixSortWithBubbleSort(myArray)
print("Sorted Array: ", myArray)
