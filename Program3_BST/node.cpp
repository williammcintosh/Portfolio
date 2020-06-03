#include "node.h"
using namespace std;

/**********************************************************
 * VEC CLASS
 **********************************************************/

//Default constructor
//The tasks array (which is an array of base
//class pointers) get instantiated initially at 10.
//Then the temps points is used for temporary storage.
vec::vec() : cap(3)
{
    tasks = new task * [cap];
    temps = new task * [cap];

    for (int i = 0; i < cap; ++i)
    {
        tasks[i] = NULL;
        temps[i] = NULL;
    }
}

//Wrecks the grill of all things dynamic!
vec::~vec()
{
    for (int i = 0; i < cap; ++i)
        if (tasks[i])
            delete tasks[i];

    if (tasks)
        delete tasks;

    for (int i = 0; i < cap; ++i)
        if (temps[i])
            delete temps[i];

    if (temps)
        delete temps;
}

//This function is called by the node class
//It requests the type of activity to be inserted be the user,
//so that way it know which task type to create, binding the type dynamically.
//Then stores informaion into it
int vec::insert(int my_pri)
{
    int inc = 0;
    task * in_task;
    char t_type;

    //Creates a new Task class object using dynamic cast
    cout << "\nWhich activity would you like to insert?\n"
        << " a. Hiking.\n b. Dining.\n c. Zooing.\n";
    cin.get(t_type); cin.ignore(MAX,'\n');

    switch(toupper(t_type))
    {
        case 'A': in_task = new hiking; break;
        case 'B': in_task = new dining; break;
        case 'C': in_task = new zooing; break;
        default : cout << "I didn't catch that.\n"; break;
    }

    //Stores information into the new Task
    in_task->name::read();
    in_task->read();
    in_task->activity::read();
    in_task->task::read();

    //Transfers most recently created task to 'temps'
    if (!task_to_array(in_task, inc = 0))
        cout << "Looks like something while inserting. Try again!\n";

    //Displays 'tasks'
    if (!display_array(my_pri))
        cout << "Looks like something while inserting. Try again!\n";

    //Clears memory for task created in this function.
    if (in_task)
    {
        delete in_task;
        return 1;
    }

    return 0;
}

//This function first takes into consideration,
//whether the list is empty first
//if so, then a new object is build from one derivatives
//of the abstract base class type.
int vec::task_to_array(task *& in_task, int & inc)
{
    if (tasks[inc] == NULL
            || (strcmp(in_task->get_name(),tasks[inc]->get_name()) <= 0))
    { 
        shifty_shift_up(inc);

        hiking * t_ptr = dynamic_cast< hiking * >(in_task);
        if (t_ptr)
        {
            tasks[inc] = new hiking(* t_ptr);
            return 1;
        }
        else
        {
            dining * t_ptr = dynamic_cast< dining * >(in_task);
            if (t_ptr)
            {
                tasks[inc] = new dining(* t_ptr);
                return 1; 
            }
            else
            {
                zooing * t_ptr = dynamic_cast< zooing * >(in_task);
                if (t_ptr)
                {
                    tasks[inc] = new zooing(* t_ptr);
                    return 1;
                }
                else
                {
                    cerr << "Looks like we have a downcasting error. Please try again.\n";
                    return 0;
                }
            }
        }
    }

    return task_to_array(in_task, ++inc);
}

//This function moves everything in the array up one element,
//to the point "inc" passed from the calling function.
//Since I have no real way of reporting errors,
//or results from this activity, this function
//has a return type of "void".
void vec::shifty_shift_up(int & inc)
{
    for (int i = cap-1; i > inc-1; --i)
       if (tasks[i])
            tasks[i+1] = tasks[i];
}

//This function moves everything in the array down one element,
//to the point "inc" passed from the calling function.
//If a match exists, that number is sent as an argument
//as to it's specific location within the array.
//This function then goes from the bottom of the array,
//starting at the location brought in from the argument,
//moves that pointer over into the temporary (which for the sake
//of our conversation can be viewed as a dumpster) and then
//that temp array is cleared with the destructor later.
//Since I have no real way of reporting errors,
//or results from this activity, this function
//has a return type of "void".
void vec::shifty_shift_down(int & inc)
{
    for (int i = inc+1; i < cap-1; ++i)
    {
        for (int j = 0; j < cap; ++j)
            if (!temps[j])
                temps[j] = tasks[i-1];

        tasks[i-1] = tasks[i];
    }
}

