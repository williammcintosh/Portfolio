#include "source.h"
using namespace std;

//Will McIntosh 5-15-20

//Global Function for client 
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
name::name() {}

//Copy Constructor
name::name(const name & to_copy)
{
    a_name = to_copy.a_name;
}

//Destructor
name::~name() {}

char * name::get_name()
{
    return a_name.get_str();
}

//Then store the object's "a_name" member from the user,
//otherwise store from the txt file.
int name::read_from_user()
{
    cout << "Please enter the name of source:\n";
    cin >> a_name; cin.ignore(MAX,'\n');

    return 1;
}

//Read's in a char star written from a file
int name::read_from_file(char * word1)
{
    if (word1) a_name = word1;

    return 1;
}

//Used for partial searches
int name::compare_name_by_letter(int num, char letter)
{
    if (a_name.compare_letter(num, letter))
        return 1;

    return 0;
}

//This simply displays the single private member
//Since there's no result from this function,
//I simply set it as a return type of void;
void name::display() const
{
    cout << "Name:\t" << a_name << endl;
}

/**********************************************************
 * SOURCE CLASS
**********************************************************/

//Default constructors
source::source() : name() {}

//Invokes the copy constructo for Address that I
// created earlier which does a deep copy.
source::source(const source & to_copy) :
    name(to_copy), an_address(to_copy.an_address)
{
    a_source = to_copy.a_source;
}

//Each class is responsible for displaying it's own data
int source::display() const
{
    cout << "File type:\t" << a_source << endl;

    return 0;
}

//This function simply tells the address class
//to accept input from the user and edit
int source::read_from_user()
{
    cout << "Please enter the type of this source:\n";
    cin >> a_source; cin.ignore(MAX,'\n');

    return an_address.read_from_user();
}

//Reads in information from the file
int source::read_from_file(char * word1, char * word2)
{
    if (word1) a_source = word1;

    an_address.read_from_file(word2);

    return 1;
}

//Called in the operator overload
String & source::get_address()
{
    return an_address.get_address();
}

/**********************************************************
 * ADDRESS CLASS
**********************************************************/

//Default Constructor
address::address() {}

//Copies the class to the new class object.
address::address(const address & to_copy) {}

//Destructor
address::~address() {}

//Called in the operator overload
String & address::get_address()
{
    return link;
}

//This function is called from int_main(),
// it collects the information from the user,
// and stores that into the temp static char array.
int address::read_from_user()
{
    cout << "Please enter the link address of this source:\n";
    cin >> link; cin.ignore(MAX,'\n');

    return 1;
}

//Reads the information in from a file
int address::read_from_file(char * word2)
{
    if (word2) link = word2;

    return 1;
}

//Each class is responsible for displaying it's own data
int address::display() const
{
    cout << "Link:\t" << link << endl;

    return 1;
}

/**********************************************************
 * STRING CLASS
 **********************************************************/

//Default Constructor
String::String() : str(0), len(0) {}

//Copy Constructor
String::String(const String & in_string) : len(in_string.len)
{
    str = NULL;
    str = new char[strlen(in_string.str) +1];
    strcpy(str, in_string.str);
}

//Parameterized Copy Constructor
String::String (char * in_char)
{
    str = NULL;
    len = strlen(in_char);

    str = new char[strlen(in_char) +1];
    strcpy(str, in_char);
}

//Destructor
String::~String()
{
    if (str)
        delete [] str;
}

//Assigns a String class object's char star to the
//String class object's char star
String & String::operator = (const String & in_string)
{
    if (this == & in_string)
        return * this;

    if (str)
        delete [] str;

    str = new char[in_string.len +1];
    strcpy(str, in_string.str);
    len = in_string.len;

    return * this;
}

//Assigns a char star to the string class's char star
String & String::operator = (const char * in_char)
{
    if (str)
        delete [] str;

    str = new char[strlen(in_char) +1];
    strcpy(str, in_char);
    len = strlen(in_char);

    return * this;
}

