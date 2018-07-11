#include <iostream>

enum rbtcolors { RED, BLACK };

template <class T>
struct rbtnode
{
    int key; //guarda a chave do nó
    T data; //guarda o dado do nó
    rbtcolors color; //guarda a cor do nó
    rbtnode<T> *parent, *left, *right; //pai e filhos

    rbtnode() {};

    rbtnode(int key, T data, rbtcolors color, rbtnode<T> *node)
    {
        this->key = key;
        this->data = data;
        this->color = color;
        this->parent = this->left = this->right = node;
    };
};

template <class T>
class RBTree
{
private:
    rbtnode<T> *root;
    rbtnode<T> *NIL;
    void fixrbinsert(rbtnode<T>* node); //corrige as propriedades após inserção
    void leftrotation(rbtnode<T>* node); //rotação a esquerda
    void rightrotation(rbtnode<T>* node); //rotação a direita
    void transplant(rbtnode<T>* u, rbtnode<T>* v); //troca nós de posição
    void fixrbremove(rbtnode<T>* node); //corrige as propriedades após remoção
    rbtnode<T>* minimum(rbtnode<T>* node); //retorna no minimo da subarvore
    rbtnode<T>* maximum(rbtnode<T>* node); //retorna no maximo da subarvore
    void clearTree(rbtnode<T>* node); //libera todos os nós da arvore

public:
    RBTree();
    ~RBTree();
    rbtnode<T>* getRoot(); //retorna o nó raiz da arvore
    std::pair<rbtnode<T>*, bool> search(int key); //procura o no com chave key na arvore
    void insert(int key, T data); //insere dado data com chave key na arvore
    void remove(int key); //remove nó com chave key da arvore
    rbtnode<T>* successor(int key); //retorna sucessor do nó de chave key
    rbtnode<T>* predecessor(int key); //retorna predecessor do nó de chave key
    void inOrder(rbtnode<T>* node); //percurso em order
    void preOrder(rbtnode<T>* node); //percurso pre order
    void postOrder(rbtnode<T>* node); //percurso pos order
    //mostra uma arvore binária formatada. Pelo professor David Sena.
    //https://github.com/senapk/btree_formatada
    void bshow_dual(rbtnode<T>* node, std::string heranca, std::ostream& fout);
};

template <class T>
RBTree<T>::RBTree()
{
    NIL = new rbtnode<T>;
    NIL->color = BLACK;
    NIL->parent = NIL;
    NIL->left = NIL;
    NIL->right = NIL;
    root = NIL;
};

template <class T>
RBTree<T>::~RBTree()
{
    clearTree(root);
    delete NIL;
};


template <class T>
rbtnode<T>* RBTree<T>::getRoot()
{
    return root;
};

template <class T>
std::pair<rbtnode<T>*, bool> RBTree<T>::search(int key)
{
    rbtnode<T> *temp = root;

    while(temp != NIL && temp->key != key)
    {
        if(key > temp->key)
            temp = temp->right;
        else
            temp = temp->left;
    }

    return std::make_pair(temp, temp->key == key);
};

template <class T>
void RBTree<T>::insert(int key, T data)
{
    rbtnode<T> *newnode = new rbtnode<T>(key, data, RED, NIL);
    bool repeated = false;

    if(root == NIL)
    {
        root = newnode;
        root->color = BLACK;
    }
    else
    {
        rbtnode<T> *temp = root, *parent;

        while(temp != NIL)
        {
            parent = temp;

            if(key == temp->key)
            {
                repeated = true;
                break;
            }

            if(key < temp->key)
                temp = temp->left;
            else
                temp = temp->right;
        }

        if(!repeated)
        {
            newnode->parent = parent;

            if(key < parent->key)
                parent->left = newnode;
            else
                parent->right = newnode;

            fixrbinsert(newnode);
        }
        else
            std::cerr << "Key already in the tree.\n";
    }
};

