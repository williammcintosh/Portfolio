import java.io.File;
import java.io.FileNotFoundException;
import java.util.Scanner;

public class FullTime extends Job {
    protected Scanner input;
    protected String duties;
    protected String benefits;
    protected String type;

    protected FullTime() {
        super();
        this.duties = new String();
        this.benefits = new String();
        this.type = new String();
    }

    public FullTime(FullTime in_FullTime) {
        super(in_FullTime);
        this.input = in_FullTime.input;
        this.type = in_FullTime.type;
        this.duties = in_FullTime.duties;
        this.benefits = in_FullTime.benefits;
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

        type = "FullTime";

        System.out.print("Please enter the full time job's benefits:");
        benefits = input.nextLine();
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
        //System.out.println("Wage:\t$" + a_wage + " an hour");
        duties = inSC.nextLine();
        //System.out.println("Duties:\t" + duties);
        benefits = inSC.nextLine();
        //System.out.println("Benefits:\t" + benefits);
        System.out.print("\n");

        if (a_name == null || a_source == null || a_date == null ||
                a_time == null || type == null || duties == null) {
            return false;
        }
        return true;
    }
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
        System.out.println("Benefits:\t" + benefits + "\n");
        return 1;
    }
}

