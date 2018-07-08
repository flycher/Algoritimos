#include <iostream>

template <class T>
struct bstnode
{
    int key; //guarda a chave do nó
    T data; //guarda o dado do nó
    bstnode<T> *parent, *left, *right; //pai e filhos

    bstnode() {};

    bstnode(int key, T data, bstnode<T> *node)
    {
        this->key = key;
        this->data = data;
        this->parent = this->left = this->right = node;
    };
};

template <class T>
class BSTree
{
private:
    bstnode<T> *root; //raiz da arvore
    void transplant(bstnode<T>* u, bstnode<T>* v); //troca nós de posição
    bstnode<T>* minimum(bstnode<T>* node); //retorna no minimo da subarvore
    bstnode<T>* maximum(bstnode<T>* node); //retorna no maximo da subarvore
    void clearTree(bstnode<T>* node); //libera todos os nós da arvore

public:
    BSTree(); //inicializa a saiz da árvore
    ~BSTree(); //libera os nós da memória
    bstnode<T>* getRoot(); //retorna o nó raiz da arvore
    bstnode<T>* search(int key); //procura o no com chave k na arvore
    void insert(int key, T data); //insere dado d com chave k na arvore
    void remove(int key); //remove nó com chave k da arvore
    bstnode<T>* successor(int key); //retorna sucessor do nó de chave k
    bstnode<T>* predecessor(int key); //retorna predecessor do nó de chave k
    void inOrder(bstnode<T>* node); //percurso em ordem
    void preOrder(bstnode<T>* node); //percurso pre ordem
    void postOrder(bstnode<T>* node); //percurso pos ordem
    //mostra uma arvore binária formatada. Pelo professor David Sena.
    //https://github.com/senapk/btree_formatada
    void bshow_dual(bstnode<T>* node, std::string heranca, std::ostream& fout);
};

template <class T>
BSTree<T>::BSTree()
{
    this->root = nullptr;
};

template <class T>
BSTree<T>::~BSTree()
{
    clearTree(this->root);
};

template <class T>
bstnode<T>* BSTree<T>::getRoot()
{
    return root;
};

template <class T>
bstnode<T>* BSTree<T>::search(int key)
{
    bstnode<T> *temp = root;

    while(temp != nullptr && temp->key != key)
    {
        if(key > temp->key)
            temp = temp->right;
        else
            temp = temp->left;
    }

    return temp;
};

template <class T>
void BSTree<T>::insert(int key, T data)
{
    bstnode<T> *newnode = new bstnode<T>(key, data, nullptr);
    bool repeated = false;

    if(root == nullptr)
    {
        root = newnode;
    }
    else
    {
        bstnode<T> *temp = root, *parent;

        while(temp != nullptr)
        {
            parent = temp;

            if(key == temp->key)
            {
                repeated = true;
                break;
            }

            if(key > temp->key)
                temp = temp->right;
            else
                temp = temp->left;
        }

        if(!repeated)
        {
            newnode->parent = parent;

            if(key > parent->key)
                parent->right = newnode;
            else
                parent->left = newnode;
        }
        else
            std::cerr << "Value already in the tree.\n";
    }
};

template <class T>
void BSTree<T>::transplant(bstnode<T>* u, bstnode<T>* v)
{
    if(u->parent == nullptr) //u é a raiz da arvore
        root = v;
    else if(u == u->parent->left) //u é filho esquerdo
        u->parent->left = v;
    else //u é filho direito
        u->parent->right = v;
    if(v != nullptr) //atribui parente se v não for nulo
        v->parent = u->parent;
};

template <class T>
void BSTree<T>::remove(int key)
{
    bstnode<T> *old = search(key); //acha nó com chave k na arvore

    if(old == nullptr)
        std::cerr << "Value not in the tree.\n";
    else
    {
        if(old->left == nullptr) //old não tem filho direito
            transplant(old, old->right);
        else if(old->right == nullptr) //old não tem filho esquerdo
            transplant(old, old->left);
        else //old tem 2 filhos
        {
            bstnode<T> *replacement = minimum(old->right); //sucessor de old

            if(replacement->parent != old) //se replacement não for filho direito de old
            {
                //troca replacement como o filho de seu pai pelo filho direito de replacement
                //e torna o filho direito de old no filho direito de replacement
                transplant(replacement, replacement->right);
                replacement->right = old->right;
                replacement->right->parent = replacement;
            }
            //troca old como o filho de seu pai por replacement e
            //troca o filho direito de replacement pelo filho direito de old
            transplant(old, replacement);
            replacement->left = old->left;
            replacement->left->parent = replacement;
            delete old;
        }
    }
};

template <class T>
bstnode<T>* BSTree<T>::minimum(bstnode<T>* node)
{
    bstnode<T> *temp = node;

    while(temp->left != nullptr)
        temp = temp->left;

    return temp;
};

template <class T>
bstnode<T>* BSTree<T>::maximum(bstnode<T>* node)
{
    bstnode<T> *temp = node;

    while(temp->right != nullptr)
        temp = temp->right;

    return temp;
};

template <class T>
bstnode<T>* BSTree<T>::successor(int key)
{
    bstnode<T> *temp = search(key);

    if(temp->right != nullptr)
        return minimum(temp->right);

    bstnode<T>* succ = temp->parent;

    while(succ != nullptr && temp == succ->right)
    {
        temp = succ;
        succ = succ->parent;
    }

    return succ;
};

template <class T>
bstnode<T>* BSTree<T>::predecessor(int key)
{
    bstnode<T> *temp = search(key);

    if(temp->left != nullptr)
        return maximum(temp->left);

    bstnode<T>* pred = temp->parent;

    while(pred != nullptr && temp == pred->left)
    {
        temp = pred;
        pred = pred->parent;
    }

    return pred;
};

template <class T>
void BSTree<T>::inOrder(bstnode<T>* node)
{
    if(node != nullptr)
    {
        inOrder(node->left);
        std::cout << "| " << node->key << ',' << node->data << " |";
        inOrder(node->right);
    }
};

template <class T>
void BSTree<T>::preOrder(bstnode<T>* node)
{
    if(node != nullptr)
    {
        std::cout << "| " << node->key << ',' << node->data << " |";
        preOrder(node->left);
        preOrder(node->right);
    }
};

template <class T>
void BSTree<T>::postOrder(bstnode<T>* node)
{
    if(node != nullptr)
    {
        postOrder(node->left);
        postOrder(node->right);
        std::cout << "| " << node->key << ',' << node->data << " |";
    }
};

template <class T>
void BSTree<T>::clearTree(bstnode<T>* node)
{
    if(node != nullptr)
    {
        clearTree(node->left);
        clearTree(node->right);
        delete node;
    }
};

template <class T>
void BSTree<T>::bshow_dual(bstnode<T>* node, std::string heranca, std::ostream& fout)
{
    if(node != nullptr && (node->left != nullptr || node->right != nullptr))
        bshow_dual(node->right , heranca + "r", fout);

    int tam = heranca.size();

    for(int i = 0; i < tam - 1; i++)
    {
        if(heranca[i] != heranca[i + 1])
            fout << "│" << "   ";
        else
            fout << " " << "   ";
    }

    if(heranca != "")
    {
        if(heranca.back() == 'r')
            fout << "┌───";
        else
            fout << "└───";
    }

    if(node == nullptr)
    {
        fout << "#" << std::endl;
        return;
    }

    fout << node->key << std::endl;

    if(node != nullptr && (node->left != nullptr || node->right != nullptr))
        bshow_dual(node->left, heranca + "l", fout);
};
