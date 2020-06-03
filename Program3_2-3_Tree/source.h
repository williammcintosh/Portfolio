//Will McIntosh 5-15-20
//This file contains the classes for the custom String class.
//As well as all classes up the hierarchy.
//Each class contains a single String member.
//
//The information is built using a 2-3 balanced tree data structure

#include <iostream>
#include <cctype>
#include <cstring>
#include <fstream>
#include <cmath>

//Used for cin functions.
const int MAX = 100;

class String
{
    public:
        String();
        String(const String &);
        explicit String (char *);
        ~String();
        String & operator = (const String &);
        String & operator = (const char *);
        int operator == (const char *);
        friend std::istream & operator >> (std::istream &, String &);       
        friend std::ostream & operator << (std::ostream &, const String &);
        friend String operator + (const String &, char *);
        friend String operator + (char *, const String &);
        friend String operator + (const String &, const String &);
        String operator + (char * num) const;
        String & operator += (const String &);
        String & operator += (char *);
        char * get_str();
        int compare_letter(int num, char temp);
        friend bool operator < (const String &, char *);
        friend bool operator < (char *, const String &);
        friend bool operator < (const String &, const String &);
        friend bool operator <= (const String &, char *);
        friend bool operator <= (char *, const String &);
        friend bool operator <= (const String &,const String &);
        friend bool operator > (const String &, char *);
        friend bool operator > (char *, const String &);
        friend bool operator > (const String &, const String &);
        friend bool operator >= (const String &, char *);
        friend bool operator >= (char *, const String &);
        friend bool operator >= (const String &,const String &);
        friend bool operator != (const String &, char *);
        friend bool operator != (char *, const String &);
        friend bool operator != (const String &,const String &);
        friend bool operator == (const String &, char *);
        friend bool operator == (char *, const String &);
        friend bool operator == (const String &,const String &);
    protected:
        char * str;
        int len;
};

//This is the most base class of the hierarchy
//Since all class objects have a name
class name
{
    public:
        name();
        name(const name & to_copy);
        int read_from_user();
        int read_from_file(char * word1);
        void display() const;
        ~name();
        int compare_name_by_letter(int num, char letter);
        char * get_name();
    protected:
        class String a_name;
};

//This class comes from the approved source class,
//but it is not derived.
//The approved source contains an object of this class.
//This class houses the address the source is being held at.
class address
{
    public:
        address();
        address(const address & to_copy);
        int read_from_user();
        int read_from_file(char * word2);
        int display() const;
        ~address();
        String & get_address();
    protected:
        class String link;
};

//This is more for the generic source,
//before it is considered approved by the PSU board
class source : public name
{
    public:
        source();
        source(const source & to_copy); 
        int display() const;
        int read_from_user();
        int read_from_file(char * word1, char * word2);
        String & get_address();
    protected:
        class String a_source; 
        address an_address;
};


