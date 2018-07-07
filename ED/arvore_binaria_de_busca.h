#include <iostream>

struct bstnode
{
    int key; //guarda a chave do nó
    bstnode *father = nullptr, *left = nullptr, *right = nullptr; //pai e filhos
};

class BST
{
private:
    bstnode *root; //raiz da arvore
public:
    BST();
    ~BST();
    bstnode* getRoot(); //retorna o nó raiz da arvore
    bstnode* search(int k); //procura o no com chave k na arvore
    void insert(int k); //insere no com chave k na arvore
    void rotation(bstnode* u, bstnode* v); //rotação
    void remove(int k); //remove nó com chave k da arvore
    bstnode* minimum(bstnode* r); //retorna no minimo da subarvore
    bstnode* maximum(bstnode* r); //retorna no maximo da subarvore
    bstnode* successor(bstnode* r); //retorna sucessor do nó
    bstnode* predecessor(bstnode* r); //retorna predecessor do nó
    void inOrder(bstnode* r); //percurso em order
    void preOrder(bstnode* r); //percurso pre order
    void postOrder(bstnode* r); //percurso pos order
    void clearTree(bstnode* r); //libera todos os nós da arvore
};

BST::BST()
{
    root = nullptr;
};

BST::~BST()
{
    clearTree(root);
};

bstnode* BST::getRoot()
{
    return root;
}

bstnode* BST::search(int k)
{
    bstnode* temp = root;
    while(temp != nullptr && temp->key != k)
    {
        if(k > temp->key)
            temp = temp->right;
        else
            temp = temp->left;
    }
    return temp;
};

void BST::insert(int k)
{
    bstnode *z = new bstnode;
    z->key = k;
    if(root == nullptr) {
        root = z;
    } else {
        bstnode *temp = root, *y;
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

void BST::rotation(bstnode* u, bstnode* v)
{
    if(u->father == nullptr) //u é a raiz da arvore
        root = v;
    else if(u == u->father->left) //u é filho esquerdo
        u->father->left = v;
    else //u é filho direito
        u->father->right = v;
    if(v != nullptr) //atribui parente se v não for nulo
        v->father = u->father;

}

void BST::remove(int k)
{
    bstnode *z = search(k); //acha nó com chave k na arvore
    if(z->left == nullptr) //z não tem filho direito
        rotation(z, z->right);
    else if(z->right == nullptr) //z não tem filho esquerdo
        rotation(z, z->left);
    else { //z tem 2 filhos
        bstnode *y = minimum(z->right); //sucessor de z
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

bstnode* BST::minimum(bstnode* r)
{
    bstnode* temp = r;
    while(temp->left != nullptr)
        temp = temp->left;
    return temp;
};

bstnode* BST::maximum(bstnode* r)
{
    bstnode* temp = r;
    while(temp->right != nullptr)
        temp = temp->right;
    return temp;
};

bstnode* BST::successor(bstnode* r)
{
    bstnode* temp = r;
    if(temp->right != nullptr)
        return minimum(temp->right);
    bstnode* y = temp->father;
    while(y != nullptr && temp == y->right)
    {
        temp = y;
        y = y->father;
    }
    return y;
}

bstnode* BST::predecessor(bstnode* r)
{
    bstnode* temp = r;
    if(temp->left != nullptr)
        return maximum(temp->left);
    bstnode* y = temp->father;
    while(y != nullptr && temp == y->left)
    {
        temp = y;
        y = y->father;
    }
    return y;
}

void BST::inOrder(bstnode* r)
{
    if(r != nullptr) {
        inOrder(r->left);
        std::cout << "| " << r->key << " |";
        inOrder(r->right);
    }
};

void BST::preOrder(bstnode* r)
{
    if(r != nullptr) {
        std::cout << "| " << r->key << " |";
        preOrder(r->left);
        preOrder(r->right);
    }
};

void BST::postOrder(bstnode* r)
{
    if(r != nullptr) {
        postOrder(r->left);
        postOrder(r->right);
        std::cout << "| " << r->key << " |";
    }
};

void BST::clearTree(bstnode* r)
{
    if(r != nullptr) {
        clearTree(r->left);
        clearTree(r->right);
        delete r;
    }
};
