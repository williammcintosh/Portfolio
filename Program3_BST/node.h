#include "activity.h"

//This is the most base class.
//All pieces of activity come from this class.
//It houses the name field.
/**********************************************************
 * VEC CLASS
**********************************************************/

class vec
{
    public:
        vec();
       ~vec();
        int insert(int my_pri);
        int remove(char * in_name);
        int display_array(int in_pri);
        int display_array_name();
        int delete_array();
        int name_exists(char * in_name);
    protected:
        int cap;
        class task ** tasks;
        class task ** temps;
        void shifty_shift_up(int & inc);
        void shifty_shift_down(int & inc);
        int task_to_array(task *& in_task, int & inc);
        int display_element(task * in_task);
        int display_element_name(task * in_task);
};

/**********************************************************
 * NODE CLASS
**********************************************************/

//This class houses the nodes for the video lectures.
//The nodes don't do anything, except have a left pointer,
//to point to the left node in the list.
class node : public vec
{
    public:
        node();
        node(int my_level);
        node(const node & term_table);
        node *& go_left();
        node *& go_right();
        node *& go_parent();
        node * get_left() const;
        int check_pri(int my_pri);
        int get_pri();
        int set_ancestor_path(char * in_path);
        void connect_left(node * connection);
        void connect_right(node * connection);
        void connect_parent(node * connection);
        char * get_ancestor_path();
    protected:
        node * parent;
        node * left;
        node * right;
        int level;
        char * ancestor_path;
};

class task_tree
{
    public:
        task_tree();
        ~task_tree();
        int remove_by_priority();
        int remove_by_name(node *& root, char * user_input);
        int insert();
        int display_everything();
        int task_by_priority();
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
        int task_by_priority(node * root, int in_pri);
        int create_pri(node *& root, int & my_pri);
        int destroy_all(node *& in_root);
        int remove_by_priority(node *& root, int in_pri);
        char * find_ancestor_path(node * root, char * my_path);
        int locate_path(node * root, char * in_path);
        int make_ancestor_path(node *& root);
        class node * root;
};

//Since this class contains an object (through a pointer)
//of the nodes I chose to build an object
//of this class in int_main making it the most derived class of all.

class task : public activity
{
    public:
        task();
        task(const task & to_copy);
        virtual ~task();
        virtual int read() =0;
        virtual int display() const;
    protected:
        char * date;
        char * time;
};

class hiking : public task
{
    public:
        hiking();
        hiking(const hiking & to_copy);
        ~hiking();
        int read();
        int display() const;
    protected:
        float duration;
        int friends;
        char * trailroot;
};

class dining : public task
{
    public:
        dining();
        dining(const dining & to_copy);
        ~dining();
        int read();
        int display() const;
    protected:
        float duration;
        int friends;
        char * meal;
};

class zooing : public task
{
    public:
        zooing();
        zooing(const zooing & to_copy);
        ~zooing();
        int read();
        int display() const;
    protected:
        float duration;
        int friends;
        char * animal;
};
