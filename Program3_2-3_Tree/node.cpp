#include "node.h"
using namespace std;

//Will McIntosh 5-15-20

/**********************************************************
 * VEC CLASS
 **********************************************************/

//Default constructor
//The datas array (which is an array of base
//class pointers) get instantiated initially at 10.
//Then the temps points is used for temporary storage.
vec::vec() : cap(3)
{
    datas = new data * [cap];
    temps = new data * [cap];

    for (int i = 0; i < cap; ++i)
    {
        datas[i] = NULL;
        temps[i] = NULL;
    }
}

//Destructor
vec::~vec()
{
    for (int i = 0; i < cap; ++i)
    {
        if (datas[i])
        {
            delete datas[i];
            datas[i] = NULL;
        }
    }

    if (datas)
    {
        delete datas;
        datas = NULL;
    }

    for (int i = 0; i < cap; ++i)
    {
        if (temps[i])
        {
            delete temps[i];
            temps[i] = NULL;
        }
    }

    if (temps)
    {
        delete temps;
        temps = NULL;
    }
}

//This function is called by the node class
//It requests the type of source to be inserted be the user,
//so that way it know which data type to create, binding the type dynamically.
//Then stores informaion into it
int vec::insert_into_array(data *& in_data)
{
    //Incremented counter in recursive call
    int inc = 0;

    //Transfers most recently created data to vec's array in order of priority
    if (!data_to_array(in_data, inc = 0))
        cout << "Looks like something went wrong while inserting. Try again!\n";

    return 0;
}

//This function first takes into consideration,
//whether the list is empty first
//if so, then a new object is build from one derivatives
//calls the copy constructor
int vec::data_to_array(data *& in_data, int & inc)
{
    //Confirms that the search stays within bounds of the array
    if (inc >= cap)
        return 0;

    if ((!datas[inc]) || (strcmp(in_data->get_name(),datas[inc]->get_name()) <= 0))
    {
        shifty_shift_up(inc);

        //Copies over to the address and triggers the copy constructors
        datas[inc] = new data(*in_data);
        return 1;
    }

    return data_to_array(in_data, ++inc);
}

