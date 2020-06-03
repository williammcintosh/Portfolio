/**
 * Will McIntosh, 5-21-20, Program 4
 * This class is all things pertaining to the Binary Search Tree.
 * You'll find a small heading over each function explaining it's purpose.
 */
import java.io.FileNotFoundException;
import java.util.Scanner;

public class Table {
    protected Node root [];
    protected int cap;

    /**
     * Default constructor.
     */
    public Table() {
        this.cap = 99;
        this.root = new Node [cap];
    }

    /**
     * Called from main
     * @param sc takes the scanner from user selected txt source option
     * @return the numbers of inserted files
     * @throws FileNotFoundException used if the file isn't found
     */
    public int InsertFromFile(Scanner sc) throws FileNotFoundException {
        int inserted = 0;
        //Checks next line in txt file sc scanner
        while (sc.hasNextLine()) {
            //Temporary String to read in the type of job from the file
            String tempType = sc.nextLine();
            //Instantiating an object of Job
            Job MyJob1;
            //Upcasting the Job object
            if (tempType.equals("Gig")) {
                MyJob1 = new Gig();
            } else {
                MyJob1 = new FullTime();
            }
            //Reading in from file and confirming
            if (MyJob1.ReadFromFile(sc, tempType)) {
                inserted++;
            }
            //Recursively call this same function.
            root [MyJob1.priority] = InsertionSort(root [MyJob1.priority], MyJob1);
        }
        //Displays the numbers of items inserted
        System.out.println("We inserted " + inserted + " job listings.");
        //number inserted returned
        return inserted;
    }

    /**
     * Called from main when user wants to manually insert a new job
     * @return true if the strings were copied, false otherwise
     */
    public boolean InsertFromUser () {
        //Instantiating scanner and strings for menu options
        Scanner input = new Scanner(System.in);
        String userInput = new String();
        System.out.println("Which type would you like to make:");
        System.out.println(" a. Gig job");
        System.out.println(" b. Full Time job");
        userInput = input.nextLine();
        //Instantiating an object of Job w/o initialization
        Job MyJob1;
        //Upcasting the Job object
        switch (userInput.toUpperCase()) {
            //User selected Gig. Collects info from user into temp.
            case "A":
                MyJob1 = new Gig();
                if (MyJob1.ReadFromUser()) {
                    root [MyJob1.priority] = InsertionSort(root [MyJob1.priority], MyJob1);
                    return true;
                }
                break;
            case "B":
                MyJob1 = new FullTime();
                if (MyJob1.ReadFromUser()) {
                    root [MyJob1.priority] = InsertionSort(root [MyJob1.priority], MyJob1);
                    return true;
                }
                break;
            default: System.out.println("That...wasn't an option. Well done.");
        }

        return false;
    }

    /**
     * Called from main.
     * @param root Required for recursion. The specific element requested in the call
     * @param inJob Takes a Job class object and inserts in the appropriate node
     * @return root. Required for recursion.
     */
    public Node InsertionSort(Node root, Job inJob) {
        //This means we're a leaf location
        if ((root == null) || (inJob.a_name.compareTo(root.aJob.a_name) > 0)) {
            return new Node(inJob);
        }

        root.next = InsertionSort(root.next, inJob);

        return root;
    }

    /**
     * Called if InsertionSort found a match. Downcasts.
     * @param inJob Takes a Job class object and inserts into node's array
     * @return root, required for recursion
     *
    public Node InsertIntoArray(Job inJob) {
        if (inJob instanceof Gig) {
            Gig newGig = (Gig) inJob;
            root [inJob.priority] = InsertGigIntoArray(newGig);
        }
        else if (inJob instanceof FullTime) {
            FullTime newFullTime = (FullTime) inJob;
            root [inJob.priority] = InsertFullTimeIntoArray(newFullTime);
        }
        return root [inJob.priority];
    }
    */

    /**
     * Inserts the Gig into the next available spot in the array
     * @param newGig Takes a Gig class object and passes it in array
     * @return root, required for recursive calls w/ node connection on unwind
    public Node InsertGigIntoArray(Gig newGig) {
        for (int i = 0; i < root.cap; ++i) {
            if (root.aJob [i] == null) {
                root.aJob [i] = new Gig(newGig);
                return root;
            }
        }
        return null;
    }
    */

    /**
     * Inserts the FullTime into the next available spot in the array
     * @param newFullTime Takes a FullTime class object and passes it in array
     * @return root, required for recursive calls w/ node connection on unwind
    public Node InsertFullTimeIntoArray(FullTime newFullTime) {
        for (int i = 0; i < root.cap; ++i) {
            if (root.aJob [i] == null) {
                root.aJob [i] = new FullTime(newFullTime);
                return root;
            }
        }
        return null;
    }
    */

    /**
     * Wrapper called from main.
     * @return 1, no need to send anything further to main
     */
    public int DisplayEverything() {
        int count = 0;
        for (int i = 0; i < this.cap; ++i) {
            if (root [i] != null) {
                count += DisplayEverything(root [i]);
            }
        }
        System.out.println("There are currently " + count + " job listings");
        return count;
    }

    /**
     * Traverses through tree displaying all nodes
     * @param root required for recursion
     * @return the amount of nodes
     */
    public int DisplayEverything(Node root) {
        int count = 0;
        //If at end of tree, return 0
        if (root == null)
            return 0;
        //Display and Recursive call to the next
        root.DisplayNode();
        count += DisplayEverything(root.next) +1;
        //Return the amount of nodes
        return count;
    }

