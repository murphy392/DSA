public class LinkedLiest{
    static class Node {
        int data;
        Node next;

        node (int data) {
            this.data = data;
            this.next = null;
        }
    }

    public static void main(String[] args) {
        // creating individual nodes
        Node firstNode = new Node(3);
        Node secondNode = new Node(5);
        Node thirdNode = new Node(13);
        Node fourthNode = new Node(2);

        // linking nodes together
        firstNode.next = secondNode;
        secondNode.next = thirdNode;
        thirdNode = fourthNode;

        //Printing linked list
        Node currentNode = firstNode;
        while (currentNode != null) {
            System.out.print(currentNode.data + " -> ");
            currentNode = currentNode.next;
        }
        System.out.println("null");
    }
}