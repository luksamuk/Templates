#include <iostream>
using namespace std;

template <typename T>
class Stack
{
public:
    Stack()
    {
        _stack = NULL;
    }
    ~Stack()
    {
        if(!isempty())
        {
            while(_stack->next != NULL)
            {
                node * aux = _stack;
                _stack = _stack->next;
                delete aux;
            }

            delete _stack;
            _stack = NULL;
        }
    }

    inline bool isempty()
    {
        return (_stack == NULL) ? true : false;
    }

    // Pushes a new content to the top of the stack.
    bool push(T newdata)
    {
        try
        {
            if(isempty())
            {
                _stack = new node;
                _stack->next = NULL;
                _stack->data = newdata;
            }
            else
            {
                node * aux = new node;
                aux->data = newdata;
                aux->next = _stack;
                _stack = aux;
            }

            return true;
        }
        catch(...)
        { return false; }
    }

    // Pops (and returns) content from the top of the stack.
    T pop()
    {
        if(isempty())
        {
            T empty;
            return empty;
        }

        T getdata;
        // ELSE IF
        if(_stack->next == NULL)
        {
            getdata = _stack->data;
            delete _stack;
            _stack = NULL;
            return getdata;
        }
        else
        {
	    node * aux = _stack;
            _stack = _stack->next;
            getdata = aux->data;
            delete aux;
        }
        return getdata;
    }

    // Peeks content from the top of the stack.
    inline T peek()
    {
        T empty;
        return (isempty() ? empty : _stack->data);
    }

private:
    struct node
    {
        T data;
        node * next;
    };

    node * _stack;
};



int main(int argc, char** argv)
{
    for(int i = 1; i < argc; i++)
    {
        cout << argv[i] << " ";
    }
    cout << endl;
    Stack<char> mystack;
    cout << "Pushing \'e\' > " << ((mystack.push('e')) ? "true" : "false") << endl;
    cout << "Pushing \'a\' > " << ((mystack.push('a')) ? "true" : "false") << endl;
    cout << "Peeked " << mystack.peek() << endl;
    cout << "Peeked " << mystack.peek() << endl;

    cout << endl;

    cout << "Popped " << mystack.pop() << ";" << endl;
    cout << "Peeked " << mystack.peek() << endl;
    cout << "Popped " << mystack.pop() << ";" << endl;
    cout << "Popped " << mystack.pop() << ";" << endl;
    cout << "Peeked " << mystack.peek() << endl;
    return 0;
}