//For each node that matches the level number
//sent in by the user, this displays all
//elements in that array and returns the amount there.
int vec::display_array(int in_pri)
{
    int count = 0;

    for (int i = 0; i < cap; ++i)
    {
        if (tasks[i])
        {
            cout << "level #" << in_pri
                << ", task [" << i+1 << "]:\n";
            if (display_element(tasks[i]))
                ++count;
            cout << endl;
        }
    }

    return count;
}

//The argument in some cases is simply passed on from other 
//functions which will ne
int vec::display_array_name()
{
    int count = 0;

    for (int i = 0; i < cap; ++i)
        if (tasks[i])
            cout << tasks[i]->name::get_name();

    return count;
}
//Am I right in thinkig I'm wanting to down cast
//the ACTUAL pointer that lives within Vec's array?
//Or does it make more sense to bring in a copy?
//Should I pass this pointer in by reference?
int vec::display_element(task * in_task)
{
    hiking * t_ptr = dynamic_cast< hiking * >(in_task);
    if (t_ptr)
    {
        cout << "Name: ";
        t_ptr->name::display();
        t_ptr->display();
        return 1;
    }
    else
    {
        dining * t_ptr = dynamic_cast< dining * >(in_task);
        if (t_ptr)
        {
            cout << "Name: ";
            t_ptr->name::display();
            t_ptr->display();
            return 1;
        }
        else
        {
            zooing * t_ptr = dynamic_cast< zooing * >(in_task);
            if (t_ptr)
            {
                cout << "Name: ";
                t_ptr->name::display();
                t_ptr->display();
                return 1;
            }
            else
            {
                cerr << "Looks like we have a downcasting error. Please try again.\n";
                return 0;
            }
        }
    }
}

int vec::display_element_name(task * in_task)
{
    hiking * t_ptr = dynamic_cast< hiking * >(in_task);
    if (t_ptr)
    {
        t_ptr->name::display();
        return 1;
    }
    else
    {
        dining * t_ptr = dynamic_cast< dining * >(in_task);
        if (t_ptr)
        {
            t_ptr->name::display();
            return 1;
        }
        else
        {
            zooing * t_ptr = dynamic_cast< zooing * >(in_task);
            if (t_ptr)
            {
                t_ptr->name::display();
                return 1;
            }
            else
            {
                cerr << "Looks like we have a downcasting error. Please try again.\n";
                return 0;
            }
        }
    }
}
//Removes anything inside of it
//and checks first that it exists
//so it doesn't accidently makes
//and double free errors.
//returns the amount destroyed.
int vec::delete_array()
{
    int kill_count = 0;

    for (int i = 0; i < cap; ++i)
    {
        if (tasks[i])
        {
            cout << "We removed: ";
            tasks[i]->name::display();
            delete tasks[i];
            ++kill_count;
        }
    }

    return kill_count;
}

//Check if the name exists,
//if so, it returns a true/false to the calling
//routine, and then it also shifts all 
//the elements in the array down for
//filling in the hole that would exist otherwise.
int vec::name_exists(char * in_name)
{
    for (int i = 0; i < cap; ++i)
    {
        if (tasks[i])
        {
            if (strcmp(in_name,tasks[i]->get_name()) == 0)
            {
                shifty_shift_down(i);
                return 1;
            }
        }
    }

    return 0;
}

/**********************************************************
 * NODE CLASS
 **********************************************************/

//Default constructor
node::node() : parent(0), left(0), right(0), level(0), ancestor_path(NULL) {}
//Copy constructor
//Used for whenever a new task is made from the insert
//function, and brought in as an argument into the calling
//routine, working it's way up the chain of inheritance
node::node(int my_level) : parent(0), left(0), right(0), level(my_level), ancestor_path(NULL) {}

//Copy constructor
//Calls the parent copy constructor to begin the derivation copy process
node::node(const node & in_root) :
    parent(in_root.parent), left(in_root.left),
    right(in_root.right), level(in_root.level)
{
    if (in_root.ancestor_path)
    {
        ancestor_path = new char[strlen(in_root.ancestor_path) +1];
        strcpy(ancestor_path, in_root.ancestor_path);
    }
}

//This are wrapper functions,
//I mean, they're IMHO getters,
//but this seems to be common practice
//for class nodes as opposed to structs.
node *& node::go_left()
{
    return left;
}

