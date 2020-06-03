/**
 * Will McIntosh 5-21-20, program 4
 * This class is all things pertaining to the abstract base class.
 * It also holds unique information about the job class object that
 * not other class has, which is the date, time, and wage.
 */
import java.util.Scanner;
import java.io.FileNotFoundException;

public class Job extends Source {
    protected String a_date;
    protected String a_time;
    protected float a_wage;

    /**
     * Default constructor
     */
    public Job() {
        super();
        this.a_date = new String();
        this.a_time = new String();
        this.a_wage = 0.0f;
    }

    /**
     * Copy Constructor.
     * @param in_Job
     */
    public Job(Job in_Job) {
        super(in_Job);
        this.a_date = in_Job.a_date;
        this.a_time = in_Job.a_time;
        this.a_wage = in_Job.a_wage;
    }

    /**
     * These functions don't do anything.
     * I needed it here in order to satisfy the syntax checker's
     * requirements for dynamic binding.
     */
    public boolean ReadFromUser() { return true; }
    public int OutPut() {
        return 1;
    }
    public boolean ReadFromFile(Scanner inSC, String tempType) throws FileNotFoundException { return true; }
}

