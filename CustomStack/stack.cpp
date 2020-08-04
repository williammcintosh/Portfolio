#include<iostream>
using namespace std;

class Node {
    public:
        Node();
        void SetNext(Node * connection);
        Node *& GetNext();
        void SetVal(int num);
        int GetVal();
    protected:
        int val;
        Node * next;
};

class Stack {
    public:
        Stack();
        void Push(int val);
        int Size();
        int Top();
        int Pop();
        ~Stack();
    protected:
        Node * top;
        int Size(Node *& top);
        int DeleteAll(Node *& top);
};

Stack::Stack() : top(0) {}

void Stack::Push(int val) {
    Node * temp = new Node;
    temp->SetNext(NULL);
    temp->SetVal(val);
    
    if (top) temp->SetNext(top);

    top = temp;
}

int Stack::Size() {
    return Size(top);
}

int Stack::Size(Node *& top) {
    if (!top) return 0;
    return Size(top->GetNext()) +1;
}

int Stack::Top() {
    if (top) return top->GetVal();
    return 0;
}

int Stack::Pop() {
    if (top)
    {
        int myVal = top->GetVal();
        Node * temp = top;
        delete top;
        top = temp;
        return myVal;
    }
    return 0;
}

int Stack::DeleteAll(Node *& top) {
    if (!top) return 0;
    DeleteAll(top->GetNext());
    top->SetNext(NULL);
    delete top;
    return 1;
}

Stack::~Stack() {
    DeleteAll(top);
}


Node::Node() : next(0) {
    val = 0;
}

void Node::SetNext(Node * connection) {
    this->next = connection;
}

Node *& Node::GetNext() {
    return next; 
}

void Node::SetVal(int num) {
    this->val = num;
}

int Node::GetVal() {
    return val;
}

int main()
{
    Stack myStack;
    myStack.Push(10);
    cout << "Stack size = " << myStack.Size() << '\n';
    cout << "Stack top  = " << myStack.Top() << '\n';
    myStack.Push(20);
    cout << "Stack size = " << myStack.Size() << '\n';
    cout << "Stack top  = " << myStack.Top() << '\n';
    myStack.Push(30);
    cout << "Stack size = " << myStack.Size() << '\n';
    cout << "Stack top  = " << myStack.Top() << '\n';
    cout << "Stack popped = " << myStack.Pop() << '\n';
}




