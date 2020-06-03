#include <iostream>
#include <cctype>
#include <cstring>
#include <cmath>

//Used for cin functions.
const int MAX = 100;

class name
{
    public:
        name();
        name(const name & to_copy);
        int read();
        char * get_name();
        void display() const;
        ~name();

    protected:
        char * a_name;
};

//This class comes from the approved activity class,
//but it is not derived.
//The approved activity contains an object of this class.
//This class houses the address the activity is being held at.
class address
{
    public:
        address();
        address(const address & to_copy);
        int read();
        int display() const;
        ~address();

    protected:
        char * street;
        char * zip;
};

//This is more for the generic activity,
//before it is considered approved by the PSU board
class activity : public name
{
    public:
        activity();
        activity(const activity & to_copy); 
        int display() const;
        int read();
    protected:
        address an_address;
        class task_tree * my_task_tree;
};


