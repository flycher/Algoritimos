#include <iostream>

template <class T>
struct bstnode
{
    int key; //guarda a chave do nó
    T data; //guarda o valor do nó
    bstnode<T> *father = nullptr, *left = nullptr, *right = nullptr; //pai e filhos
};

template <class T>
class BST
{
private:
    bstnode<T> *root; //raiz da arvore
public:
    BST();
    ~BST();
    bstnode<T>* getRoot(); //retorna o nó raiz da arvore
    bstnode<T>* search(int k); //procura o no com chave k na arvore
    void insert(int k, T d); //insere valor d com chave k na arvore
    void rotation(bstnode<T>* u, bstnode<T>* v); //rotação
    void remove(int k); //remove nó com chave k da arvore
    bstnode<T>* minimum(bstnode<T>* r); //retorna no minimo da subarvore
    bstnode<T>* maximum(bstnode<T>* r); //retorna no maximo da subarvore
    bstnode<T>* successor(bstnode<T>* r); //retorna sucessor do nó
    bstnode<T>* predecessor(bstnode<T>* r); //retorna predecessor do nó
    void inOrder(bstnode<T>* r); //percurso em order
    void preOrder(bstnode<T>* r); //percurso pre order
    void postOrder(bstnode<T>* r); //percurso pos order
    void clearTree(bstnode<T>* r); //libera todos os nós da arvore
};

template <class T>
BST<T>::BST()
{
    root = nullptr;
};

template <class T>
BST<T>::~BST()
{
    clearTree(root);
};

template <class T>
bstnode<T>* BST<T>::getRoot()
{
    return root;
};

template <class T>
bstnode<T>* BST<T>::search(int k)
{
    bstnode<T> *temp = root;
    while(temp != nullptr && temp->key != k)
    {
        if(k > temp->key)
            temp = temp->right;
        else
            temp = temp->left;
    }
    return temp;
};

template <class T>
void BST<T>::insert(int k, T d)
{
    bstnode<T> *z = new bstnode<T>;
    z->key = k;
    z->data = d;
    if(root == nullptr) {
        root = z;
    } else {
        bstnode<T> *temp = root, *y;
        while(temp != nullptr)
        {
            y = temp;
            if(k > temp->key)
                temp = temp->right;
            else
                temp = temp->left;
        }
        z->father = y;
        if(k > y->key)
            y->right = z;
        else
            y->left = z;
    }
};

template <class T>
void BST<T>::rotation(bstnode<T>* u, bstnode<T>* v)
{
    if(u->father == nullptr) //u é a raiz da arvore
        root = v;
    else if(u == u->father->left) //u é filho esquerdo
        u->father->left = v;
    else //u é filho direito
        u->father->right = v;
    if(v != nullptr) //atribui parente se v não for nulo
        v->father = u->father;

};

template <class T>
void BST<T>::remove(int k)
{
    bstnode<T> *z = search(k); //acha nó com chave k na arvore
    if(z->left == nullptr) //z não tem filho direito
        rotation(z, z->right);
    else if(z->right == nullptr) //z não tem filho esquerdo
        rotation(z, z->left);
    else { //z tem 2 filhos
        bstnode<T> *y = minimum(z->right); //sucessor de z
        if(y->father != z) { //se y não for filho direito de z
            //troca y como o filho de seu pai pelo filho direito de y e
            //torna o filho direito de z no filho direito de y
            rotation(y, y->right);
            y->right = z->right;
            y->right->father = y;
        }
        //troca z como o filho de seu pai por y e
        //troca o filho direito de y pelo filho direito de z
        rotation(z, y);
        y->left = z->left;
        y->left->father = y;
        delete z;
    }
};

template <class T>
bstnode<T>* BST<T>::minimum(bstnode<T>* r)
{
    bstnode<T> *temp = r;
    while(temp->left != nullptr)
        temp = temp->left;
    return temp;
};

template <class T>
bstnode<T>* BST<T>::maximum(bstnode<T>* r)
{
    bstnode<T> *temp = r;
    while(temp->right != nullptr)
        temp = temp->right;
    return temp;
};

template <class T>
bstnode<T>* BST<T>::successor(bstnode<T>* r)
{
    bstnode<T> *temp = r;
    if(temp->right != nullptr)
        return minimum(temp->right);
    bstnode<T>* y = temp->father;
    while(y != nullptr && temp == y->right)
    {
        temp = y;
        y = y->father;
    }
    return y;
};

template <class T>
bstnode<T>* BST<T>::predecessor(bstnode<T>* r)
{
    bstnode<T> *temp = r;
    if(temp->left != nullptr)
        return maximum(temp->left);
    bstnode<T>* y = temp->father;
    while(y != nullptr && temp == y->left)
    {
        temp = y;
        y = y->father;
    }
    return y;
};

template <class T>
void BST<T>::inOrder(bstnode<T>* r)
{
    if(r != nullptr) {
        inOrder(r->left);
        std::cout << "| (" << r->key << ',' << r->data << ") |";
        inOrder(r->right);
    }
};

template <class T>
void BST<T>::preOrder(bstnode<T>* r)
{
    if(r != nullptr) {
        std::cout << "| (" << r->key << ',' << r->data << ") |";
        preOrder(r->left);
        preOrder(r->right);
    }
};

template <class T>
void BST<T>::postOrder(bstnode<T>* r)
{
    if(r != nullptr) {
        postOrder(r->left);
        postOrder(r->right);
        std::cout << "| (" << r->key << ',' << r->data << ") |";
    }
};

template <class T>
void BST<T>::clearTree(bstnode<T>* r)
{
    if(r != nullptr) {
        clearTree(r->left);
        clearTree(r->right);
        delete r;
    }
};
