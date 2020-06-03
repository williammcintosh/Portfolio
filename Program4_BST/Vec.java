public class Vec {
    protected Job aJob [];
    protected int cap;

    /**
     * Default constructor.
     */
    public Vec() {
        this.cap = 5;
        this.aJob = new Job [cap];
    }

    /**
     * Parameterized Constructor down casting to call copy constructors
     * @param inJob object passed in and inserted into the proper array element
     */
    public Vec(Job inJob) {
        this.cap = 5;
        this.aJob = new Job [cap];
        if (inJob instanceof Gig) {
            Gig newGig = (Gig) inJob;
            InsertGigIntoArray(newGig);
        }
        else if (inJob instanceof FullTime) {
            FullTime newFullTime = (FullTime) inJob;
            InsertFullTimeIntoArray(newFullTime);
        }
    }

    /**
     * Inserts the Gig into the next available spot in the array
     * @param newGig object passed in, inserted in the nest available element
     * @return 1 if there is space available, returns 0 if not
     */
    public int InsertGigIntoArray(Gig newGig) {
        for (int i = 0; i < this.cap; ++i) {
            if (this.aJob [i] == null) {
                this.aJob [i] = new Gig(newGig);
                return 1;
            }
        }
        return 0;
    }

    /**
     * Inserts the FullTime into the next available spot in the array
     * @param newFullTime Object passed in, inserted in next available element
     * @return 1 if there is space available, returns 0 if not
     */
    public int InsertFullTimeIntoArray(FullTime newFullTime) {
        for (int i = 0; i < this.cap; ++i) {
            if (this.aJob [i] == null) {
                this.aJob [i] = new FullTime(newFullTime);
                return 1;
            }
        }
        return 0;
    }

    /**
     * Wrapper. Tells required Job object to display contents
     * @param i The element requested from the calling function
     * @return simply calls the object's output / display function
     */
    public int DisplayNode(int i) {
        return aJob [i].OutPut();
    }
}