node *& node::go_right()
{
    return right;
}

node *& node::go_parent()
{
    return parent;
}

//This is just for reading the left,
//as opposed to actually editing it.
node * node::get_left() const
{
    return left;
}

//This is used as a comparison check.
int node::check_pri(int my_pri)
{
    if (level == my_pri)
        return 1;

    return 0;
}

//This is simply for the user experience
//menu options to make clear where they are.
//The class that manages the data structure
//will need to, at times, display the priorty
//of the node that it's looking at to the user.
int node::get_pri()
{
    return level;
}

char * node::get_ancestor_path()
{
    return ancestor_path;
}

//This would be setter functions,
//for setting the connecting node that 
//the left pointers will be going to.
void node::connect_left(node * connection)
{
    this->left = connection;
}

void node::connect_right(node * connection)
{
    this->right = connection;
}

void node::connect_parent(node * connection)
{
    this->parent = connection;
}

int node::set_ancestor_path(char * in_path)
{
    if (in_path)
    {
        ancestor_path = new char[strlen(in_path) +1];
        strcpy(ancestor_path,in_path);    
        return 1;
    }

    return 0;
}

/**********************************************************
 * TASK CLASS
 **********************************************************/

//Default Constructor
task::task() : date(NULL), time(NULL) {}

//Copy Constructors
//Makes a deep copy of the char stars dynamic names
//inside of the private members of the class.
//otherwise it would just be a shallow copy.
task::task(const task & to_copy) : activity(to_copy), date(NULL), time(NULL)
{
    if (to_copy.date)
    {
        date = new char[strlen(to_copy.date) +1];
        strcpy(date, to_copy.date);
    }
    else date = NULL; 

    if (to_copy.time)
    {
        time = new char[strlen(to_copy.time) +1];
        strcpy(time, to_copy.time);
    }
    else time = NULL;
}

//Destructor
task::~task()
{
    if(date)
        delete [] date;

    if(time)
        delete [] time;
}

//This function is responsible for taking in the 
//information written by the user
//and they storing that into the specific members
//of the object for each individual task.
//That way, instead of reading in from int main or
//something and then bringing everything as arguments,
//this way, each class actually manages its own data.
int task::read()
{
    char temp_date[MAX], temp_time[MAX];

    cout << "Please enter the date and time of the task:\n";
    cin.get(temp_date, MAX); cin.ignore(3000,'\n');
    cin.get(temp_time, MAX); cin.ignore(3000,'\n');

    date = new char[strlen(temp_date) +1];
    strcpy(date, temp_date);

    time = new char[strlen(temp_time) +1];
    strcpy(time, temp_time);

    if (!date || !time)
        return 0;

    return 1;
}

int task::display() const
{
    if (!date || !time)
        return 0;

    cout << "Due Date:\t" << date << endl
        << "Due Time:\t" << time << endl;

    return 1;
}

/**********************************************************
 * TASK_TREE CLASS
 **********************************************************/

//Default Constructor
task_tree::task_tree() : root(0) {}

//Copies the entire data structure
int task_tree::copy_all_nodes(node *& root, node * in_root)
{
    if (!in_root)
    {
        root = NULL;
        return 0;
    }

    root = new node(*in_root);

    return copy_all_nodes(root->go_left(), in_root->go_left());
}

//Destructor
task_tree::~task_tree()
{
    if (root)
    {
        delete root;
        root = NULL;
    }
}

int task_tree::display_tree()
{
    //Resursively makes each node's 'ancestor path' member
    if (!make_ancestor_path(root))
        cout << "Looks like we have an empty tree!";
    else display_paths(root);

    cout << "\n\n The height of the three is " << height() << endl;

    int level = 1;
    return display_tree(level);
}

int task_tree::display_paths(node * root)
{
    if (!root)
        return 0;

    root->vec::display_array_name();
    cout << root->get_ancestor_path() << endl;

    display_paths(root->go_left());
    display_paths(root->go_right());

    return 0;
}


