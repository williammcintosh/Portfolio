#include "node.h"

//Will McIntosh Program 2 4-30-20
//The main purpose of this program is to produce
//a list of the user of activities that they get
//to perform once the quarantine is lifted.

using namespace std;

bool user_confirmation();

int main()
{
    char user_input_001 = '\n';
    
    task_tree my_list;

    cout << "\n\nWelcome to your post-quarantine planner!\n\n";

    do
    {
        cout << "Which action would you like to perform?\n"
            << " a. Insert a new task.\n"
            << " b. Display all tasks of a certain priority.\n"
            << " c. Display everything.\n"
            << " d. Remove a single task.\n"
            << " e. Remove tasks by priority.\n"
            << " f. Display entire tree.\n";

        cin.get(user_input_001); cin.ignore(3000,'\n');

        switch(toupper(user_input_001))
        {
            case 'A': my_list.insert(); break;
            case 'B': my_list.task_by_priority(); break;
            case 'C': my_list.display_everything(); break;
            case 'D': my_list.single_removal(); break;
            case 'E': my_list.remove_by_priority(); break;
            case 'F': my_list.display_tree(); break;
            default:
                cout << "I didn't catch that, let's try again.\n"; break;
        }

    } while (user_confirmation());

    return 0;
}
