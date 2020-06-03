#include "node.h"

//Will McIntosh Program 3 5-15-20
//The main purpose of this program is to produce
//an RSS feed to grab the items the user wants.
//Two options have sub options.
//Display tree is for troubleshooting, and looks cool.
//The information is stored into a 2-3 balanced tree

using namespace std;

bool user_confirmation();

int main()
{
    char user_input_001 = '\n';
    char user_input_002 = '\n';

    tree my_tree;

    cout << "\n\nWelcome to your new RSS feed!\n\n";

    do
    {
        cout << "Which action would you like to perform?\n"
            << " a. Grab updates from sources.\n"
            << " b. Manually write up a new piece of content.\n"
            << " c. Display some contents.\n";

        cin.get(user_input_001); cin.ignore(3000,'\n');

        switch(toupper(user_input_001))
        {
            case 'A':
                {
                    cout << "Which type would you like to grab?\n"
                        << " a. Grab updates from news sources.\n"
                        << " b. Grab updates from emails sources.\n"
                        << " c. Grab updates from meetings sources.\n";
                    cin.get(user_input_002); cin.ignore(3000,'\n');
                    switch(toupper(user_input_002))
                    {

                        case 'A': my_tree.grab_news(); break;
                        case 'B': my_tree.grab_emails(); break;
                        case 'C': my_tree.grab_meetings(); break;
                    }
                } break;
            case 'B': my_tree.insert_from_user(); break;
            case 'C':
                {
                    cout << "Which type would you like to display?\n"
                        << " a. Display all contents of a certain priority.\n"
                        << " b. Display contents by name.\n"
                        << " c. Display everything.\n";
                    cin.get(user_input_002); cin.ignore(3000,'\n');
                    switch(toupper(user_input_002))
                    {
                        case 'A': my_tree.display_by_priority(); break;
                        case 'B': my_tree.display_by_name(); break;
                        case 'C': my_tree.display_everything(); break;
                    }
                } break;
            default: cout << "I didn't catch that, let's try again.\n"; break;
        }

    } while (user_confirmation());

    return 1;
}


