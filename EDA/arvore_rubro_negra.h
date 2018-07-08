#include <iostream>

enum rbtcolors { RED, BLACK};

template <class T>
struct rbtnode
{
    int key; //guarda a chave do nó
    T data; //guarda o valor do nó
    rbtnode<T> *parent, *left, *right; //pai e filhos
    rbtcolors color; //guarda a cor do nó
};

template <class T>
class RBTree
{
private:
    rbtnode<T> *root;
    rbtnode<T> *NIL;
public:
    RBTree();
    ~RBTree();
    rbtnode<T>* getRoot(); //retorna o nó raiz da arvore
    rbtnode<T>* search(int k); //procura o no com chave k na arvore
    void insert(int k, T d); //insere valor d com chave k na arvore
    void fixrbinsert(rbtnode<T>* z); //corrige as propriedades após inserção
    void leftrotation(rbtnode<T>* x); //rotação a esquerda
    void rightrotation(rbtnode<T>* y); //rotação a direita
    void transplant(rbtnode<T>* u, rbtnode<T>* v); //troca nós de posição
    void remove(int k); //remove nó com chave k da arvore
    void fixrbremove(rbtnode<T>* x); //corrige as propriedades após remoção
    rbtnode<T>* minimum(rbtnode<T>* r); //retorna no minimo da subarvore
    rbtnode<T>* maximum(rbtnode<T>* r); //retorna no maximo da subarvore
    rbtnode<T>* successor(int k); //retorna sucessor do nó de chave k
    rbtnode<T>* predecessor(int k); //retorna predecessor do nó de chave k
    void inOrder(rbtnode<T>* r); //percurso em order
    void preOrder(rbtnode<T>* r); //percurso pre order
    void postOrder(rbtnode<T>* r); //percurso pos order
    void clearTree(rbtnode<T>* r); //libera todos os nós da arvore
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
rbtnode<T>* RBTree<T>::search(int k)
{
    rbtnode<T> *temp = root;
    while(temp != NIL && temp->key != k)
    {
        if(k > temp->key)
            temp = temp->right;
        else
            temp = temp->left;
    }
    return temp;
};

template <class T>
void RBTree<T>::insert(int k, T d)
{
    rbtnode<T> *z = new rbtnode<T>;
    z->color = RED;
    z->data = d;
    z->key = k;
    z->parent = NIL;
    z->left = NIL;
    z->right = NIL;
    if(root == NIL) {
        root = z;
    } else {
        rbtnode<T> *temp = root, *y;
        while(temp != NIL)
        {
            y = temp;
            if(k < temp->key)
                temp = temp->left;
            else
                temp = temp->right;
        }
        z->parent = y;
        if(k < y->key)
            y->left = z;
        else
            y->right = z;
    }
    fixrbinsert(z);
};

template <class T>
void RBTree<T>::fixrbinsert(rbtnode<T>* z)
{
    rbtnode<T> *y; //y será o tio de z
    while(z->parent->color == RED) //verifica a cor do pai de z
    {
        if(z->parent == z->parent->parent->left) { //se o pai for filho esquerdo
            y = z->parent->parent->right; //y recebe o filho direito do avô
            if(y->color == RED) { //se o tio for vermelho
                z->parent->color = BLACK; //muda a cor do pai para preto
                y->color = BLACK; //muda a cor do tio para preto
                z->parent->parent->color = RED; //muda a cor do avô para vermelho
                z = z->parent->parent; //tornamos avô de z o novo z
            } else {
                if(z == z->parent->right) { //se z for filho direito
                    z = z->parent; //tornamos pai de z o novo z
                    leftrotation(z); //rotaciona z a esquerda
                }
                z->parent->color = BLACK; //mudamos a cor do parente para preto
                z->parent->parent->color = RED; //mudamos a cor do avô para vermelho
                rightrotation(z->parent->parent); //rotaciona o avô de z a direita
            }
        } else { //se o pai for filho direito
            y = z->parent->parent->left; //y recebe o filho esquerdo do avô
            if(y->color == RED) { //se o tio for vermelho
                z->parent->color = BLACK; //muda a cor do pai para preto
                y->color = BLACK; //muda a cor do tio para preto
                z->parent->parent->color = RED; //muda a cor do avô para vermelho
                z = z->parent->parent; //tornamos avô de z o novo z
            } else {
                if(z == z->parent->left) { //se z for filho esquerdo
                    z = z->parent; //tornamos pai de z o novo z
                    rightrotation(z); //rotaciona z a direita
                }
                z->parent->color = BLACK; //mudamos a cor do parente para preto
                z->parent->parent->color = RED; //mudamos a cor do avô para vermelho
                leftrotation(z->parent->parent); //rotaciona o avô de z a esquerda
            }
        }
    }
    root->color = BLACK;
};

template <class T>
void RBTree<T>::leftrotation(rbtnode<T>* x)
{
    rbtnode<T> *y = x->right; //atribui a subárvore direita de x a y
    x->right = y->left; //torna a subárvore esqueda de y na direita de x
    if(y->left != NIL)
        y->left->parent = x;
    y->parent = x->parent; //atribui o parente de x ao parente de y
    if(x->parent == NIL)
        root = y;
    else if(x == x->parent->left)
        x->parent->left = y;
    else
        x->parent->right = y;
    y->left = x; //atribui x a esquerda de y
    x->parent = y; //torna y pai de x
};

template <class T>
void RBTree<T>::rightrotation(rbtnode<T>* y)
{
    rbtnode<T> *x = y->left; //atribui a subárvore esquerda de y a x
    y->left = x->right; //torna a subárvore direita de x na direita de y
    if(x->right != NIL)
        x->right->parent = x;
    x->parent = y->parent; //atribui o parente de y ao parente de x
    if(y->parent == NIL)
        root = x;
    else if(y == y->parent->left)
        y->parent->left = x;
    else
        y->parent->right = x;
    x->right = y; //atribui y a direita de x
    y->parent = x; //torna x pai de y
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
void RBTree<T>::remove(int k)
{
    rbtnode<T> *z = search(k);
    rbtnode<T> *y = z, *x; //y sera o no a ser removido ou o que substirui z
    rbtcolors y_original_color = y->color; //a cor de y pode ser alterada
    if(z->left == NIL) { //caso z nao tenha filho esquerdo
        x = z->right; //caso z tenha um filho direito
        transplant(z, z->right); //mudamos z e o filho direito de posição
    } else if(z->right == NIL) { //caso z nao tenha filho direito
        x = z->left; //caso z tenha um filho esquerdo
        transplant(z, z->left); //mudamos z e o filho esquerdo de posição
    } else { //caso z tenha os 2 filhos
        y = minimum(z->right); //y assumira o lugar de z
        y_original_color = y->color; //guarda novamente a cor ao alterar o y
        x = y->right; //caso y tenha um filho, ele ocupara o lugar de y
        if(y->parent == z)
            x->parent = z;
        else {
            transplant(y, y->right);
            y->right = z->right;
            y->right->parent = y;
        }
        transplant(z, y);
        y->left = z->left;
        y->left->parent = y;
        y->color = z->color;
    }
    delete z;
    if(y_original_color == BLACK) //pode causar violações nas propriedades
        fixrbremove(x);

};

template <class T>
void RBTree<T>::fixrbremove(rbtnode<T>* x)
{
    rbtnode<T> *w; //w sera o irmão de x
    while(x != root && x->color == BLACK)
    {
        if(x == x->parent->left) { //caso x seja filho esquerdo
            w = x->parent->right; //w sera o filho direito
            if(w->color == RED) { //irmão tem cor vermelha
                w->color = BLACK; //muda cor do irmao
                x->parent->color = RED; //muda cor do pai
                leftrotation(x->parent); //rotaciona o pai a esquerda
                w = x->parent->right;
            }
            if(w->left->color == BLACK && w->right->color == BLACK) {
                w->color = RED; //caso os filhos de w sejam pretos, mudamos sua cor
                x = x->parent;
            } else {
                if(w->right->color == BLACK) { //apenas o filho direito e preto
                    w->left->color = BLACK;
                    w->color = RED;
                    rightrotation(w);
                    w = w->parent->right;
                }
                w->color = x->parent->color;
                x->parent->color = BLACK;
                w->right->color = BLACK;
                leftrotation(x->parent);
                x = root;
            }
        } else { //caso x seja filho direito
            w = x->parent->left; //w sera o filho esquerdo
            if(w->color == RED) { //irmão tem cor vermelha
                w->color = BLACK; //muda cor do irmao
                x->parent->color = RED; //muda cor do pai
                rightrotation(x->parent); //rotaciona o pai a direita
                w = x->parent->left;
            }
            if(w->right->color == BLACK && w->left->color == BLACK) {
                w->color = RED; //caso os filhos de w sejam pretos, mudamos sua cor
                x = x->parent;
            } else {
                if(w->left->color == BLACK) { //apenas o filho esquerdo e preto
                    w->right->color = BLACK;
                    w->color = RED;
                    leftrotation(w);
                    w = w->parent->left;
                }
                w->color = x->parent->color;
                x->parent->color = BLACK;
                w->left->color = BLACK;
                rightrotation(x->parent);
                x = root;
            }
        }
    }
    x->color = BLACK;
};

template <class T>
rbtnode<T>* RBTree<T>::minimum(rbtnode<T>* r)
{
    rbtnode<T> *temp = r;
    while(temp->left != NIL)
        temp = temp->left;
    return temp;
};

template <class T>
rbtnode<T>* RBTree<T>::maximum(rbtnode<T>* r)
{
    rbtnode<T> *temp = r;
    while(temp->right != NIL)
        temp = temp->right;
    return temp;
};

template <class T>
rbtnode<T>* RBTree<T>::successor(int k)
{
    rbtnode<T> *temp = search(k);
    if(temp->right != NIL)
        return minimum(temp->right);
    rbtnode<T>* y = temp->parent;
    while(y != NIL && temp == y->right)
    {
        temp = y;
        y = y->parent;
    }
    return y;
};

template <class T>
rbtnode<T>* RBTree<T>::predecessor(int k)
{
    rbtnode<T> *temp = search(k);
    if(temp->left != NIL)
        return maximum(temp->left);
    rbtnode<T>* y = temp->parent;
    while(y != NIL && temp == y->left)
    {
        temp = y;
        y = y->parent;
    }
    return y;
};

template <class T>
void RBTree<T>::inOrder(rbtnode<T>* r)
{
    if(r != NIL) {
        inOrder(r->left);
        std::cout << "| (" << r->key << ',' << r->color << ") |";
        inOrder(r->right);
    }
};

template <class T>
void RBTree<T>::preOrder(rbtnode<T>* r)
{
    if(r != NIL) {
        std::cout << "| (" << r->key << ',' << r->color << ") |";
        preOrder(r->left);
        preOrder(r->right);
    }
};

template <class T>
void RBTree<T>::postOrder(rbtnode<T>* r)
{
    if(r != NIL) {
        postOrder(r->left);
        postOrder(r->right);
        std::cout << "| (" << r->key << ',' << r->color << ") |";
    }
};

template <class T>
void RBTree<T>::clearTree(rbtnode<T>* r)
{
    if(r != NIL) {
        clearTree(r->left);
        clearTree(r->right);
        delete r;
    }
};

template <class T>
void RBTree<T>::bshow_dual(rbtnode<T>* node, std::string heranca, std::ostream& fout)
{
    if(node != NIL && (node->left != NIL || node->right != NIL))
        bshow_dual(node->right , heranca + "r", fout);
    int tam = heranca.size();
    for(int i = 0; i < tam - 1; i++) {
        if(heranca[i] != heranca[i + 1])
            fout << "│" << "   ";
        else
            fout << " " << "   ";
    }
    if(heranca != "") {
        if(heranca.back() == 'r')
            fout << "┌───";
        else
            fout << "└───";
    }
    if(node == NIL) {
        fout << "#" << std::endl;
        return;
    }
    fout << node->key << ',' << node->color << std::endl;
    if(node != NIL && (node->left != NIL || node->right != NIL))
        bshow_dual(node->left, heranca + "l", fout);
}
