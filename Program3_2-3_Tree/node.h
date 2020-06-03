#include "source.h"

//Will McIntosh, 5-15-20
//This file contains the management of the data.
//Vec class is inside of each Node, which is part of the Tree.
//The only exclusion to that are the Data and Content classes.
//These two classes are part of the overall hierarchy.
//But for some reason I had to place them here, otherwise
//I'd get these reference errors.

//This class houses three of the most derived class
//in the hierarchy. It holds three of them per node (for a 2-3 tree).
//There are one of these "vec" class members in each node.
//This class manages the array of dervied class pointers.
//It will reposition, remove, switch, pass along, etc.

/**********************************************************
 * VEC CLASS
**********************************************************/

class vec
{
    public:
        vec();
       ~vec();
        int insert_into_array(class data *& in_data);
        int remove(char * in_name);
        int display_array();
        char display_array_name();
        int display_array_pri();
        int delete_array();
        int name_exists(char * in_name);
        char * get_pri(int index);
        int check_pri(char * my_pri);
        class data *& get_data(int index);
        int the_housemaid_protocol(int index_1, int index_2, int index_3);
    protected:
        void shifty_shift_up(int & inc);
        void shifty_shift_down(int & inc);
        int data_to_array(data *& in_data, int & inc);
        int display_element(data in_data);
        int display_element_name(data * in_data);
        class data ** datas;
        class data ** temps;
        int cap;
};

//This class simply holds the vec classes' three data pointers.
//It also holds pointers to the next nodes, five in total.
//Right, two middle pointers, a left, and a parent pointer.
/**********************************************************
 * NODE CLASS
**********************************************************/

class node : public vec
{
    public:
        node();
        node(const node & my_tree);
        node(const data & my_data);
        node *& go_left();
        node *& go_real_middle();
        node *& go_temp_middle();
        node *& go_right();
        node *& go_parent();
        node * get_left() const;
        int set_ancestor_path(char * in_path);
        void connect_left(node * connection);
        void connect_right(node * connection);
        void connect_real_middle(node * connection);
        void connect_temp_middle(node * connection);
        void connect_parent(node * connection);
        char * get_ancestor_path();
        int compare_entire_name(char * temp);
        int compare_partial_name(char * temp);
        String & operator [] (int index);
    protected:
        node * parent;
        node * left;
        node * right;
        node * real_middle;
        node * temp_middle;
        char * ancestor_path;
};

//This class manages the tree, node placement, display, etc.
//This is a 2-3 tree!
class tree
{
    public:
        tree();
        ~tree();
        int remove_by_priority();
        int remove_by_name(node *& root, char * user_input);
        int insert_from_user();
        int grab_news();
        int grab_emails();
        int grab_meetings();
        int display_everything();
        int display_by_priority();
        int display_by_name();
        int single_removal();
        int count();
        int height();
        int display_tree();
    protected:
        int display_tree(int & level);
        int display_paths(node * root);
        int count(node * root);
        int height(node * root);
        int copy_all_nodes(node *& root, node * in_root);
        int display(node * root); 
       int display_by_priority(node * root, char * in_pri);
        int display_by_perfect_name(node * root, char * temp);
        int display_by_partial_name(node * root, char * temp);
        int insert_into_tree(node *& root, data *& in_data);
        int destroy_all(node *& in_root);
        int remove_by_priority(node *& root, char * in_pri);
        char * find_ancestor_path(node * root, char * my_path);
        int locate_path(node * root, char * in_path);
        int make_ancestor_path(node *& root);
        int look_for_leafs(node *& root, data *& in_data);
        int the_fullhouse_protocol();
        int the_lumberjack_protocol(node *& root);
        class node * root;
};

//Since this class contains an object (through a pointer)
//of the nodes I chose to build an object
//of this class in int_main making it the most derived class of all.

class content : public source
{
    public:
        content();
        content(const content & to_copy);
        ~content();
       int read_from_user();
        int read_from_file(char * word1, char * word2);
        int display() const;
    protected:
        class String date;
        class String time;
};

//This holds the "data" of the piece of news
class data : public content
{
    public:
        data();
        data(const data & to_copy);
        ~data();
        int read_from_user();
        int read_from_file(char * word1, char * word2);
        int display() const;
        int check_pri(char * my_pri);
        char * get_pri();
        String & operator [] (int index);
    protected:
        class String body_text;
        class String priority;
};





