/**
 * Will McIntosh 5-21-20, program 4
 * This class handles everything pertaining to the array
 * That is inside of each node. Vec is the parent of the node class.
 */
public class Vec {
    protected Job aJob;

    /**
     * Default constructor.
     */
    public Vec() {
        aJob = new Job();
    }

    /**
     * Parameterized Constructor down casting to call copy constructors
     * @param inJob object passed in and inserted into the proper array element
     */
    public Vec(Job inJob) {
        if (inJob instanceof Gig) {
            Gig newGig = (Gig) inJob;
            this.aJob = new Gig(newGig);
        }
        else if (inJob instanceof FullTime) {
            FullTime newFullTime = (FullTime) inJob;
            this.aJob = new FullTime(newFullTime);
        }
    }

    /**
     * Inserts the Gig into the next available spot in the array
     * @param newGig object passed in, inserted in the nest available element
     * @return 1 if there is space available, returns 0 if not
    public int InsertGigIntoArray(Gig newGig) {
        for (int i = 0; i < this.cap; ++i) {
            if (this.aJob [i] == null) {
                this.aJob [i] = new Gig(newGig);
                return 1;
            }
        }
        return 0;
    }
    */

    /**
     * Inserts the FullTime into the next available spot in the array
     * @param newFullTime Object passed in, inserted in next available element
     * @return 1 if there is space available, returns 0 if not
    public int InsertFullTimeIntoArray(FullTime newFullTime) {
        for (int i = 0; i < this.cap; ++i) {
            if (this.aJob [i] == null) {
                this.aJob [i] = new FullTime(newFullTime);
                return 1;
            }
        }
        return 0;
    }
    */

    /**
     * Wrapper. Tells required Job object to display contents
     * @return simply calls the object's output / display function
     */
    public int DisplayNode() {
        return aJob.OutPut();
    }
}