//Getter to compare for the data structure comparison
char * String::get_str()
{
    return str;
}

//These two are prototyped as a friend, since I'm not able to directly
//edit the istream class. Instead inside of the String class
//I can declare which functions have access. It's a hack,
//as Karla likes to call it.
std::istream & operator >> (std::istream & input, String & in_string)
{
    char temp[MAX];
    input.get(temp,MAX);
    in_string.len = strlen(temp);
    in_string.str = new char[in_string.len +1];
    strcpy(in_string.str, temp);
    return input;
}
    
std::ostream & operator << (std::ostream & output, const String & in_string)
{
    output << in_string.str;
    
    return output;
}

int String::operator == (const char * temp)
{
    if (strcmp(str,temp) > 0)
        return 1;

    return 0;
}

int String::compare_letter(int n, char temp)
{
    if (str[n] == temp)
        return 1;

    return 0;
}

String operator + (const String & in_string, char * in_char)
{
    String temp;
    temp.len = in_string.len + strlen(in_char);
    temp.str = new char[temp.len +1];
    strcpy(temp.str, in_string.str);
    strcat(temp.str, in_char);
    return temp;
}

String operator + (char * in_char, const String & in_string)
{
    String temp;
    temp.len = in_string.len + strlen(in_char);
    temp.str = new char[temp.len +1];
    strcpy(temp.str, in_string.str);
    strcat(temp.str, in_char);
    return temp;
}

String operator + (const String & first_string, const String & second_string)
{
    char * temp = new char[first_string.len + second_string.len+1];    
    strcpy(temp, first_string.str);
    strcat(temp, second_string.str);
    return String(temp);
}

//Makes a temp and stores in the data from it
String String::operator + (char * num) const
{
    char * temp = new char[len+strlen(num)+1];
    strcpy(temp, str);
    strcat(temp, num);
    return String(temp);
}

bool operator < (const String & s1, char * lit)
{
    return (strcmp(s1.str, lit) < 0);
}

bool operator < (const String & s1, const String & s2)
{
    return (strcmp(s1.str, s2.str) < 0);
}

bool operator < (char * lit, const String & s1)
{
    return (strcmp(lit, s1.str) < 0);
}

bool operator <= (const String & s1, char * lit)
{
    return (strcmp(s1.str, lit) < 0);
}

bool operator <= (char * lit, const String & s1)
{
    return (strcmp(lit, s1.str) < 0);
}

bool operator <= (const String & s1 ,const String & s2)
{
    return (strcmp(s1.str, s2.str) < 0);
}

bool operator > (const String & s1, char * lit)
{
    return (strcmp(s1.str, lit) < 0);
}

bool operator > (char * lit, const String & s1)
{
    return (strcmp(lit, s1.str) < 0);
}

bool operator > (const String & s1, const String & s2)
{
    return (strcmp(s1.str, s2.str) < 0);
}

bool operator >= (const String & s1, char * lit)
{
    return (strcmp(s1.str, lit) < 0);
}

bool operator >= (char * lit, const String & s1)
{
    return (strcmp(lit, s1.str) < 0);
}

bool operator >= (const String & s1,const String & s2)
{
    return (strcmp(s1.str, s2.str) < 0);
}

bool operator != (const String & s1, char * lit)
{
    return (strcmp(s1.str, lit) < 0);
}

bool operator != (char * lit, const String & s1)
{
    return (strcmp(lit, s1.str) < 0);
}

bool operator != (const String & s1,const String & s2)
{
    return (strcmp(s1.str, s2.str) < 0);
}

bool operator == (const String & s1, char * lit)
{
    return (strcmp(s1.str, lit) < 0);
}

bool operator == (char * lit, const String & s1)
{
    return (strcmp(lit, s1.str) < 0);
}

bool operator == (const String & s1,const String & s2)
{
    return (strcmp(s1.str, s2.str) < 0);
}