//This function moves everything in the array up one element,
//to the point "inc" passed from the calling function.
//Since I have no real way of reporting errors,
//or results from this source, this function
//has a return type of "void".
void vec::shifty_shift_up(int & inc)
{
    for (int i = cap-1; i > inc-1; --i)
       if (datas[i])
            datas[i+1] = datas[i];
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
//or results from this source, this function
//has a return type of "void".
void vec::shifty_shift_down(int & inc)
{
    for (int i = inc+1; i < cap-1; ++i)
    {
        for (int j = 0; j < cap; ++j)
            if (!temps[j])
                temps[j] = datas[i-1];

        datas[i-1] = datas[i];
    }
}

//For each node that matches the level number
//sent in by the user, this displays all
//elements in that array and returns the amount there.
//int vec::display_array(char * in_pri)
int vec::display_array()
{
    int count = 0;

    for (int i = 0; i < cap; ++i)
    {
        if (datas[i])
        {
            //cout << "Data [" << i+1 << "]:\n";
            if (display_element(*datas[i]))
                ++count;
            cout << endl;
        }
    }

    cout << "We found " << count << " pieces of content by that priority.\n";

    return count;
}

//The argument in some cases is simply passed on from other 
//functions which will ne
char vec::display_array_name()
{
    for (int i = 0; i < cap; ++i)
    {
        if (datas[i])
        {
            if (datas[i+1]) 
                cout << datas[i]->name::get_name() << ", ";
            else
                cout << datas[i]->name::get_name();
        }
    }

    return ' ';
}

int vec::display_array_pri()
{
    int count = 0;

    for (int i = 0; i < cap; ++i)
    {
        if (datas[i])
        {
            cout << datas[i]->data::get_pri();
            if (i+1 < cap && datas[i+1]) cout << ", ";
        }
    }

    return count;
}

//Am I right in thinkig I'm wanting to down cast
//the ACTUAL pointer that lives within Vec's array?
//Or does it make more sense to bring in a copy?
//Should I pass this pointer in by reference?
int vec::display_element(data in_data)
{
    for (int i = 0; i < 7; ++i)
        cout << in_data[i] << ' ';

    return 1;
}

int vec::display_element_name(data * in_data)
{
    if (in_data)
    {
        in_data->name::display();
        in_data->source::display();
        in_data->content::display();
        return 1;
    }

    return 0;
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
        if (datas[i])
        {
            cout << "We removed: ";
            datas[i]->name::display();
            delete datas[i];
            datas[i] = NULL;
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
        if (datas[i])
        {
            if (strcmp(in_name,datas[i]->get_name()) == 0)
            {
                shifty_shift_down(i);
                return 1;
            }
        }
    }

    return 0;
}

char * vec::get_pri(int index)
{
    //Later on when I implement the 2-3 tree,
    //this will have to do more than simply return element 0's info
    if (datas[index])
        return datas[index]->get_pri();

    return NULL;
}

//Takes the input and compares it with every element of that node's array
//if at least one match was found, 1 is returned. otherwise 0.
int vec::check_pri(char * my_pri)
{
    for (int i = 0; i < cap; ++i)
        if (datas[i])
            if (datas[i]->check_pri(my_pri))
                return 1;

    return 0;
}

data *& vec::get_data(int index)
{
    //if (datas[index])
        return datas[index];
}

//This function simply looks for any null elements,
//and pushes everything close to the 0 element.
int vec::the_housemaid_protocol(int index_1, int index_2, int index_3)
{
    if (!index_1)
    {
        if (datas[0])
        {
            delete datas[0];
            datas[0] = NULL;
        }
    }
    if (!index_2)
    {
        if (datas[1])
        {
            delete datas[1];
            datas[1] = NULL;
        }
    }
    if (!index_3)
    {
        if (datas[2])
        {
            delete datas[2];
            datas[2] = NULL;
        }
    }

    if (!datas[0] && !datas[2])
        datas[0] = datas[1];

    if (!datas[0] && !datas[1])
        datas[0] = datas[2];

    //At this point, data 0 should be the only one
    if (datas[1]) datas[1] = NULL;
    if (datas[2]) datas[2] = NULL;

    return 1;
}


/**********************************************************
 * NODE CLASS
 **********************************************************/

//Default constructor
node::node() : parent(0), left(0), right(0), real_middle(0), temp_middle(0), ancestor_path(NULL) {}

//Copy constructor
//Calls the parent copy constructor to begin the derivation copy process
node::node(const node & in_root) :
    parent(in_root.parent), left(in_root.left),
    right(in_root.right), real_middle(in_root.real_middle), temp_middle(in_root.temp_middle)
{
    if (in_root.ancestor_path)
    {
        ancestor_path = new char[strlen(in_root.ancestor_path) +1];
        strcpy(ancestor_path, in_root.ancestor_path);
    }
}

//Called from Tree as the user wants to display
//all nodes that match a particular name search.
int node::compare_entire_name(char * in_name)
{
    int count = 0;

    for (int i = 0; i < cap; ++i)
        if (datas[i])
            if (strcmp(datas[i]->get_name(),in_name) == 0)
                if (display_element(*datas[i]))
                    ++count;

    return count;
}

//Called from Tree as the user wants to display
//all nodes that match a particular name search.
//This examines the first three elements of the search,
//incrementally, one at a time.
int node::compare_partial_name(char * in_name)
{
    int count = 0;

    for (int i = 0; i < cap; ++i)
        if (datas[i])
            if (datas[i]->name::compare_name_by_letter(0,in_name[0]))
                if (datas[i]->name::compare_name_by_letter(1,in_name[1]))
                    if (datas[i]->name::compare_name_by_letter(2,in_name[2]))
                        if (display_element(*datas[i]))
                            ++count;

    return count;
}

//This are wrapper functions,
//I mean, they're IMHO getters,
//but this seems to be common practice
//for class nodes as opposed to structs.
node *& node::go_left()
{
    return left;
}

node *& node::go_real_middle()
{
    return real_middle;
}

node *& node::go_temp_middle()
{
    return temp_middle;
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

void node::connect_real_middle(node * connection)
{
    this->real_middle = connection;
}

void node::connect_temp_middle(node * connection)
{
    this->temp_middle = connection;
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
 * CONTENT CLASS
 **********************************************************/

//Default Constructor
content::content() : source() {}

//Copy Constructors
//Makes a deep copy of the char stars dynamic names
//inside of the private members of the class.
//otherwise it would just be a shallow copy.
content::content(const content & to_copy) : source(to_copy)
{
    date = to_copy.date;
    time = to_copy.time;
}

//Destructor
content::~content() {}

//This function is responsible for taking in the 
//information written by the user
//and they storing that into the specific members
//of the object for each individual content.
//That way, instead of reading in from int main or
//something and then bringing everything as arguments,
//this way, each class actually manages its own content.
int content::read_from_user()
{
    cout << "Please enter the date and time of the content:\n";
    cin >> date; cin.ignore(MAX, '\n');
    cin >> time; cin.ignore(MAX, '\n');

    return 1;
}

int content::read_from_file(char * word1, char * word2)
{
    if (word1) date = word1;
    if (word2) time = word2;

    return 1;
}

int content::display() const
{
    cout << "Due Date:\t" << date << endl
        << "Due Time:\t" << time << endl;

    return 1;
}

/**********************************************************
 * tree CLASS
 **********************************************************/

//Default Constructor
tree::tree() : root(0) {}

//Copies the entire data structure
int tree::copy_all_nodes(node *& root, node * in_root)
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
tree::~tree()
{
    destroy_all(root);

    if (root)
    {
        delete root;
        root = NULL;
    }
}

int tree::display_by_name()
{
    char temp[MAX];

    cout << "Please enter the name you're interested in: ";
    cin.get(temp,MAX); cin.ignore(MAX,'\n');

    char * in_name = new char[strlen(temp) +1];
    strcpy(in_name, temp);
    
    int perfect_count = display_by_perfect_name(root, in_name);

    cout << "We've discovered " << perfect_count << " pieces of content by the precise wording of that name.\n";

    if (!perfect_count)
    {
        if (strlen(temp) > 3)
        {
            int partial_count = display_by_partial_name(root, in_name);

            if (partial_count)
                cout << "\nWe've also discovered " << partial_count
                    << " pieces of content by partial wording of that name.\n";
        }
    }


    if (in_name)
    {
        delete in_name;
        in_name = NULL;
    }

    return 1;
}

int tree::display_by_partial_name(node * root, char * in_name)
{
    int count = 0;

    if (!root)
        return 0;

    if (root->compare_partial_name(in_name))
        ++count;

    count += display_by_partial_name(root->go_left(), in_name);
    count += display_by_partial_name(root->go_real_middle(), in_name);
    count += display_by_partial_name(root->go_right(), in_name);

    return count;
}

int tree::display_by_perfect_name(node * root, char * in_name)
{
    int count = 0;

    if (!root)
        return 0;

    if (root->compare_entire_name(in_name))
        ++count;

    count += display_by_perfect_name(root->go_left(), in_name);
    count += display_by_perfect_name(root->go_real_middle(), in_name);
    count += display_by_perfect_name(root->go_right(), in_name);

    return count;
}

//Returns the amount of data
int tree::count()
{
    return count(root);
}

int tree::count(node * root)
{
    if (!root)
        return 0;

    int node_count = count(root->go_left());

    ++node_count;

    node_count += count(root->go_right());

    return node_count;
}

int tree::height()
{
    return height(root);
}

//I chose to not add a middle pointer,
//Since there'd never be a scenario where
//the middle pointer exists and the other two dont.
int tree::height(node * root)
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
int tree::destroy_all(node *& root)
{
    if (!root)
        return 0;

    int count = destroy_all(root->go_left()) +1;
    count += destroy_all(root->go_real_middle()) +1;
    count += destroy_all(root->go_right()) +1;

    root->delete_array();

    delete root;
    root = NULL;

    return count;
}

//Since tree manages the DLL list of nodes,
//This function is an
//insert Function which places a new node,
//or determines which node to place this in.
//Sticks user in a loop if it's out of range.
//The in_file is just created in this case,
//to satisfy the arguments for when its needed elsewhere.
int tree::insert_from_user()
{
    int response = 0;
    data * in_data = new data;

    in_data->name::read_from_user();
    in_data->source::read_from_user();
    in_data->content::read_from_user();
    in_data->data::read_from_user();
    
    if (insert_into_tree(root, in_data))
        response = 1;

    if (in_data)
    {
        delete in_data;    
        in_data = NULL;
    }

    return response;
}

//A temporary data object is made
//so that all the information can be stored into it
//then it passed in as an argument to be stored
//when insterted into the tree data structure.
//The two String classes are used to store
//the information into;
int tree::grab_news()
{
    int count = 0;
    char temp1[MAX];
    char temp2[MAX];
    data * in_data = new data;
    String string1;
    String string2;
    ifstream in_file;

    in_file.open("news.txt");

    if (!in_file) return 0;

    //Primes the pump
    in_file.peek();

    while(in_file && !in_file.eof()) 
    {
        //Name grabbed from file into temp static
        in_file.get(temp1,MAX,'|'); in_file.ignore(MAX,'|');

        //Temp1 static transferred to dynamic char pointer
        char * word1 = new char[strlen(temp1) +1];
        strcpy(word1, temp1);

        //Word1 transferred to name String
        in_data->name::read_from_file(word1);
        if (word1) { delete [] word1; word1 = NULL; }

        //Source type and Link get stored into temps
        in_file.get(temp1,MAX,'|'); in_file.ignore(MAX,'|');
        in_file.get(temp2,MAX,'|'); in_file.ignore(MAX,'|');

        //Temp1 and Temp2 statics transferred to dynamic char pointers
        word1 = new char[strlen(temp1) +1];
        strcpy(word1, temp1);
        char * word2 = new char[strlen(temp2) +1];
        strcpy(word2, temp2);

        in_data->source::read_from_file(word1, word2);
        if (word1) { delete [] word1; word1 = NULL; }
        if (word2) { delete [] word2; word2 = NULL; }

        //Date and Time get stored into temps
        in_file.get(temp1,MAX,'|'); in_file.ignore(MAX,'|');
        in_file.get(temp2,MAX,'|'); in_file.ignore(MAX,'|');

        //Date and Time statics transferred to dynamic char pointers
        word1 = new char[strlen(temp1) +1];
        strcpy(word1, temp1);
        word2 = new char[strlen(temp2) +1];
        strcpy(word2, temp2);

        in_data->content::read_from_file(word1, word2);
        if (word1) { delete [] word1; word1 = NULL; }
        if (word2) { delete [] word2; word2 = NULL; }

        //body_text and Priority get stored into temps
        in_file.get(temp1,MAX,'|'); in_file.ignore(MAX,'|');
        in_file.get(temp2,MAX,'\n'); in_file.ignore(MAX,'\n');

        //body_text and Priority statics transferred to dynamic char pointers
        word1 = new char[strlen(temp1) +1];
        strcpy(word1, temp1);
        word2 = new char[strlen(temp2) +1];
        strcpy(word2, temp2);

        in_data->data::read_from_file(word1, word2);
        if (word1) { delete [] word1; word1 = NULL; }
        if (word2) { delete [] word2; word2 = NULL; }

        if (insert_into_tree(root, in_data))
            ++count;

        in_file.peek();
    }

    cout << "We inserted " << count << " piecs of new content.\n";

    if (in_data) { delete in_data; in_data = NULL; }

    return 1;
}

//A temporary data object is made
//so that all the information can be stored into it
//then it passed in as an argument to be stored
//when insterted into the tree data structure.
//The two String classes are used to store
//the information into;
int tree::grab_emails()
{
    int count = 0;
    char temp1[MAX];
    char temp2[MAX];
    data * in_data = new data;
    String string1;
    String string2;
    ifstream in_file;

    in_file.open("emails.txt");

    if (!in_file) return 0;

    //Primes the pump
    in_file.peek();

    while(in_file && !in_file.eof()) 
    {
        //Name grabbed from file into temp static
        in_file.get(temp1,MAX,'|'); in_file.ignore(MAX,'|');

        //Temp1 static transferred to dynamic char pointer
        char * word1 = new char[strlen(temp1) +1];
        strcpy(word1, temp1);

        //Word1 transferred to name String
        in_data->name::read_from_file(word1);
        if (word1) { delete [] word1; word1 = NULL; }

        //Source type and Link get stored into temps
        in_file.get(temp1,MAX,'|'); in_file.ignore(MAX,'|');
        in_file.get(temp2,MAX,'|'); in_file.ignore(MAX,'|');

        //Temp1 and Temp2 statics transferred to dynamic char pointers
        word1 = new char[strlen(temp1) +1];
        strcpy(word1, temp1);
        char * word2 = new char[strlen(temp2) +1];
        strcpy(word2, temp2);

        in_data->source::read_from_file(word1, word2);
        if (word1) { delete [] word1; word1 = NULL; }
        if (word2) { delete [] word2; word2 = NULL; }

        //Date and Time get stored into temps
        in_file.get(temp1,MAX,'|'); in_file.ignore(MAX,'|');
        in_file.get(temp2,MAX,'|'); in_file.ignore(MAX,'|');

        //Date and Time statics transferred to dynamic char pointers
        word1 = new char[strlen(temp1) +1];
        strcpy(word1, temp1);
        word2 = new char[strlen(temp2) +1];
        strcpy(word2, temp2);

        in_data->content::read_from_file(word1, word2);
        if (word1) { delete [] word1; word1 = NULL; }
        if (word2) { delete [] word2; word2 = NULL; }

        //body_text and Priority get stored into temps
        in_file.get(temp1,MAX,'|'); in_file.ignore(MAX,'|');
        in_file.get(temp2,MAX,'\n'); in_file.ignore(MAX,'\n');

        //body_text and Priority statics transferred to dynamic char pointers
        word1 = new char[strlen(temp1) +1];
        strcpy(word1, temp1);
        word2 = new char[strlen(temp2) +1];
        strcpy(word2, temp2);

        in_data->data::read_from_file(word1, word2);
        if (word1) { delete [] word1; word1 = NULL; }
        if (word2) { delete [] word2; word2 = NULL; }

        if (insert_into_tree(root, in_data))
            ++count;

        in_file.peek();
    }

    cout << "We inserted " << count << " piecs of new content.\n";

    if (in_data)
    {
        delete in_data;    
        in_data = NULL;
    }

    return 1;
}

//A temporary data object is made
//so that all the information can be stored into it
//then it passed in as an argument to be stored
//when insterted into the tree data structure.
//The two String classes are used to store
//the information into;
int tree::grab_meetings()
{
    int count = 0;
    char temp1[MAX];
    char temp2[MAX];
    data * in_data = new data;
    String string1;
    String string2;
    ifstream in_file;

    in_file.open("meetings.txt");

    if (!in_file) return 0;

    //Primes the pump
    in_file.peek();

    while(in_file && !in_file.eof()) 
    {
        //Name grabbed from file into temp static
        in_file.get(temp1,MAX,'|'); in_file.ignore(MAX,'|');

        //Temp1 static transferred to dynamic char pointer
        char * word1 = new char[strlen(temp1) +1];
        strcpy(word1, temp1);

        //Word1 transferred to name String
        in_data->name::read_from_file(word1);
        if (word1) { delete [] word1; word1 = NULL; }

        //Source type and Link get stored into temps
        in_file.get(temp1,MAX,'|'); in_file.ignore(MAX,'|');
        in_file.get(temp2,MAX,'|'); in_file.ignore(MAX,'|');

        //Temp1 and Temp2 statics transferred to dynamic char pointers
        word1 = new char[strlen(temp1) +1];
        strcpy(word1, temp1);
        char * word2 = new char[strlen(temp2) +1];
        strcpy(word2, temp2);

        in_data->source::read_from_file(word1, word2);
        if (word1) { delete [] word1; word1 = NULL; }
        if (word2) { delete [] word2; word2 = NULL; }

        //Date and Time get stored into temps
        in_file.get(temp1,MAX,'|'); in_file.ignore(MAX,'|');
        in_file.get(temp2,MAX,'|'); in_file.ignore(MAX,'|');

        //Date and Time statics transferred to dynamic char pointers
        word1 = new char[strlen(temp1) +1];
        strcpy(word1, temp1);
        word2 = new char[strlen(temp2) +1];
        strcpy(word2, temp2);

        in_data->content::read_from_file(word1, word2);
        if (word1) { delete [] word1; word1 = NULL; }
        if (word2) { delete [] word2; word2 = NULL; }

        //body_text and Priority get stored into temps
        in_file.get(temp1,MAX,'|'); in_file.ignore(MAX,'|');
        in_file.get(temp2,MAX,'\n'); in_file.ignore(MAX,'\n');

        //body_text and Priority statics transferred to dynamic char pointers
        word1 = new char[strlen(temp1) +1];
        strcpy(word1, temp1);
        word2 = new char[strlen(temp2) +1];
        strcpy(word2, temp2);

        in_data->data::read_from_file(word1, word2);
        if (word1) { delete [] word1; word1 = NULL; }
        if (word2) { delete [] word2; word2 = NULL; }

        if (insert_into_tree(root, in_data))
            ++count;

        in_file.peek();
    }

    cout << "We inserted " << count << " piecs of new content.\n";

    if (in_data)
    {
        delete in_data;    
        in_data = NULL;
    }

    return 1;
}
//This function is responsible for
//checking if the level node already exists.
//If the list is empty, then a new node is created.
//If the level node requested exists,
//then that node's Vec class inserts a new data.
//Otherwise call the recursive function.
//Since I checked above that the input is between
//1 and 5, I know that this will find the node
//it's looking for.
//This function then calls Vec's insert,
//which makes a new array sized right and sorted.
//This is the only time we're going to be making
//a new node in insertion directly like this.
//The other times are going to be through a node split.
//Also, if root doesn't have a left or a right node,
//then just insert here.
//Otherwise, resuse through the tree to find a node.
int tree::insert_into_tree(node *& root, data *& in_data)
{
    //[1]Only triggers on the initial call
    if (!root)
    {
        node * temp = new node;

        temp->vec::insert_into_array(in_data);
        temp->connect_left(0);
        temp->connect_right(0);

        root = temp;
        return the_lumberjack_protocol(root);
    }
    //[2]Only triggers when the first node has no children
    else if (!root->go_left() && !root->go_right())
    {
        root->vec::insert_into_array(in_data);
        return the_lumberjack_protocol(root);
    }

    look_for_leafs(root, in_data);

    return the_lumberjack_protocol(root);
}

//If we are here, then that means the list isn't empty, 
//and we have some nodes on either the left or the right of the root.
//We still need to insert at a leaf.
//Looks to a value, right first.
//If the value being inserted is greater than the last vec element,
//Then check if there's another node to down to.
//if not, insert the data here.
int tree::look_for_leafs(node *& root, data *& in_data)
{
    //Does element 0 exist?
    if (root->vec::get_pri(0))
    {
        //Are you less than or equal to element 0?
        if (strcmp(in_data->get_pri(),root->vec::get_pri(0)) <= 0)
        {
            //Okay, you're less than element 0. Is there a left node?
            if (!root->go_left())
            {
                //If so, insert here...
                root->vec::insert_into_array(in_data);
                return 1;
            }
            //...otherwise go to that left node.
            else
            look_for_leafs(root->go_left(), in_data);
            root->go_left()->connect_parent(root);
            return 1;
        }
        //Are you greater than element 0?
        else if (strcmp(in_data->get_pri(),root->vec::get_pri(0)) > 0)
        {
            //Does element 1 exist?
            if (root->vec::get_pri(1))
            {
                //Are you larger than it?
                if (strcmp(in_data->get_pri(),root->vec::get_pri(1)) > 0)
                {
                    //Okay, you're larger than element 1. Does a right node exist?
                    if (!root->go_right())
                    {
                        //No. Insert here...
                        root->vec::insert_into_array(in_data);
                        return 1;
                    }

                    //...otherwise go to that right node.
                    look_for_leafs(root->go_right(), in_data);
                    root->go_right()->connect_parent(root);
                    return 1;
                }
                //You're smaller than element 1 and greater than element 0, okay. Is there a middle node?
                else if (root->go_real_middle())
                {
                    //If there is, then go to that middle node.
                    look_for_leafs(root->go_real_middle(), in_data);
                    root->go_real_middle()->connect_parent(root);
                    return 1;
                }
                //You're smaller than element 1 and greater than element 0 and no middle node. Right node?
                else if (!root->go_right())
                {
                    //No. Insert here...
                    root->vec::insert_into_array(in_data);
                    return 1;
                }

                //...otherwise call this function again.
                look_for_leafs(root->go_right(), in_data);
                root->go_right()->connect_parent(root);
                return 1;
            }
            //No element 1 but you're larger than element 0? Okay.
            else
            {
                //If a right node doesn't exist, insert here...
                if (!root->go_right())
                {
                    root->vec::insert_into_array(in_data);
                    return 1;
                }

                //...otherwise call this function again.
                look_for_leafs(root->go_right(), in_data);
                
                root->go_right()->connect_parent(root);
                return 1;
            }
        }
    }
    //Element 0 is null? Oh that's bad. This shouldn't happen.
    //Spit out an error and get out of here.

    cerr << "There was an error when trying to insert: " << in_data->get_pri()
        << "into the array containing: " << root->vec::display_array_name() << endl
        << "Please check vec::the_housemaid_protocol() to confirm it's shifting everything down.\n";
    return 0;
}

//This function looks for every node in the tree
//to see if there are any nodes that need to be split,
//until there are no more nodes that need to be split.
int tree::the_lumberjack_protocol(node *& root)
{
    if (!root)
        return 0;

    the_lumberjack_protocol(root->go_left());
    the_lumberjack_protocol(root->go_real_middle());
    the_lumberjack_protocol(root->go_right());

    //If the last element is being used... CHOP!
    if (root->vec::get_pri(2))
    {
        //If we have a fullhouse, go clean that shtuff up!
        //This is when all pointers and elements are used in a single node.
        if (the_fullhouse_protocol())
            return root->vec::the_housemaid_protocol(0, 1, 0);

        //cerr << "\nHere is the current state of root: " << root->vec::display_array_name() << endl;
        
        //If this root's parent pointer is null,
        //This one becomes the new parent pointer.
        //Creates two new nodes to the left and right pointers.
        if (!root->go_parent())
        {
            node * temp_left = new node;

            temp_left->vec::insert_into_array(root->vec::get_data(0));
            temp_left->connect_left(0);
            temp_left->connect_right(0);
            temp_left->connect_parent(this->root);

            root->connect_left(temp_left);

            node * temp_right = new node;

            temp_right->vec::insert_into_array(root->vec::get_data(2));
            temp_right->connect_left(0);
            temp_right->connect_right(0);
            temp_right->connect_parent(this->root);

            root->connect_right(temp_right);

            //Sets the data from element 1 into element 0
            //Sets elements 1 and 2 to NULL;
            return root->vec::the_housemaid_protocol(0, 1, 0);
        }
        //You have a parent! Excellent. I'm so happy for you. Hurray you.
        else
        {
            //cerr << "We are trying to give: " << root->vec::get_data(1)->get_pri()
            //    << " to the parent: " << root->go_parent()->vec::display_array_name() << endl;

            //Let's give your parent your element 1
            root->go_parent()->vec::insert_into_array(root->vec::get_data(1));

            //Let's talk about your relationship with your parent. Are you right, mid or left child?
            if (root->go_parent()->go_right() == root)
            {
                //[Scenario 1]You're a right child. Good for you. Does your parent have a middle child?
                if (!root->go_parent()->go_real_middle())
                {
                    //No middle kid? Okay.
                    //Lets tell your parent to make a new node at real_middle
                    //and store your element 0 in it
                    node * temp = new node;

                    temp->vec::insert_into_array(root->vec::get_data(0));
                    temp->connect_left(0);
                    temp->connect_right(0);
                    temp->connect_parent(root->go_parent());

                    root->go_parent()->connect_real_middle(temp);

                    //Now let's clean you up
                    return root->vec::the_housemaid_protocol(0, 0, 1);
                }
                //[Scenario 4]You're a right child, and your parent does have a middle.
                else
                {
                    //lets tell your parent to make a new node at temp_middle
                    //and store your element 0 in it
                    node * temp = new node;

                    temp->vec::insert_into_array(root->vec::get_data(0));
                    temp->connect_left(0);
                    temp->connect_right(0);
                    temp->connect_parent(root->go_parent());

                    root->go_parent()->connect_temp_middle(temp);

                    //now let's clean you up
                    return root->vec::the_housemaid_protocol(0, 0, 1);
                }
            }
            //[Scenario 5]You're a middle child. Wow, sucks to be you.
            else if (root->go_parent()->go_real_middle() == root)
            {
                //lets tell your parent to make a new node at temp_middle
                //and store your element 2 in it
                node * temp = new node;

                temp->vec::insert_into_array(root->vec::get_data(2));
                temp->connect_left(0);
                temp->connect_right(0);
                temp->connect_parent(root->go_parent());

                root->go_parent()->connect_temp_middle(temp);

                //now let's clean you up
                return root->vec::the_housemaid_protocol(1, 0, 0);
            }
            //You're a left child
            else
            {
                //[Scenario 2]You're a left child. Good for you. Does your parent have a middle child?
                if (!root->go_parent()->go_real_middle())
                {
                    //No middle kid? Okay.
                    //Lets tell your parent to make a new node at real_middle
                    //and store your element 2 in it
                    node * temp = new node;

                    temp->vec::insert_into_array(root->vec::get_data(2));
                    temp->connect_left(0);
                    temp->connect_right(0);
                    temp->connect_parent(root->go_parent());

                    root->go_parent()->connect_real_middle(temp);

                    //Now let's clean you up
                    return root->vec::the_housemaid_protocol(1, 0, 0);
                }
                //[Scenario 3]You're a left child, and your parent does have a middle.
                else
                {
                    //The below cumbersome code makes sure that
                    //the higher node is on the parent's temp_middle
                    //and the lesser node is on the parent's real_middle.
                    //This makes for a perfect setup for the FullHouse function.
                    
                    //Creates a temp node and place parent's real_middle info inside of it.
                    node * temp_temp_middle = new node;

                    temp_temp_middle->vec::insert_into_array(root->go_parent()->go_real_middle()->vec::get_data(0));
                    temp_temp_middle->connect_left(0);
                    temp_temp_middle->connect_right(0);
                    temp_temp_middle->connect_parent(root->go_parent());

                    root->go_parent()->connect_temp_middle(temp_temp_middle);

                    //Clear out whatever is in the parent's real_middle
                    if (root->go_parent()->go_real_middle())
                    {
                        delete root->go_parent()->go_real_middle();
                        root->go_parent()->connect_real_middle(0);
                    }

                    //Creates a temp node for the parent's real middle and stores it in there
                    node * temp_real_middle = new node;

                    temp_real_middle->vec::insert_into_array(root->vec::get_data(2));
                    temp_real_middle->connect_left(0);
                    temp_real_middle->connect_right(0);
                    temp_real_middle->connect_parent(root->go_parent());

                    root->go_parent()->connect_temp_middle(temp_real_middle);

                    //now let's clean you up
                    return root->vec::the_housemaid_protocol(1, 0, 0);
                }
            }
        }
    }

    return 1;
}

//Display Wrapper
int tree::display_everything() 
{
    int count = display(root);

    cout << "There are " << count << " datas currently.\n\n";

    return count;
}

//If all elements and all pointers are not null,
//clean up everything, otherwise return 0;
int tree::the_fullhouse_protocol()
{
    if (root->vec::get_pri(0) && root->vec::get_pri(1) && root->vec::get_pri(2)
        && root->go_left() && root->go_real_middle()
        && root->go_temp_middle() && root->go_right())
        {
            //if all elements and all pointers are used,
            //This large chunk takes care of the left side.
            node * temp_left_left_child = new node;

            //cerr << "\n\nWe're trying to insert " << root->go_left()->vec::get_data(0)
            //    << " into temp_left_left_child\n";

            temp_left_left_child->vec::insert_into_array(root->go_left()->vec::get_data(0));
            temp_left_left_child->connect_left(0);
            temp_left_left_child->connect_right(0);

            node * temp_left_right_child = new node;

            //cerr << "\n\nWe're trying to insert " << root->go_real_middle()->vec::get_data(0)
            //    << " into temp_left_right_child\n";

            temp_left_right_child->vec::insert_into_array(root->go_real_middle()->vec::get_data(0));
            temp_left_right_child->connect_left(0);
            temp_left_right_child->connect_right(0);

            node * temp_parent_left = new node;

            //cerr << "\n\nWe're trying to insert " << root->get_data(0)
            //    << " into temp_parent_left\n";

            temp_parent_left->vec::insert_into_array(root->vec::get_data(0));
            temp_parent_left->connect_left(temp_left_left_child);
            temp_parent_left->connect_right(temp_left_right_child);

            temp_parent_left->connect_parent(this->root);
            temp_left_left_child->connect_parent(temp_parent_left);
            temp_left_right_child->connect_parent(temp_parent_left);

            //This large chunk takes care of the right side.
            node * temp_right_right_child = new node;

            //cerr << "\n\nWe're trying to insert " << root->go_right()->vec::get_data(0)
            //    << " into temp_right_right_child\n";

            temp_right_right_child->vec::insert_into_array(root->go_right()->vec::get_data(0));
            temp_right_right_child->connect_left(0);
            temp_right_right_child->connect_right(0);

            node * temp_right_left_child = new node;

            //cerr << "\n\nWe're trying to insert " << root->go_temp_middle()->vec::get_data(0)
            //    << " into temp_right_left_child\n";

            temp_right_left_child->vec::insert_into_array(root->go_temp_middle()->vec::get_data(0));
            temp_right_left_child->connect_left(0);
            temp_right_left_child->connect_right(0);

            node * temp_parent_right = new node;

            //cerr << "\n\nWe're trying to insert " << root->vec::get_data(2)
            //    << " into temp_parent_right\n";

            temp_parent_right->vec::insert_into_array(root->vec::get_data(2));
            temp_parent_right->connect_right(temp_right_right_child);
            temp_parent_right->connect_left(temp_right_left_child);

            temp_parent_right->connect_parent(this->root);
            temp_right_right_child->connect_parent(temp_parent_right);
            temp_right_left_child->connect_parent(temp_parent_right);

            //GEN-NODE-CIDE!
            if (root->go_right())
            {
                delete root->go_right();
                root->connect_right(0);
            }
            if (root->go_left())
            {
                delete root->go_left();
                root->connect_left(0);
            }
            if (root->go_real_middle())
            {
                delete root->go_real_middle();
                root->connect_real_middle(0);
            }
            if (root->go_temp_middle())
            {
                delete root->go_temp_middle();
                root->connect_temp_middle(0);
            }

            //Connect up root's left and right to the new parent temps
            root->connect_left(temp_parent_left);
            root->connect_right(temp_parent_right);


            //Sets the data from element 1 into element 0
            //Sets elements 1 and 2 to NULL;
            
            //root->vec::the_housemaid_protocol(0, 1, 0);

            return 1;
        }

    return 0;
}


//Recursive display all function
int tree::display(node * root)
{
    if (!root)
        return 0;

    int count = display(root->go_left());

    if (root->vec::get_pri(0))
    {
        root->vec::get_data(0)->name::display();
        root->vec::get_data(0)->source::display();
        root->vec::get_data(0)->content::display();
        root->vec::get_data(0)->display();
        ++count;
    }
        
    count += display(root->go_real_middle());

    if (root->vec::get_pri(1))
    {
        root->vec::get_data(1)->name::display();
        root->vec::get_data(1)->source::display();
        root->vec::get_data(1)->content::display();
        root->vec::get_data(1)->display();
        ++count;
    }

    count += display(root->go_right());

    return count;
}

//This is the function that's called from Int main.
//It's job is to search for a specific name
//that will be typed in from the user
//and then checked to see if it exists.
int tree::single_removal()
{
    char user_input[MAX];
    int killed = 0;

    cout << "Which data name would you like to remove? ";
    cin.get(user_input,MAX); cin.ignore(MAX,'\n');

    killed = remove_by_name(root, user_input);

    cout << "We removed " << killed << " datas.\n";

    return 0;
}

//This function looks for the name entered in from the user
//and check to see if it exists within the list.
//if so, the left function kills it and the total is returned.
int tree::remove_by_name(node *& root, char * user_input)
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
int tree::display_by_priority()
{
    int pri = 0;
    char temp_pri[MAX];

    cout << "Please enter the priority you're interested in (1-100): ";
    cin.get(temp_pri,MAX); cin.ignore(MAX,'\n');

    char * in_pri = new char[strlen(temp_pri) +1];
    strcpy(in_pri, temp_pri);

    if (in_pri)
        display_by_priority(root, in_pri);

    //If there isnt' any contents of the array
    if (pri == -1)
    {
        cout << "Looks like that priority doesn't exist in the list.\n";
        return 0;
    }

    if (in_pri)
    {
        delete [] in_pri;
        in_pri = NULL;
    }

    return 1;
}

//Takes the requests priority number as an argument
//Checks each node witin the tree to see if there's a match
int tree::display_by_priority(node * root, char * in_pri)
{
    if (!root)
        return 0;

    //if a match was found, display contents and returns 1;
    if (root->vec::check_pri(in_pri))
        if (root->vec::display_array())
            return 1;

    display_by_priority(root->go_left(), in_pri);
    display_by_priority(root->go_real_middle(), in_pri);
    display_by_priority(root->go_right(), in_pri);

    return 1;
}

/**********************************************************
 * DATA CLASS
 **********************************************************/

//Default Constructor
data::data() : content() {}

//Copy Constructor
data::data(const data & to_copy) : content(to_copy)
{
    body_text = to_copy.body_text;
    priority = to_copy.priority;
}

//Destructor
data::~data() {}

//Practice using the operator overload for the subscript
//or array operator.
//This is where the subscript (array) operator's are overloaded.
//They return the specifically desired
String & data::operator [] (int index)
{
    if (index == 0) return a_name;
    if (index == 1) return a_source;
    if (index == 2) return an_address.get_address();
    if (index == 3) return date;
    if (index == 4) return time;
    if (index == 5) return priority;
    if (index == 6) return body_text;

    return a_name;
}

//This is the first function called from int_main.
//a data object is created from int_main,
//and it calls the left function,
//up the chain of inheritance from itself,
//which is the tree class.
//It collects the returned data only to make some
//fun numbers to "pretend" like a video was uploaded.
int data::read_from_user()
{
    cout << "What's the first body text of this new content?\n";
    cin >> body_text; cin.ignore(MAX,'\n');

    cout << "What's the priority of this data? How important is it? (1-100): ";
    cin >> priority; cin.ignore(MAX,'\n');

    return 1;
}

//Transfers information from the string class in
//This is used to store information into 
//a temporary data object, then that object
//is tossed in as the argument to kickstart
//the copy constructors all the way up the hierarchy,
//but before that can happen the temp has to be made.
int data::read_from_file(char * word1, char * word2)
{
    if (word1) body_text = word1;
    if (word2) priority = word2;

    return 1;
}

//This displays the members of this class,
//Then treats the left display function like a wrapper
//going up the chain of inheritance.
int data::display() const
{
    cout << "Priority:\t" << priority << endl;
    cout << "Body Text:\t" << body_text << endl;

    return 1;
}

//Compares priortiy
int data::check_pri(char * my_pri)
{
    if (strcmp(priority.get_str(), my_pri) == 0)
        return 1;

    return 0;
}

//Getter used to get the priortiy
char * data::get_pri()
{
    return priority.get_str();
}





