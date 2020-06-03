/**
 * Will McIntosh, 5-21-20, program 5
 * This is the main class which acts as the main menu for the program.
 * Here, the user is greeted and asked to insert, display or remove materials.
 */
import java.io.File;
import java.io.FileNotFoundException;
import java.util.Scanner;

public class CS202_Prog4 {
    public static void main(String[] args) throws FileNotFoundException {
        //Instantiating Booleans to prevent loading data from the same source
        boolean hasNewsPaper = false;
        boolean hasIndeedcom = false;
        boolean hasPSUjobs = false;
        //Tree object to start the data structure
        Table my_tree = new Table();
        Boolean again = false;

        //Input Scanner for user menu
        Scanner input = new Scanner(System.in);
        String mainInput = new String();

        //Menu display options
        System.out.println("Welcome to your job list insertion!");
        do {
            System.out.println("Would you like to:");
            System.out.println(" a. Insert jobs from sources");
            System.out.println(" b. Insert job manually");
            System.out.println(" c. Display job listing(s)");
            System.out.println(" d. Remove job listing(s)");
            System.out.println(" e. Get the number of listings");
            mainInput = input.nextLine();
            //Main menu options
            switch (mainInput.toUpperCase()) {
                //User selected to insert jobs from sources (txt files)
                case "A":
                    String userInput2 = new String();
                    System.out.println(" a. Insert jobs from newspaper");
                    System.out.println(" b. Insert jobs from indeed.com");
                    System.out.println(" c. Insert jobs from PSU listings");
                    userInput2 = input.nextLine();

                    switch (userInput2.toUpperCase()) {
                        //User selected they want jobs from the newspaper
                        case "A":
                            File paperFile = new File(System.getProperty("user.dir") + "/src/" + "Newspaper.txt");
                            Scanner sc1 = new Scanner(paperFile);
                            //Checks to see if the user already loaded from source and there was an error in input
                            if (!hasNewsPaper) {
                                if (my_tree.InsertFromFile(sc1) <= 0) {
                                    System.out.println("Looks like that didn't work. Let's try again.");
                                } else {
                                    hasNewsPaper = true;
                                }
                            } else {
                                System.out.println("Looks like you've already loaded from that source. Try again.");
                            } break;
                        //User selected they want jobs from the Indeed.com
                        case "B":
                            File onlineFile = new File(System.getProperty("user.dir") + "/src/" + "Indeedcom.txt");
                            Scanner sc2 = new Scanner(onlineFile);
                            //Checks to see if the user already loaded from source and there was an error in input
                            if (!hasIndeedcom) {
                                if (my_tree.InsertFromFile(sc2) <= 0) {
                                    System.out.println("Looks like that didn't work. Let's try again.");
                                } else {
                                    hasIndeedcom = true;
                                }
                            } else {
                                System.out.println("Looks like you've already loaded from that source. Try again.");
                            } break;
                        //User selected they want jobs from the PSU's Jobs
                        case "C":
                            File PSUFile = new File(System.getProperty("user.dir") + "/src/" + "PSUJobs.txt");
                            Scanner sc3 = new Scanner(PSUFile);
                            //Checks to see if the user already loaded from source and there was an error in input
                            if (!hasPSUjobs) {
                                if (my_tree.InsertFromFile(sc3) <= 0) {
                                    System.out.println("Looks like that didn't work. Let's try again.");
                                } else {
                                    hasPSUjobs = true;
                                }
                            } else {
                                System.out.println("Looks like you've already loaded from that source. Try again.");
                            } break;
                    } break;
                //User selected to manually insert a new job
                case "B": if (!my_tree.InsertFromUser()) {
                    System.out.println("Looks like that didn't work. Let's try again.");
                } break;
                //User selected to display jobs
                case "C":
                    String userInput3 = new String();
                    System.out.println(" a. Display job(s) by priority");
                    System.out.println(" b. Display everything");
                    userInput3 = input.nextLine();
                    //Display sub menu options
                    switch (userInput3.toUpperCase()) {
                        case "A": my_tree.DisplayByPriority(); break;
                        case "B": my_tree.DisplayEverything(); break;
                    } break;
                //User selected to remove jobs
                case "D":
                    String userInput4 = new String();
                    System.out.println(" a. Remove job(s) by priority");
                    System.out.println(" b. Remove all jobs");
                    userInput4 = input.nextLine();
                    //User removal options
                    switch (userInput4.toUpperCase()) {
                        case "A":
                            my_tree.RemoveByPriority(); break;
                        case "B":
                            my_tree.RemoveEverything(); break;
                    } break;
                case "E": System.out.println("There are currently " + my_tree.CountAll() + " job listings"); break;
                default: System.out.println("I...didn't get that."); break;
            }
            //Check if user wants to repeat
            System.out.println("Perform another action?(Y/N)");
            mainInput = input.nextLine();
            switch (mainInput.toUpperCase()) {
                case "Y": again = true; break;
                default: again = false; break;
            }
        } while(again);
        //Friendly closing message
        System.out.println("Thank you, and keep being awesome!");
    }
}
