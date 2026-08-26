public class DoublyCircular{
    static class Node {
        int data;
        Node next;
        Node Prev;

        Node(int data){
            this.data = data;
            this.next = null;
            this.prev = null;
        }
    }

    public static void main(String args[]){
        Node node1 = new Node(3);
        Node node2 = new Node(5);
        Node node3 = new Node(13);
        Node node4 = new Node(2);

        node1.next = node2;
        node1.prev = node4;

        node2.next = node3;
        node2.prev = node1;

        node3.next = node4;
        node3.prev = node2;

        node4.next = node1;
        node4.prev = node3;

        currentNode = node1;
        startingNode = node1;
        System.out.println("\nTraversing forward:");
        System.out.print(currentNode.data + " -> ");
        currentNode = currentNode.next;

        while (currentNode != startingNode){
            System.out.print(currentNode.data + " -> ");
            currentNode = currentNode.next;
        }

        System.out.println("..."); // List loops back

        System.out.println("\nTraversing backward:");
        currentNode = node4;
        startingNode = node4;
        System.out.print(currentNode.prev + " -> ");
        currentNode = currentNode.prev;

        while (currentNode != startingNode){
            System.out.print(currentNode.data + " -> ");
            currentNode = currentNode.prev;
        }
        System.out.println("...");
    }
}