//Recursive display all function
int task_tree::display_tree(int & level)
{
    int spacing = (16 / pow(2,level));

    if (level > height())
        return 0;

    //Resursively makes each node's 'ancestor path' member
    if (!make_ancestor_path(root))
        cout << "Looks like we have an empty tree!";

    cout << "Level: " << level << endl;
    
    //Display's the name with spacing on each side, loops for number of nodes per line
    for (int j = 0; j < (pow(2,level) /2); ++j) 
    {
        //Lil aesthetic spacer
        cout << ' ';
        //Places spacing around the node's name
        for (int i = 0; i < spacing; ++i) cout << " \t";

        //Creates / resets 'my_path'
        char * my_path = new char[j+4];

        if (level == 1)
        {
            if (j == 0) strcpy(my_path,"| 0");
        }
        else if (level == 2)
        {
            if (j == 0) strcpy(my_path,"| L0");
            if (j == 1) strcpy(my_path,"| R0");
        }
        else if (level == 3)
        {
            if (j == 0) strcpy(my_path,"| LL0");
            if (j == 1) strcpy(my_path,"| RL0");
            if (j == 2) strcpy(my_path,"| LR0");
            if (j == 3) strcpy(my_path,"| RR0");
        }
        else if (level == 4)
        {
            if (j == 0) strcpy(my_path,"| LLL0");
            if (j == 1) strcpy(my_path,"| RLL0");
            if (j == 2) strcpy(my_path,"| LRL0");
            if (j == 3) strcpy(my_path,"| RRL0");
            if (j == 4) strcpy(my_path,"| LLR0");
            if (j == 5) strcpy(my_path,"| RLR0");
            if (j == 6) strcpy(my_path,"| LRR0");
            if (j == 7) strcpy(my_path,"| RRR0");
        }

        //Resursively combs through tree, print elements if match found otherwise blank
        if (!locate_path(root, my_path))
            cout << " ";

        //Aesthetic blank space for each call.
        for (int i = 0; i < spacing; ++i) cout << " \t";

        //Clears dynamic memory
        if (my_path)
            delete [] my_path;
    }

    cout << "\n\n";

    ++level;
            
    //Recursive calls
    level = display_tree(level);

    return 1;
}

int task_tree::make_ancestor_path(node *& root)
{
    int count = 0;

    if (!root)
        return 0;

    //Creates / resets 'my_path'
    char * my_path = new char[8];
    strcpy(my_path,"| ");

    //Recursively sets the entire tree's 'ancestor path' char star member
    if (root->set_ancestor_path(find_ancestor_path(root, my_path)))
        ++count;

    make_ancestor_path(root->go_left());
    make_ancestor_path(root->go_right());

    if (my_path)
        delete [] my_path;

    return count;
}

//This function is responsible for traveling up the
//path of the tree to label each root's ancestor_path
//based on its relationship with it's parent.
//It recursively goes up the ancestry,
//and checks if the root that called it was to the right
//or to the left, and concatenates that information
//to the root's 
char * task_tree::find_ancestor_path(node * root, char * my_path)
{
    if (!root) return 0;

    if (!root->go_parent())
    {
        strcat(my_path,"0");
        return my_path;
    }

    if (root->go_parent()->go_right() == root)
        strcat(my_path,"R");
    else
        strcat(my_path,"L");

    find_ancestor_path(root->go_parent(), my_path);

    return my_path;
}

int task_tree::locate_path(node * root, char * in_path)
{
    if (!root)
        return 0;

    if (strcmp(root->get_ancestor_path(),in_path) == 0)
    {
        root->vec::display_array_name();
        return 1;
    }

    locate_path(root->go_left(), in_path);
    locate_path(root->go_right(), in_path);

    return 0;
}

//Returns the amount of content
int task_tree::count()
{
    return count(root);
}

int task_tree::count(node * root)
{
    if (!root)
        return 0;

    int node_count = count(root->go_left());

    ++node_count;

    node_count += count(root->go_right());

    return node_count;
}

int task_tree::height()
{
    return height(root);
}

int task_tree::height(node * root)
{
    if (!root)
        return 0;
    
    int L_count = height(root->go_left());
    int R_count = height(root->go_right());

    if (L_count > R_count)
        return L_count +1;

    return R_count +1;
}

//Recursive destroy all nodes function
int task_tree::destroy_all(node *& root)
{
    if (!root)
        return 0;

    int count = destroy_all(root->go_left()) +1;

    node * temp = root->go_left();
    delete root;
    root = temp;

    return count;
}

//Since task_tree manages the DLL list of nodes,
//This function is an
//insert Function which places a new node,
//or determines which node to place this in.
//Sticks user in a loop if it's out of range.
int task_tree::insert()
{
    int my_pri;

    cout << "What's the level of this task? How important is it? (1-5): ";
    cin >> my_pri; cin.ignore(MAX,'\n');

    if (create_pri(root, my_pri))
        return 1;

    return 0;
}

