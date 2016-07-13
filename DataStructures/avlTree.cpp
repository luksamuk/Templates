#include <string>
#include <iostream>
#include <cstdlib>
#include "savetool.hpp"

template<typename K, typename T>
class AVLTree
{
public:
    struct Node
    {
        K key;
        T info;
        int fb = 0;
        Node* left  = nullptr,
            * right = nullptr;
    };

private:
    Node* root;
	unsigned int n_elems;

    // Limpa recursivamente
    inline void _recursiveClear(Node*& n)
    {
        if(!n) return;
        if(n->left)  _recursiveClear(n->left);
        if(n->right) _recursiveClear(n->right);
        Remove(n->key);
        n = nullptr;
    }

    // Pesquisa
    inline T _find(K key, Node* n)
    {
        if(n) {
            if(n->key == key) return n->info;
            return _find(key, key < n->key ? n->left : n->right);
        }
        return 0;
    }

    // Inserção
    inline void _add(Node*& n, K key, T info)
    {
        if(!n)
        {
            n = new Node;
            n->key = key;
            n->info = info;
            // Left e Right são nullptr por default
            // fator de balancemento é 0 por default
            return;
        }

        if(key < n->key) _add(n->left,  key, info);
        else             _add(n->right, key, info);
    }

    // Remoção
    inline void _remove(Node*& n, K key)
    {
        if(!n) return;
        if(n->key == key) _deleteNode(n);
        else if(n->key < key) _remove(n->left, key);
        else _remove(n->right, key);
    }

    // Deleção de nó
    inline void _deleteNode(Node*& n)
    {
        // Caso sem sub-árvore
        if(!n->left && !n->right)
        {
            delete n;
            n = nullptr; // Nó é referência vinda do pai
            return;
        }

        // Casos de sub-árvore
        if(n->left && !n->right)
            n = n->left;
        else if(!n->left && n->right)
            n = n->right;
        else
        {
            Node* aux = n->left;
            Node* parent = n;
            while(aux->right)
            {
                parent = aux;
                aux = aux->right;
            }
            parent->right = aux->left;
            aux->left = n->left;
            aux->right = n->right;
            Node* aux2 = n;
            delete aux2;
            n = aux;
            return;
        }
        delete n;
        n = nullptr;
    }

    long long int _getHeight(const Node* n)
    {
        long long int Hl, Hr;
        if(!n) return 0L;
        Hl = _getHeight(n->left);
        Hr = _getHeight(n->right);
        return 1L + ((Hl > Hr) ? Hl : Hr);
    }

    // Balanceamento
    inline void _evaluateBalanceFactor(Node*& n)
    {
        if(!n) return;
        n->fb = static_cast<int>(_getHeight(n->left) - _getHeight(n->right));
    }

    inline void _evaluateFactorsRecursively(Node*& n)
    {
        _evaluateBalanceFactor(n);
        if(!n) return;
        _evaluateFactorsRecursively(n->left);
        _evaluateFactorsRecursively(n->right);
    }

    inline void _balance(Node*& n)
    {
        if(!n) return;
        _evaluateBalanceFactor(n);
        if(n->fb == 2) {
            _evaluateBalanceFactor(n->left);
            if(n->left->fb > 0) _rightRotation(n);
            else                _doubleRightRotation(n);
        }
        else if(n->fb == -2) {
            _evaluateBalanceFactor(n->right);
            if(n->right->fb < 0) _leftRotation(n);
            else                 _doubleLeftRotation(n);
        }
        _balance(n->left);
        _balance(n->right);
    }

    // Rotações
    inline void _rightRotation(Node*& n)
    {
        Node* aux = n->left;
        n->left = aux->right;
        aux->right = n;
        n = aux;
    }

    inline void _leftRotation(Node*& n)
    {
        Node* aux = n->right;
        n->right = aux->left;
        aux->left = n;
        n = aux;
    }

    inline void _doubleRightRotation(Node*& n)
    {
        Node* aux  = n->left;
        Node* aux2 = aux->right;
        aux->right = aux2->left;
        n->left = aux2->right;
        aux2->left = aux;
        aux2->right = n;
        n = aux2;
    }

    inline void _doubleLeftRotation(Node*& n)
    {
        Node* aux  = n->right;
        Node* aux2 = aux->left;
        n->right = aux2->left;
        aux->left = aux2->right;
        aux2->left = n;
        aux2->right = aux;
        n = aux2;
    }
public:
    AVLTree() {
        root = nullptr;
		n_elems = 0u;
    }

    ~AVLTree() {
		Clear();
    }

    void Add(K key, T info) {
        _add(root, key, info);
		n_elems++;
        _balance(root);
        _evaluateFactorsRecursively(root);
    }

    void Remove(K key) {
        _remove(root, key);
		n_elems--;
        _balance(root);
        _evaluateFactorsRecursively(root);
    }

    void Clear() {
        _recursiveClear(root);
    }

    T Find(K key) {
        return _find(key, root);
    }

    bool IsEmpty() {
        return (root == nullptr);
    }

	unsigned int size() {
		return n_elems;
	}

	Node* getRoot() {
		return root;
	}
};

int main(void)
{
	printf("TODO: Maybe someday I'll write a test here.");
	return 0;
}