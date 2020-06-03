#include "activity.h"
using namespace std;

//Global Function for Client
bool user_confirmation()
{
    char user_input = '\0';

    cout << "Would you like to do this again (Y/N)? ";
    cin.get(user_input); cin.ignore(3000,'\n');

    if ('Y' == toupper(user_input))
        return true;

    return false;
}


/**********************************************************
 * NAME CLASS
**********************************************************/
 
//Default Constructor
name::name() : a_name(NULL) {}

//Copy Constructor
name::name(const name & to_copy)
{
    if (to_copy.a_name)
    {
        a_name = new char[strlen(to_copy.a_name) +1];
        strcpy(a_name, to_copy.a_name);
    }
    else
        a_name = NULL;
}

name::~name()
{
    if(a_name)
        delete [] a_name;
}

char * name::get_name()
{
    if (a_name)
        return a_name;
    else return NULL;
}

int name::read()
{
    cout << "Please enter the name of activity:\n";
    char temp[MAX];

    cin.get(temp, MAX,'\n'); cin.ignore(MAX, '\n');

    a_name = new char[strlen(temp) +1];
    strcpy(a_name, temp);

    return strlen(a_name);
}

//This simply displays the single private member
//Since there's no result from this function,
//I simply set it as a return type of void;
void name::display() const
{
    if (a_name)
        cout << a_name << endl;
    else return;
}

/**********************************************************
 * ACTIVITY CLASS
**********************************************************/

//Default constructors
activity::activity() {}

//Invokes the copy constructo for Address that I
// created earlier which does a deep copy.
activity::activity(const activity & to_copy) :
    name(to_copy), an_address(to_copy.an_address) {}

int activity::display() const
{
    if (a_name)
        cout << "File name:\t" << a_name << endl;

    if (an_address.display())
        return 1;

    return 0;
}

//This function simply tells the address class
//to accept input from the user and edit
int activity::read()
{
    return an_address.read();
}

/**********************************************************
 * ADDRESS CLASS
**********************************************************/

//Default Constructor
address::address() : street(NULL), zip(NULL) {}

//Copies the class to the new class object.
address::address(const address & to_copy)
{
    if (to_copy.street)
    {
        street = new char[strlen(to_copy.street) +1];
        strcpy(street, to_copy.street);
    }
    else
        street = NULL;

    if (to_copy.zip)
    {
        zip = new char[strlen(to_copy.zip) +1];
        strcpy(zip, to_copy.zip);
    }
    else
        zip = NULL;
}

address::~address()
{
    if(street)
        delete [] street;
    if(zip)
        delete [] zip;
}

//This function is called from int_main(),
// it collects the information from the user,
// and stores that into the temp static char array.
int address::read()
{
    char tempstr[MAX];
    char tempzip[MAX];

    cout << "Please enter the street and zip address of this activity:\n";
    cin.get(tempstr, MAX); cin.ignore(3000,'\n');
    cin.get(tempzip, MAX); cin.ignore(3000,'\n');

    street = new char[strlen(tempstr) +9];
    strcpy(street, tempstr);
    zip = new char[strlen(tempzip) +9];
    strcpy(zip, tempzip);

    if (street && zip)
        return 1;

    return 0;
}

int address::display() const
{
    if (street)
        cout << "Street:\t" << street << endl;
    if (zip)
        cout << "Street:\t" << zip << endl;

    return 0;
}


