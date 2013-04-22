#include <iostream>

template<typename T>
class List
{
public:

    List()
    {
        _list = NULL;
    }

    ~List()
    {
        if(_list != NULL)
        {
            if(_list->next == NULL)
            {
                delete _list;
                _list = NULL;
            }
            else
            {
                node * i = _list->next;
                delete _list; _list = NULL;

                while(i->next != NULL)
                {
                    i = i->next;
                    delete i->prev;
                }

                delete i;
            }
        }
    }

    inline bool isempty()
    { return ((_list == NULL) ? true : false); }

    bool Add(T item)
    {
        try
        {
            if(isempty())
            {
                _list = new node;
                _list->prev = NULL;
                _list->next = NULL;
                _list->data = item;
            }
            else
            {
                node * i = _list;
                while(i->next != NULL)
                  i = i->next;

                i->next = new node;
                i->next->prev = i;
                i->next->next = NULL;
                i->next->data = item;
            }
            return true;
        }
        catch(...) { return false; }
    }

    T Remove(T item)
    {
        if(isempty())
        {
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
                T empty;
                return empty;
            }
        }

        if(i->prev != NULL && i->next != NULL)
        {
            i->prev->next = i->next;
            i->next->prev = i->prev;
        }
        else if(i->prev == NULL && i->next != NULL)
        {
            i->next->prev = NULL;
            _list = i->next;
        }
        else if(i->prev != NULL && i->next == NULL)
            i->prev->next = NULL;
        else
            _list = NULL;

        T returning_item = i->data;
        delete i;
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
    List<char> lista;

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