template <class T>
void RBTree<T>::fixrbinsert(rbtnode<T>* node)
{
    rbtnode<T> *uncle; //uncle será o tio de node

    while(node->parent->color == RED) //verifica a cor do pai de node
    {
        if(node->parent == node->parent->parent->left) //se o pai for filho esquerdo
        {
            uncle = node->parent->parent->right; //uncle recebe o filho direito do avô

            if(uncle->color == RED) //se o tio for vermelho
            {
                node->parent->color = BLACK; //muda a cor do pai para preto
                uncle->color = BLACK; //muda a cor do tio para preto
                node->parent->parent->color = RED; //muda a cor do avô para vermelho
                node = node->parent->parent; //tornamos avô de node o novo node
            }
            else
            {
                if(node == node->parent->right) //se node for filho direito
                {
                    node = node->parent; //tornamos pai de node o novo node
                    leftrotation(node); //rotaciona node a esquerda
                }

                node->parent->color = BLACK; //mudamos a cor do parente para preto
                node->parent->parent->color = RED; //mudamos a cor do avô para vermelho
                rightrotation(node->parent->parent); //rotaciona o avô de node a direita
            }
        }
        else //se o pai for filho direito
        {
            uncle = node->parent->parent->left; //uncle recebe o filho esquerdo do avô

            if(uncle->color == RED)  //se o tio for vermelho
            {
                node->parent->color = BLACK; //muda a cor do pai para preto
                uncle->color = BLACK; //muda a cor do tio para preto
                node->parent->parent->color = RED; //muda a cor do avô para vermelho
                node = node->parent->parent; //tornamos avô de node o novo node
            }
            else
            {
                if(node == node->parent->left) //se node for filho esquerdo
                {
                    node = node->parent; //tornamos pai de node o novo node
                    rightrotation(node); //rotaciona node a direita
                }

                node->parent->color = BLACK; //mudamos a cor do parente para preto
                node->parent->parent->color = RED; //mudamos a cor do avô para vermelho
                leftrotation(node->parent->parent); //rotaciona o avô de node a esquerda
            }
        }
    }

    root->color = BLACK;
};

template <class T>
void RBTree<T>::leftrotation(rbtnode<T>* node)
{
    rbtnode<T> *rightchild = node->right; //atribui a subárvore direita de node a rightchild
    node->right = rightchild->left; //torna a subárvore esqueda de rightchild na direita de node

    if(rightchild->left != NIL)
        rightchild->left->parent = node;

    rightchild->parent = node->parent; //atribui o parente de node ao parente de rightchild

    if(node->parent == NIL)
        root = rightchild;
    else if(node == node->parent->left)
        node->parent->left = rightchild;
    else
        node->parent->right = rightchild;

    rightchild->left = node; //atribui node a esquerda de rightchild
    node->parent = rightchild; //torna rightchild pai de node
};

template <class T>
void RBTree<T>::rightrotation(rbtnode<T>* node)
{
    rbtnode<T> *leftchild = node->left; //atribui a subárvore esquerda de node a leftchild
    node->left = leftchild->right; //torna a subárvore direita de leftchild na direita de node

    if(leftchild->right != NIL)
        leftchild->right->parent = node;

    leftchild->parent = node->parent; //atribui o parente de node ao parente de leftchild

    if(node->parent == NIL)
        root = leftchild;
    else if(node == node->parent->left)
        node->parent->left = leftchild;
    else
        node->parent->right = leftchild;

    leftchild->right = node; //atribui node a direita de leftchild
    node->parent = leftchild; //torna leftchild pai de node
};

template <class T>
void RBTree<T>::transplant(rbtnode<T>* u, rbtnode<T>* v)
{
    if(u->parent == NIL)
        root = v;
    else if(u == u->parent->left)
        u->parent->left = v;
    else
        u->parent->right = v;

    v->parent = u->parent;
};

template <class T>
void RBTree<T>::remove(int key)
{
    rbtnode<T> *old = search(key);

    if(old == NIL)
        std::cerr << "Key not in the tree.\n";
    else
    {
        rbtnode<T> *sub = old, *replacement; //sub será o nó a ser removido ou o que substituirá old
        rbtcolors sub_original_color = sub->color; //a cor de sub pode ser alterada

        if(old->left == NIL) //caso old nao tenha filho esquerdo
        {
            replacement = old->right; //caso old tenha um filho direito
            transplant(old, old->right); //mudamos old e o filho direito de posição
        }
        else if(old->right == NIL) //caso old nao tenha filho direito
        {
            replacement = old->left; //caso old tenha um filho esquerdo
            transplant(old, old->left); //mudamos old e o filho esquerdo de posição
        }
        else //caso old tenha os 2 filhos
        {
            sub = minimum(old->right); //sub assumira o lugar de old
            sub_original_color = sub->color; //guarda novamente a cor ao alterar o sub
            replacement = sub->right; //caso sub tenha um filho, ele ocupara o lugar de sub

            if(sub->parent == old)
                replacement->parent = old;
            else
            {
                transplant(sub, sub->right);
                sub->right = old->right;
                sub->right->parent = sub;
            }

            transplant(old, sub);
            sub->left = old->left;
            sub->left->parent = sub;
            sub->color = old->color;
        }

        delete old;

        if(sub_original_color == BLACK) //pode causar violações nas propriedades
            fixrbremove(replacement);
    }
};

