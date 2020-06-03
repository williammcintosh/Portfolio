
public class Source extends Name {
    protected String a_source;
    protected int priority;

    //Default Constructor
    protected Source() {
        super();
        this.a_source = new String(); }

    //Copy Constructor
    public Source(Source inSource) {
        super(inSource);
        this.a_source = inSource.a_source;
        this.priority = inSource.priority;
    }
}
