public class Node extends Vec {
    protected Node left;
    protected Node right;

    /**
     * Default constructor
     */
    public Node() {
        this.left = null;
        this.right = null;
    }

    /**
     * Parameterized constructor. Takes a Job object & calls parent
     * @param inJob
     */
    public Node (Job inJob) {
        super(inJob);
        this.left = null;
        this.right = null;
    }

    /**
     * Wrapper function calls parent to display contents of each element
     * @param i this is the element called from various locations
     * @return simply calls it's parent's display function
     */
    public int DisplayNode(int i) {
        return super.DisplayNode(i);
    }
}
