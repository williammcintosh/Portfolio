/**
 * Will McIntosh, 5-21-20, program 4
 * This class simply holds the name of the class object. It is the highest of the hierarchy
 */
public class Name {
    protected String a_name;

    /**
     * Default constructor
     */
    public Name() {this.a_name = new String(); }

    /**
     * Copy constructor
     * @param in_Name
     */
    public Name(Name in_Name) { this.a_name = in_Name.a_name; }
}