//This function is responsible for
//checking if the level node already exists.
//If the list is empty, then a new node is created.
//If the level node requested exists,
//then that node's Vec class inserts a new task.
//Otherwise call the recursive function.
//Since I checked above that the input is between
//1 and 5, I know that this will find the node
//it's looking for.
//This function then calls Vec's insert,
//which makes a new array sized right and sorted.
int task_tree::create_pri(node *& root, int & my_pri)
{
    if (!root)
    {
        node * temp = new node(my_pri);
        temp->vec::insert(my_pri);
        temp->connect_left(0);
        temp->connect_right(0);
        temp->connect_parent(this->root);

        root = temp;
        return 1;
    }
    else if (root->get_pri() > my_pri)
    {
        create_pri(root->go_left(), my_pri);
        root->go_left()->connect_parent(root);
        return 1;
    }

    create_pri(root->go_right(), my_pri);
    root->go_right()->connect_parent(root);
    return 1;
}


//Display Wrapper
int task_tree::display_everything() 
{
    int count = display(root);

    cout << "There are " << count << " tasks currently.\n\n";

    return count;
}

//Recursive display all function
int task_tree::display(node * root)
{
    if (!root)
        return 0;

    int count = display(root->go_left());

    count += root->vec::display_array(root->get_pri());

    count += display(root->go_right());

    return count;
}

//This is the function that's called from Int main.
//It's job is to search for a specific name
//that will be typed in from the user
//and then checked to see if it exists.
int task_tree::single_removal()
{
    char user_input[MAX];
    int killed = 0;

    cout << "Which task name would you like to remove? ";
    cin.get(user_input,MAX); cin.ignore(MAX,'\n');

    killed = remove_by_name(root, user_input);

    cout << "We removed " << killed << " tasks.\n";

    return 0;
}

//This function looks for the name entered in from the user
//and check to see if it exists within the list.
//if so, the left function kills it and the total is returned.
int task_tree::remove_by_name(node *& root, char * user_input)
{
    int removed = 0;

    if (!root) return 0;

    removed += remove_by_name(root->go_left(), user_input);

    if (root->name_exists(user_input))
        ++removed;

    return removed;
}

//This takes in input from the user and uses that
//to understand which prority they're interested in
//getting more information about for removal, insert and display.
int task_tree::task_by_priority()
{
    int in_pri = 0;
    cout << "Please enter the level you're interested in (1-5): ";
    cin >> in_pri; cin.ignore(MAX,'\n');

    if (!task_by_priority(root, in_pri))
        cout << "Looks like that level has no tasks.\n";

    return in_pri;
}

int task_tree::task_by_priority(node * root, int in_pri)
{
    if (!root)
        return 0;

    if (root->check_pri(in_pri))
    {
        if (!root->vec::display_array(in_pri))
            return 0;
        else return 1;
    }

    return task_by_priority(root->go_left(), in_pri);
}

int task_tree::remove_by_priority()
{
    char user_input = '\n';
    int in_pri = task_by_priority();
    int killed = 0;

    cout << "Would you like to remove all tasks in the level? (Y/N): ";
    cin.get(user_input); cin.ignore(MAX,'\n');

    if ('Y' == toupper(user_input))
        killed = remove_by_priority(root, in_pri);

    cout << "We removed " << killed << " tasks.\n";

    return killed;
}

int task_tree::remove_by_priority(node *& root, int in_pri)
{
    int removed = 0;

    if (!root) return 0;

    removed += remove_by_priority(root->go_left(), in_pri);

    if (!root->go_left() && root->check_pri(in_pri))
        removed = root->delete_array();
    else if (root->check_pri(in_pri)) 
    {
        removed = root->delete_array();

        root->go_left()->connect_right(root->go_right());

        node * temp = root;
        root = root->go_left();

        delete temp;
    }

    return removed;
}

/**********************************************************
 * HIKING CLASS
 **********************************************************/

//Default Constructor
hiking::hiking() : duration(0.0f), friends(0), trailroot(NULL) {}

//Copy Constructor
hiking::hiking(const hiking & to_copy) : 
    task(to_copy), duration(to_copy.duration), friends(to_copy.friends)
{
    trailroot = new char[strlen(to_copy.trailroot) +1];
    strcpy(trailroot, to_copy.trailroot);
}

