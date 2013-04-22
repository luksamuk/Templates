#include <iostream>

template <typename T>
class Queue
{
public:
    Queue()
    { _queue = NULL; }


    ~Queue()
    {
        if(_queue != NULL)
        {
            if(_queue->next == NULL)
            {
                delete _queue;
                _queue = NULL;
            }
            else
            {
                while(_queue->next != NULL)
                {
                    _queue = _queue->next;
                    delete _queue->prev;
                }

                delete _queue;
                _queue = NULL;
            }
        }
    }

    inline bool isempty() { return (_queue == NULL ? true : false); }

    bool enqueue(T newdata)
    {
        try
        {
            if(isempty())
            {
                _queue = new node;
                _queue->data = newdata;
                _queue->next = NULL;
                _queue->prev = NULL;
            }
            else
            {
                node * aux = _queue;
                while(aux->next != NULL) aux = aux->next;

                aux->next = new node;
                aux->next->prev = aux;
                aux->next->next = NULL;
                aux->next->data = newdata;
            }
        }
        catch (...) { return false; }

        return true;
    }

    T dequeue()
    {
        T returning_data;

        if(!isempty())
        {
            if(_queue->next == NULL)
            {
                returning_data = _queue->data;
                delete _queue;
                _queue = NULL;
            }
            else
            {
                node * aux = _queue;
                _queue = _queue->next;
                _queue->prev = NULL;

                returning_data = aux->data;
                delete aux;
          }
        }

       return returning_data;
    }
private:
    struct node
    {
        T data;
        node * next;
        node * prev;
    };

    node * _queue;
};


int main()
{
    Queue<char> fila;

    std::cout << "Enqueue \'a\': " << fila.enqueue('a') << std::endl;
    std::cout << "Enqueue \'b\': " << fila.enqueue('b') << std::endl;
    std::cout << "Dequeue - must return \'a\': " << fila.dequeue() << std::endl;
    std::cout << "Dequeue - must return \'b\': " << fila.dequeue() << std::endl;
    std::cout << "Dequeue - must return NULL: " << fila.dequeue() << std::endl;
    return 0;
}
