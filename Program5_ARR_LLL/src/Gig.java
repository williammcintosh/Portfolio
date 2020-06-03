/**
 * Will McIntosh, 5-21-20, program 4
 * This class is one of the children of the two children
 * of the abstract base class. It's unique member is the duration.
 * Since a gig is a short term job, the duration is in days.
 */
import java.util.Scanner;

public class Gig extends Job {
    protected Scanner input;
    protected String duties;
    protected String duration;
    protected String type;

    public Gig() {
        super();
        this.duties = new String();
        this.duration = new String();
        this.type = new String();
    }

    public Gig(Gig in_Gig) {
        super(in_Gig);
        this.input = in_Gig.input;
        this.type = in_Gig.type;
        this.duties = in_Gig.duties;
        this.duration = in_Gig.duration;
    }

    @Override
    public boolean ReadFromUser() {
        Scanner input = new Scanner(System.in);
        System.out.print("Please enter the name of the job:");
        a_name = input.nextLine();
        System.out.print("Please enter the source of this posting:");
        a_source = input.nextLine();
        System.out.print("Please enter a priority:");
        priority = input.nextInt(); input.nextLine();
        System.out.print("Please enter the start date and time:");
        a_date = input.nextLine();
        a_time = input.nextLine();
        System.out.print("Please enter your hourly wage:");
        a_wage = input.nextFloat(); input.nextLine();
        type = "Gig";
        System.out.print("Please enter the gig's duties:");
        duties = input.nextLine();
        System.out.print("Please enter the gig's duration in days:");
        duration = input.nextLine();
        if (a_name == null || a_source == null || a_date == null ||
            a_time == null || type == null || duties == null) {
            return false;
        }
        return true;
    }

    /**
     * This function continues to read in from the txt file for each member
     * @param inSC This is the same scanner object, combing through the txt file
     * @param tempType This reads the first line for each object, determining it's type
     * @return True.
     */
    @Override
    public boolean ReadFromFile(Scanner inSC, String tempType) {
        //Copies the type over from the calling function
        type = tempType;
        //System.out.println("Type:\t" + type);
        a_name = inSC.nextLine();
        System.out.println("Name:\t" + a_name);
        a_source = inSC.nextLine();
        //System.out.println("Source:\t" + a_source);
        priority = inSC.nextInt(); inSC.nextLine();
        System.out.println("Priority:\t" + priority);
        a_date = inSC.nextLine();
        //System.out.println("Date:\t" + a_date);
        a_time = inSC.nextLine();
        //System.out.println("Time:\t" + a_time);
        a_wage = inSC.nextFloat(); inSC.nextLine();
        //System.out.println("Wage:\t" + a_wage);
        duties = inSC.nextLine();
        //System.out.println("Duties:\t" + duties);
        duration = inSC.nextLine();
        //System.out.println("Duration:\t" + duration + " days");
        System.out.print("\n");
        //I couldn't figure out a way to determine reading in from file
        if (a_name == null || a_source == null || a_date == null ||
                a_time == null || type == null || duties == null) {
            return false;
        }
        return true;
    }

    /**
     * Prints out each member in the hierarchy
     * @return
     */
    @Override
    public int OutPut() {
        System.out.println("Type:\t" + type);
        System.out.println("Name:\t" + a_name);
        System.out.println("Source:\t" + a_source);
        System.out.println("Priority:\t" + priority);
        System.out.println("Date:\t" + a_date);
        System.out.println("Time:\t" + a_time);
        System.out.println("Wage:\t$" + a_wage + " an hour");
        System.out.println("Duties:\t" + duties);
        System.out.println("Duration:\t" + duration + " days\n");
        return 1;
    }
}
