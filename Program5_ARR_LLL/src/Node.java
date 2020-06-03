/**
 * Will McIntosh, 5-21-22, program 4
 * This class works on all things pertaining to the node
 * that is inside of the binary search tree.
 */
public class Node extends Vec {
    protected Node next;

    /**
     * Default constructor
     */
    public Node() {
        this.next = null;
    }

    /**
     * Parameterized constructor. Takes a Job object & calls parent
     * @param inJob
     */
    public Node (Job inJob) {
        super(inJob);
        this.next = null;
    }

    /**
     * Wrapper function calls parent to display contents of each element
     * @return simply calls it's parent's display function
     */
    public int DisplayNode() {
        return super.DisplayNode();
    }
}
