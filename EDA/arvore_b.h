#include <iostream>

template <class T>
struct btreenode
{
    int *keys; //guarda a chave do elemento
    T *data; //guarda o dado do elemento
    btreenode<T> **children; //array de ponteiros para nós
    bool is_leaf; //se o nó e uma folha
    int n_of_elements; //quantidade de elementos no nó

    btreenode() {};

    btreenode(int degree, bool is_leaf, int n_of_elements)
    {
        keys = new int[2 * degree - 1];
        data = new T[2 * degree - 1];
        children = new btreenode<T>*[2 * degree];
        this->is_leaf = is_leaf;
        this->n_of_elements = n_of_elements;
    }
};

template <class T>
class BTree
{
private:
    int degree; //grau da árvore
    btreenode<T> *root;
    void splitChild(btreenode<T>* node, btreenode<T>* child, int index); //cisão
    void insertNonfull(btreenode<T>* node, int key, T data); //insersão em folha

public:
    BTree(int degree);
    ~BTree();
    btreenode<T>* getRoot(); //retora a raiz da árvore
    std::pair<btreenode<T>*, int> search(int key); //retorna o no que se encontra a chave
    void insert(int key, T data); //insere um elemento na árvore
    void traverseInOrder(btreenode<T>* node); //percorre a árvore em ordem
    void showNodes(btreenode<T>* node); //mostra os nós da árvore

};

template <class T>
BTree<T>::BTree(int degree)
{
    this->degree = degree;
    root = new btreenode<T>(degree, true, 0);
};

template <class T>
BTree<T>::~BTree()
{
};

template <class T>
btreenode<T>* BTree<T>::getRoot()
{
    return this->root;
};

template <class T>
std::pair<btreenode<T>*, int> BTree<T>::search(int key)
{
    btreenode<T> *node = root;
    int l, r, m, k;

    while(node != nullptr)
    {
        l = 0, r = node->n_of_elements - 1;
        while(l <= r)
        {
            m = l + (r - 1) / 2;
            k = node->keys[m];

            if(k == key)
                return std::make_pair(node, m);
            else if(k > key)
                r = m - 1;
            else
                l = m + 1;
        }

        if(node->is_leaf)
        {
            return std::make_pair(node, -1);
        }

        if(k > key)
            node = node->children[m];
        else
            node = node->children[m + 1];
    }
};

template <class T>
void BTree<T>::splitChild(btreenode<T>* node, btreenode<T>* child, int index)
{
    btreenode<T> *new_node = new btreenode<T>(degree, child->is_leaf, degree - 1);

    //copia os últimos (degree - 1) elementos de child para new_node
    for(int i = 0; i < degree - 1; i++)
    {
        new_node->keys[i] = child->keys[i + degree];
        new_node->data[i] = child->data[i + degree];
    }

    if(!child->is_leaf)
    {   //copia últimos degree nós de child para new_node
        for(int i = 0; i < degree; i++)
            new_node->children[i] = child->children[i + degree];
    }

    child->n_of_elements = degree - 1; //atualiza o numero de elementos em child

    //move os nós de node até index + 1 criando espaço para o novo nó
    for(int i = node->n_of_elements; i >= index + 1; i--)
        node->children[i + 1] = node->children[i];

    node->children[index + 1] = new_node; //põe o novo nó em node

    //move os elemtos de node até index criando espaço para o novo elemento
    for(int i = node->n_of_elements - 1; i >= index; i--)
    {
        node->keys[i + 1] = node->keys[i];
        node->data[i + 1] = node->data[i];
    }

    //insere o novo elemento em node e aumenta a quantidade de elementos em node
    node->keys[index] = child->keys[degree - 1];
    node->data[index] = child->data[degree - 1];
    node->n_of_elements++;
};

template <class T>
void BTree<T>::insert(int key, T data)
{
    std::pair<btreenode<T>*, int> repeated = search(key);

    if(repeated.second != -1)
        cerr << "Key already in the tree.\n";
    else
    {
        if(root->n_of_elements == 2 * degree - 1) //se não ha espaço a raiz
        {
            btreenode<T> *new_node = new btreenode<T>(degree, false, 0); //cria nova raiz
            new_node->children[0] = root;
            root = new_node;
            splitChild(new_node, new_node->children[0], 0); //realiza cisão na antiga raiz

            int i = 0;
            if (key > new_node->keys[0]) //se o elemento que sobe e menor que a chave
                i++;

            insertNonfull(new_node->children[i], key, data); //inserimos o novo elemento em uma folha
        }
        else
            insertNonfull(root, key, data); //inserimos o novo elemento na raiz
    }
};

template <class T>
void BTree<T>::insertNonfull(btreenode<T>* node, int key, T data)
{
    int index = node->n_of_elements - 1; //quantidade de elementos no nó

    if(node->is_leaf) //se o nó é folha
    {
        while(index >= 0 && key < node->keys[index]) //cria espaço para o novo elemento
        {
            node->keys[index + 1] = node->keys[index];
            node->data[index + 1] = node->data[index];
            index--;
        }

        //insere o novo elemento em node e aumenta a quantidade de elementos em node
        node->keys[index + 1] = key;
        node->data[index + 1] = data;
        node->n_of_elements++;
    }
    else //se o nó não é folha
    {
        while(index >= 0 && key < node->keys[index]) //procuramos onde vamos descer
            index--;

        index++;
        if(node->children[index]->n_of_elements == 2 * degree - 1) //se não há espaço
        {
            splitChild(node, node->children[index], index); //cisão no nó destino

            if(key > node->keys[index]) //se o elemento que sobe e menor que a chave
                index++;
        }

        insertNonfull(node->children[index], key, data); //insere no destino
    }
};

template <class T>
void BTree<T>::traverseInOrder(btreenode<T>* node)
{
    int i, n = node->n_of_elements;

    for (i = 0; i < n; i++)
    {
        if (!node->is_leaf)
            traverseInOrder(node->children[i]);
        std::cout << " " << node->keys[i];
    }

    if (!node->is_leaf)
        traverseInOrder(node->children[i]);
};

template <class T>
void BTree<T>::showNodes(btreenode<T>* node)
{
    int i, n = node->n_of_elements;

    std::cout << '[';
    for (i = 0; i < n; i++)
    {
        std::cout << node->keys[i]  << ',';
    }
    std::cout << ']';

    if (!node->is_leaf)
    {
        for (i = 0; i < n + 1; i++)
        {
            showNodes(node->children[i]);
        }
    }
}
