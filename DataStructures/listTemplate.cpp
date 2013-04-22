#include <iostream>
#include <exception>

template<typename T>
class List
{
public:
    bool _debug;

    List(bool isdebugging)
    {
        if(isdebugging)
        {
            std::cout << "\nctor\nlist is empty and ready.\n\n\n";
            _debug = true;
        }
        else _debug = false;
        _list = NULL;
    }

    ~List()
    {
        if(_debug) std::cout << "\ndtor\n";

        if(_list != NULL)
        {
            if(_debug) std::cout << "list is not empty.\n";

            if(_list->next == NULL)
            {
                if(_debug) std::cout << "detected a single-element list. destructing... ";
                delete _list;
                _list = NULL;
            }
            else
            {
                if(_debug) std::cout << "detected a multiple-element list. destructing... ";

                node * i = _list->next;
                delete _list; _list = NULL;

                while(i->next != NULL)
                {
                    i = i->next;
                    delete i->prev;
                }

                delete i;
            }

            if(_debug) std::cout << "done.\n\n";
        }
        else
        {
            if(_debug) std::cout << "list is empty.\nno destruction necessary.\n\n";
        }
    }

    inline bool isempty()
    { return ((_list == NULL) ? true : false); }

    bool Add(T item)
    {
        if(_debug)
        {
            if(sizeof(T) == sizeof(int)
            || sizeof(T) == sizeof(char)
            || sizeof(T) == sizeof(bool)
            || sizeof(T) == sizeof(float)
            || sizeof(T) == sizeof(double))
                std::cout << "adding item \"" << item << "\" to list\n";
            else std::cout << "adding item to list\n";
        }

        try
        {
            if(isempty())
            {
                if(_debug) std::cout << "list is empty. adding... ";
                _list = new node;
                _list->prev = NULL;
                _list->next = NULL;
                _list->data = item;
            }
            else
            {
                if(_debug) std::cout << "list is not empty. adding... ";
                node * i = _list;
                while(i->next != NULL)
                  i = i->next;

                i->next = new node;
                i->next->prev = i;
                i->next->next = NULL;
                i->next->data = item;
            }

            if(_debug) std::cout << "done.\nreturn success;\n\n";
            return true;
        }
        catch(std::exception e)
        {
            if(_debug) std::cout << "exception thrown: " << e.what() << "\n return failure;\n\n";
            return false;
        }
    }

    T Remove(T item)
    {
        if(_debug)
        {
            if(sizeof(T) == sizeof(int)
            || sizeof(T) == sizeof(char)
            || sizeof(T) == sizeof(bool)
            || sizeof(T) == sizeof(float)
            || sizeof(T) == sizeof(double))
                std::cout << "removing item \"" << item << "\" from list\n";
            else std::cout << "removing item from list\n";
        }

        if(isempty())
        {
           if(_debug) std::cout <<  "error: list empty.\nreturn NULL item;\n\n";
           T empty;
           return empty;
        }

        node * i = _list;
        while(true)
        {
            if(i->data == item) break;
            else if(i->next != NULL) i = i->next;
            else
            {
                if(_debug) std::cout << "error: item not found.\nreturn NULL item;\n\n";
                T empty;
                return empty;
            }
        }
        if(_debug) std::cout << "found. ";

        if(i->prev != NULL && i->next != NULL)
        {
            if(_debug) std::cout << "removing from middle of list... ";
            i->prev->next = i->next;
            i->next->prev = i->prev;
        }
        else if(i->prev == NULL && i->next != NULL)
        {
            if(_debug) std::cout << "removing from start of list... ";
            i->next->prev = NULL;
            _list = i->next;
        }
        else if(i->prev != NULL && i->next == NULL)
        {
            if(_debug) std::cout << "removing from end of list... ";
            i->prev->next = NULL;
        }
        else
        {
            if(_debug) std::cout << "removing the single element of list... ";
            _list = NULL;
        }

        T returning_item = i->data;
        delete i;
        if(_debug) std::cout << "done.\nreturn item;\n\n";
        return returning_item;
    }

private:

    struct node
    {
        T data;
        node * next;
        node * prev;
    };

    node * _list;
};


int main()
{
    List<char> lista(true);

    std::cout << "~ Tests for adding elements to list and removing its first element\n\n";
    lista.Add('b');
    lista.Add('a');
    lista.Remove('b');

    std::cout << "~ Tests for removing from the end of list of from a single-element list.\n\n";
    lista.Add('b');
    lista.Remove('b');
    lista.Remove('c');
    lista.Remove('a');
    lista.Remove('c');


    std::cout << "~ Tests for removing from middle of list.\n\n";

    lista.Add('a');
    lista.Add('b');
    lista.Add('c');
    lista.Remove('b');
    return 0;
}