    /**
     * Wrapper called from main. Displays nodes based on user's desired priority
     * @return count from recursive function below
     */
    public int DisplayByPriority() {
        //Initializing input Scanner and new int for user input of desired priority
        Scanner input = new Scanner(System.in);
        int inPri = 0;
        System.out.println("Please type in the priority integer you're interested in seeing(1-99):");
        inPri = input.nextInt(); input.nextLine();
        //instantiates integer to count number of jobs in that priority
        int count = 0;
        //Combs through the entire array looking for that specific priority.
        for (int i = 0; i < cap; ++i) {
            if (root [i] != null) {
                if (root [i].aJob.priority == inPri) {
                    //Calls the function with the new int as an argument
                    count = DisplayByPriority(root[i], inPri);
                }
            }
        }
        System.out.println("There are currently " + count + " job listings with priority " + inPri);
        return count;
    }

    /**
     * Recursive. Looks for nodes with matching priority entered from user
     * @param root required for recursion
     * @param inPri user define parameter to search for matches
     * @return count, the amount of matching items
     */
    public int DisplayByPriority(Node root, int inPri) {
        int count = 0;
        //Return null if at end of tree
        if (root == null)
            return 0;
        //Display and Recursive call to the next
        root.DisplayNode();
        count += DisplayByPriority(root.next, inPri);
        //Returns the amount of matching nodes
        return count;
    }

    /**
     * Wrapper called from various locations
     * @return the number of job listings
     */
    public int CountAll() {
        //Instantiates the counter
        int count = 0;
        for (int i = 0; i < cap; ++i)
            if (root [i] != null) {
                count += CountAll(root[i]);
            }
        return count;
    }

    /**
     * Recursive function returning number of job listings
     * @param root
     * @return count which is the number of job listings
     */
    public int CountAll(Node root) {
        //Instantiates counter
        int count = 0;
        //If we're at the end, return 0
        if (root == null) {
            return 0;
        }
        //Recursively calls to the next adding to 'count'
        count += CountAll(root.next) +1;
        //returns count total
        return count;
    }

    /**
     * Wrapper function called from main.
     * @return 1 because I'm not sure how to confirm removal
     */
    public int RemoveEverything() {
        for (int i = 0; i < cap; ++i) {
            if (root [i] != null) {
                root [i] = RemoveEverything(root [i]);
            }
        }
        return 1;
    }

    /**
     * Recursive function called for each for loop from wrapper.
     * @param root required for recursion w/ node connection at unwinding
     * @return required for recursion w/ node connection at unwinding
     */
    public Node RemoveEverything(Node root) {
        if (root == null) {
            return null;
        }

        root.next = RemoveEverything(root.next);

        return root;
    }

    /**
     * Wrapper function called from main. Get's users desired Priority number.
     * @return 1 because I'm not sure how to confirm success of removal
     */
    public int RemoveByPriority() {
        //Initializing input Scanner and new int
        Scanner input = new Scanner(System.in);
        int inPri = 0;
        System.out.println("Please type in the priority you're interested in removing(1-99):");
        inPri = input.nextInt(); input.nextLine();

        //Calls the function with the new int as an argument
        root [inPri] = RemoveEverything(root [inPri]);
        System.out.println("We removed all job listings with priority " + inPri);
        return 1;
    }

    /**
     * Recursive function to remove a node by desired priority
     * @param root Required for recursive node connection at unwinding
     * @param inPri Argument written from user to select desired priority
     * @return root, Required for recursive node connection at unwinding
    public Node RemoveByPriority(Node root, int inPri) {
        if (root == null) {
            return null;
        }
        //If inPri is lesser, move next
        if (inPri < root.aJob [0].priority) {
            root.next = RemoveByPriority(root.next, inPri);
        }
        //If inPri is greater, move right
        else if (inPri > root.aJob [0].priority) {
            root.right = RemoveByPriority(root.right, inPri);
        }
        //If there's a match...
        else if (inPri == root.aJob [0].priority)
        {
            //...and you only have a single child, return that child.
            if (root.next == null)
                return root.right;
            else if (root.right == null)
                return root.next;
            //...and you have both children, we need the IOS and all it's array's members
            for (int i = 0; i < root.cap; ++i) {
                root.aJob [i] = new Job(FindIOSJob(root.right, i));
            }
            //Replace the IOS
            root.right = RemoveByPriority(root.right, inPri);
        }
        //Needed for recursion
        return root;
    }
    */

    /**
     * Returns the IOS Job class object
     * @param root Takes a node
     * @param i Takes the element to comb up the array
     * @return return the Job object from the IOS
    public Job FindIOSJob(Node root, int i) {
        root = FindIOS(root);
        //After the IOS has been found above, gets the job from it recursively
        if (root != null) {
            return root.aJob [i];
        }
        //Reached the end
        return null;
    }
    */

    /**
     * This returns the root that is the IOS, using recursion
     * @param root required for recursive node connection at unwinding
     * @return required for recursive node connection at unwinding
    public Node FindIOS(Node root) {
        //This connects
        if (root.next == null) {
            return root;
        }
        //Keeps moving next
        root = FindIOS(root.next);
        //Required for recursion
        return root;
    }
    */
}
