import java.io.File;
import java.io.FileNotFoundException;
import java.util.Scanner;

public class Tree {
    protected Node root;

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
            if (tempType == "Gig") {
                MyJob1 = new Gig();
            } else {
                MyJob1 = new FullTime();
            }
            //Reading in from file and confirming
            if (MyJob1.ReadFromFile(sc, tempType)) {
                inserted++;
            }
            //Recursively call this same function.
            root = InsertIntoTree(root, MyJob1);
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
                    root = InsertIntoTree(root, MyJob1);
                    return true;
                }
                break;
            case "B":
                MyJob1 = new FullTime();
                if (MyJob1.ReadFromUser()) {
                    root = InsertIntoTree(root, MyJob1);
                    return true;
                }
                break;
            default: System.out.println("That...wasn't an option. Well done.");
        }

        return false;
    }

    /**
     * Called from main.
     * @param root Required for recursion.
     * @param inJob Takes a Job class object and inserts in the appropriate node
     * @return root. Required for recursion.
     */
    public Node InsertIntoTree(Node root, Job inJob) {
        //This means we're a leaf location
        if (root == null) {
            return new Node(inJob);
        }
        //Traverse either left or right, examining the first element in the array
        //If there's a match, store in that node's array.

        if (inJob.priority == root.aJob [0].priority) {
            root = InsertIntoArray(inJob);
        } else if (inJob.priority < root.aJob[0].priority) {
            root.left = InsertIntoTree(root.left, inJob);
        } else {
            root.right = InsertIntoTree(root.right, inJob);
        }
        return root;
    }

    /**
     * Called if InsertIntoTree found a match. Downcasts.
     * @param inJob Takes a Job class object and inserts into node's array
     * @return root, required for recursion
     */
    public Node InsertIntoArray(Job inJob) {
        if (inJob instanceof Gig) {
            Gig newGig = (Gig) inJob;
            root = InsertGigIntoArray(newGig);
        }
        else if (inJob instanceof FullTime) {
            FullTime newFullTime = (FullTime) inJob;
            root = InsertFullTimeIntoArray(newFullTime);
        }
        return root;
    }

    /**
     * Inserts the Gig into the next available spot in the array
     * @param newGig Takes a Gig class object and passes it in array
     * @return root, required for recursive calls w/ node connection on unwind
     */
    public Node InsertGigIntoArray(Gig newGig) {
        for (int i = 0; i < root.cap; ++i) {
            if (root.aJob [i] == null) {
                root.aJob [i] = new Gig(newGig);
                return root;
            }
        }
        return null;
    }

    /**
     * Inserts the FullTime into the next available spot in the array
     * @param newFullTime Takes a FullTime class object and passes it in array
     * @return root, required for recursive calls w/ node connection on unwind
     */
    public Node InsertFullTimeIntoArray(FullTime newFullTime) {
        for (int i = 0; i < root.cap; ++i) {
            if (root.aJob [i] == null) {
                root.aJob [i] = new FullTime(newFullTime);
                return root;
            }
        }
        return null;
    }

    /**
     * Wrapper called from main.
     * @return 1, no need to send anything further to main
     */
    public int DisplayEverything() {
        int count = DisplayEverything(root);
        System.out.println("There are currently " + count + " job listings");
        return 1;
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
        //Recursive call to the left
        count += DisplayEverything(root.left);
        //Displays all elements in the array, increasing count
        for (int i = 0; i < root.cap; ++i) {
            if (root.aJob [i] != null) {
                root.DisplayNode(i);
                count++;
            }
        }
        //Recursive call to the right
        count += DisplayEverything(root.right);
        //Return the amount of nodes
        return count;
    }

    /**
     * Wrapper called from main. Displays nodes based on user's desired priority
     * @return count from recursive function below
     */
    public int DisplayByPriority() {
        //Initializing input Scanner and new int
        Scanner input = new Scanner(System.in);
        int inPri = 0;
        System.out.println("Please type in the priority integer you're interested in seeing:");
        inPri = input.nextInt(); input.nextLine();

        //Calls the function with the new int as an argument
        int count = DisplayByPriority(root, inPri);
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
        //Recursive call to the left
        count += DisplayByPriority(root.left, inPri);
        //It node is a match, comb through array displaying each
        if (root.aJob [0].priority == inPri) {
            for (int i = 0; i < root.cap; ++i) {
                if (root.aJob[i] != null) {
                    root.DisplayNode(i);
                    count++;
                }
            }
        }
        //Recursive call to the right
        count += DisplayByPriority(root.right, inPri);
        //Returns the amount of matching nodes
        return count;
    }

    /**
     * Wrapper called from various locations
     * @return the number of job listings
     */
    public int CountAll() {
        return CountAll(root);
    }

    /**
     * Recursive function returning number of job listings
     * @param root
     * @return count which is the number of job listings
     */
    public int CountAll(Node root) {
        int count = 0;
        //If we're at the end, return 0
        if (root == null) {
            return 0;
        }
        //Recursively calls to the left adding to 'count'
        count += CountAll(root.left);
        //Counts one for each non null element
        for (int i = 0; i < root.cap; ++i) {
            if (root.aJob[i] != null) {
                count++;
            }
        }
        //Recursively calls to the right adding to 'count'
        count += CountAll(root.right);
        //returns count total
        return count;
    }

    /**
     * Wrapper function called from main.
     * @return 1 because I'm not sure how to confirm removal
     */
    public int RemoveEverything() {
        do {
            root = RemoveEverything(root);
        } while(CountAll() > 0);
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
        if (root.left == null && root.right == null) {
            return null;
        }

        root.left = RemoveEverything(root.left);
        root.right = RemoveEverything(root.right);

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
        System.out.println("Please type in the priority you're interested in removing:");
        inPri = input.nextInt(); input.nextLine();

        //Calls the function with the new int as an argument
        root = RemoveByPriority(root, inPri);
        System.out.println("We removed all job listings with priority " + inPri);
        return 1;
    }

    /**
     * Recursive function to remove a node by desired priority
     * @param root Required for recursive node connection at unwinding
     * @param inPri Argument written from user to select desired priority
     * @return root, Required for recursive node connection at unwinding
     */
    public Node RemoveByPriority(Node root, int inPri) {
        if (root == null) {
            return null;
        }
        //If inPri is lesser, move left
        if (inPri < root.aJob [0].priority) {
            root.left = RemoveByPriority(root.left, inPri);
        }
        //If inPri is greater, move right
        else if (inPri > root.aJob [0].priority) {
            root.right = RemoveByPriority(root.right, inPri);
        }
        //If there's a match...
        else if (inPri == root.aJob [0].priority)
        {
            //...and you only have a single child, return that child.
            if (root.left == null)
                return root.right;
            else if (root.right == null)
                return root.left;
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

    /**
     * Returns the IOS Job class object
     * @param root Takes a node
     * @param i Takes the element to comb up the array
     * @return return the Job object from the IOS
     */
    public Job FindIOSJob(Node root, int i) {
        root = FindIOS(root);
        //After the IOS has been found above, gets the job from it recursively
        if (root != null) {
            return root.aJob [i];
        }
        //Reached the end
        return null;
    }

    /**
     * This returns the root that is the IOS, using recursion
     * @param root required for recursive node connection at unwinding
     * @return required for recursive node connection at unwinding
     */
    public Node FindIOS(Node root) {
        //This connects
        if (root.left == null) {
            return root;
        }
        //Keeps moving left
        root = FindIOS(root.left);
        //Required for recursion
        return root;
    }
}
