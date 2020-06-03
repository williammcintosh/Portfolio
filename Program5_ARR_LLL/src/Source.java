/**
 * Will McIntosh, 5-21-20, program 4
 * This class as the source member which is a string which stores where the listing came from
 * It also has a priority which the user can choose to display
 */
public class Source extends Name {
    protected String a_source;
    protected int priority;

    /**
     * Default Constructor
     */
    protected Source() {
        super();
        this.a_source = new String(); }

    /**
     * Copy Constructor
     * @param inSource
     */
    public Source(Source inSource) {
        super(inSource);
        this.a_source = inSource.a_source;
        this.priority = inSource.priority;
    }
}