template <class T>
void RBTree<T>::fixrbremove(rbtnode<T>* node)
{
    rbtnode<T> *brother; //brother sera o irmão de node

    while(node != root && node->color == BLACK)
    {
        if(node == node->parent->left) //caso node seja filho esquerdo
        {
            brother = node->parent->right; //brother sera o filho direito

            if(brother->color == RED) //irmão tem cor vermelha
            {
                brother->color = BLACK; //muda cor do irmao
                node->parent->color = RED; //muda cor do pai
                leftrotation(node->parent); //rotaciona o pai a esquerda
                brother = node->parent->right;
            }

            if(brother->left->color == BLACK && brother->right->color == BLACK)
            {
                brother->color = RED; //caso os filhos de brother sejam pretos, mudamos sua cor
                node = node->parent;
            }
            else
            {
                if(brother->right->color == BLACK)  //apenas o filho direito e preto
                {
                    brother->left->color = BLACK;
                    brother->color = RED;
                    rightrotation(brother);
                    brother = brother->parent->right;
                }

                brother->color = node->parent->color;
                node->parent->color = BLACK;
                brother->right->color = BLACK;
                leftrotation(node->parent);
                node = root;
            }
        }
        else //caso node seja filho direito
        {
            brother = node->parent->left; //brother sera o filho esquerdo

            if(brother->color == RED) //irmão tem cor vermelha
            {
                brother->color = BLACK; //muda cor do irmao
                node->parent->color = RED; //muda cor do pai
                rightrotation(node->parent); //rotaciona o pai a direita
                brother = node->parent->left;
            }

            if(brother->right->color == BLACK && brother->left->color == BLACK)
            {
                brother->color = RED; //caso os filhos de brother sejam pretos, mudamos sua cor
                node = node->parent;
            }
            else
            {
                if(brother->left->color == BLACK)  //apenas o filho esquerdo e preto
                {
                    brother->right->color = BLACK;
                    brother->color = RED;
                    leftrotation(brother);
                    brother = brother->parent->left;
                }

                brother->color = node->parent->color;
                node->parent->color = BLACK;
                brother->left->color = BLACK;
                rightrotation(node->parent);
                node = root;
            }
        }
    }

    node->color = BLACK;
};

template <class T>
rbtnode<T>* RBTree<T>::minimum(rbtnode<T>* node)
{
    rbtnode<T> *temp = node;

    while(temp->left != NIL)
        temp = temp->left;

    return temp;
};

template <class T>
rbtnode<T>* RBTree<T>::maximum(rbtnode<T>* node)
{
    rbtnode<T> *temp = node;

    while(temp->right != NIL)
        temp = temp->right;

    return temp;
};

template <class T>
rbtnode<T>* RBTree<T>::successor(int key)
{
    rbtnode<T> *temp = search(key);

    if(temp->right != NIL)
        return minimum(temp->right);

    rbtnode<T>* pred = temp->parent;

    while(pred != NIL && temp == pred->right)
    {
        temp = pred;
        pred = pred->parent;
    }

    return pred;
};

template <class T>
rbtnode<T>* RBTree<T>::predecessor(int key)
{
    rbtnode<T> *temp = search(key);

    if(temp->left != NIL)
        return maximum(temp->left);

    rbtnode<T>* pred = temp->parent;

    while(pred != NIL && temp == pred->left)
    {
        temp = pred;
        pred = pred->parent;
    }
    return pred;
};

template <class T>
void RBTree<T>::inOrder(rbtnode<T>* node)
{
    if(node != NIL) {
        inOrder(node->left);
        std::cout << "| " << node->key << ',' << node->color << " |";
        inOrder(node->right);
    }
};

template <class T>
void RBTree<T>::preOrder(rbtnode<T>* node)
{
    if(node != NIL) {
        std::cout << "| " << node->key << ',' << node->color << " |";
        preOrder(node->left);
        preOrder(node->right);
    }
};

template <class T>
void RBTree<T>::postOrder(rbtnode<T>* node)
{
    if(node != NIL) {
        postOrder(node->left);
        postOrder(node->right);
        std::cout << "| " << node->key << ',' << node->color << " |";
    }
};

template <class T>
void RBTree<T>::clearTree(rbtnode<T>* node)
{
    if(node != NIL) {
        bstnode<T> *left = node->left, right = node->right;
        delete node;
        clearTree(node->left);
        clearTree(node->right);
    }
};

template <class T>
void RBTree<T>::bshow_dual(rbtnode<T>* node, std::string heranca, std::ostream& fout)
{
    if(node != NIL && (node->left != NIL || node->right != NIL))
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

    if(node == NIL)
    {
        fout << "#" << std::endl;
        return;
    }

    fout << node->key << ',' << node->color << std::endl;

    if(node != NIL && (node->left != NIL || node->right != NIL))
        bshow_dual(node->left, heranca + "l", fout);
}