hiking::~hiking()
{
    if (trailroot)
        delete [] trailroot;
}


//This is the first function called from int_main.
//a hiking object is created from int_main,
//and it calls the left function,
//up the chain of inheritance from itself,
//which is the task_tree class.
//It collects the returned data only to make some
//fun numbers to "pretend" like a video was uploaded.
int hiking::read()
{
    char temp[MAX];

    cout << "How many hours will this activity take?\n";
    cin >> duration; cin.ignore(MAX,'\n');
    cout << "How many friends do you plan to take with you?\n";
    cin >> friends; cin.ignore(MAX,'\n');
    cout << "What's the first trailroot you'll be looking for?\n";
    cin.get(temp,MAX); cin.ignore(MAX,'\n');

    trailroot = new char[strlen(temp) +1];
    strcpy(trailroot,temp);

    return 1;
}

//This displays the members of this class,
//the duration of the file and the size.
//Then treats the left display function like a wrapper
//going up the chain of inheritance.
int hiking::display() const
{
    if (!duration || !friends || !trailroot)
        return 0;

    cout << "Duration: " << duration << " hours."
        << "\n# Friends: " << friends
        << "\nTrailroot: " << trailroot << endl;

    return 1;
}

/**********************************************************
 * dining CLASS
 **********************************************************/

//Default Constructor
dining::dining() : duration(0.0f), friends(0), meal(NULL) {}

//Copy Constructor
dining::dining(const dining & to_copy) : 
    task(to_copy), duration(to_copy.duration), friends(to_copy.friends)
{
    meal = new char[strlen(to_copy.meal) +1];
    strcpy(meal, to_copy.meal);
}

dining::~dining()
{
    if (meal)
        delete [] meal;
}

//This is the first function called from int_main.
//a dining object is created from int_main,
//and it calls the left function,
//up the chain of inheritance from itself,
//which is the task_tree class.
//It collects the returned data only to make some
//fun numbers to "pretend" like a video was uploaded.
int dining::read()
{
    char temp[MAX];

    cout << "How many hours will this activity take?\n";
    cin >> duration; cin.ignore(MAX,'\n');
    cout << "How many friends do you plan to take with you?\n";
    cin >> friends; cin.ignore(MAX,'\n');
    cout << "What type of meal will you be looking forward to?\n";
    cin.get(temp,MAX); cin.ignore(MAX,'\n');

    meal = new char[strlen(temp) +1];
    strcpy(meal,temp);

    return 1;
}

//This displays the members of this class,
//the duration of the file and the size.
//Then treats the left display function like a wrapper
//going up the chain of inheritance.
int dining::display() const
{
    if (!duration || !friends || !meal)
        return 0;

    cout << "Duration: " << duration << " hours."
        << "\n# Friends: " << friends
        << "\nMeal: " << meal << endl;

    return 1;
}

/**********************************************************
 * zooing CLASS
 **********************************************************/

//Default Constructor
zooing::zooing() : duration(0.0f), friends(0), animal(NULL) {}

//Copy Constructor
zooing::zooing(const zooing & to_copy) : 
    task(to_copy), duration(to_copy.duration), friends(to_copy.friends)
{
    animal = new char[strlen(to_copy.animal) +1];
    strcpy(animal, to_copy.animal);
}


//This is the first function called from int_main.
//a zooing object is created from int_main,
//and it calls the left function,
//up the chain of inheritance from itself,
//which is the task_tree class.
//It collects the returned data only to make some
//fun numbers to "pretend" like a video was uploaded.
int zooing::read()
{
    char temp[MAX];

    cout << "How many hours will this activity take?\n";
    cin >> duration; cin.ignore(MAX,'\n');
    cout << "How many friends do you plan to take with you?\n";
    cin >> friends; cin.ignore(MAX,'\n');
    cout << "Write the animal noise you're interested in hearing!\n";
    cin.get(temp,MAX); cin.ignore(MAX,'\n');

    animal = new char[strlen(temp) +1];
    strcpy(animal,temp);


    return 1;
}


int zooing::display() const
{
    if (!duration || !friends || !animal)
        return 0;

    cout << "Duration: " << duration << " hours."
        << "\n# Friends: " << friends
        << "\nAnimal: " << animal << endl;

    return 1;
}

zooing::~zooing()
{
    if (animal)
        delete [] animal;
}


