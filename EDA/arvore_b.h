#ifndef GUARD_arvore_b_h
#define GUARD_arvore_b_h

#include <iostream>
#include <queue>

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
    //funçoes de remoção adaptadas de https://www.geeksforgeeks.org/b-tree-set-3delete/
    int findKey(btreenode<T>* node, int key); //acha a posição da chave primeira maior no nó
    void removeFromNode(btreenode<T>* node, int key); //remove o elemento de um nó
    void removeFromLeaf(btreenode<T>* node, int index); //remove de um nó folha
    void removeFromInternal(btreenode<T>* node, int index); //remove de um nó interno
    std::pair<btreenode<T>*, int> getPred(btreenode<T>* node, int index); //retorna nó e posição do predecessor
    std::pair<btreenode<T>*, int> getSucc(btreenode<T>* node, int index); //retorna nó e posição do sucessor
    void fill(btreenode<T>* node, int index); //redistribuição
    void merge(btreenode<T>* node, int index); //fusão
    void borrowFromNext(btreenode<T>* node, int index); //pega uma chave do filho posterior
    void borrowFromPrev(btreenode<T>* node, int index); //pega uma chave do filho anterior

public:
    BTree(int degree);
    ~BTree();
    btreenode<T>* getRoot(); //retona a raiz da árvore
    std::pair<btreenode<T>*, int> search(int key, btreenode<T>* node); //retorna o nó e posição que se encontra a chave
    void insert(int key, T data); //insere um elemento na árvore
    void remove(int key); //remove um elemento da árvore
    void traverseInOrder(btreenode<T>* node); //percorre a árvore em ordem
    void showBtree(btreenode<T>* node); ////mostra os nós da árvore

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
std::pair<btreenode<T>*, int> BTree<T>::search(int key, btreenode<T>* node)
{
    int i = 0;
    //acha a posição da primeira chave maior ou igual a key
    while (i < node->n_of_elements && key > node->keys[i])
        i++;

    if (node->keys[i] == key)
        return std::make_pair(node, i);

    if (node->is_leaf) //se a chave não foi encontrada e estamos numa folha
        return std::make_pair(node, -1); //-1 aponta que a chave não está na árvore

    return search(key, node->children[i]); //procura no nó apropriado
};


template <class T>
void BTree<T>::insert(int key, T data)
{
    std::pair<btreenode<T>*, int> repeated = search(key, root);

    if(repeated.second != -1)
        std::cerr << "Key already in the tree.\n";

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
void BTree<T>::remove(int key)
{
    removeFromNode(root, key);

    if (root->n_of_elements == 0) //se a raiz fiou sem elementos
    {
        btreenode<T> *temp = root;
        if (root->is_leaf) //se ela e o unico nó
            root = new btreenode<T>(degree, true, 0); //cria nova raiz
        else
            root = root->children[0]; //raiz vira seu filho

        delete temp;
    }
};

template <class T>
int BTree<T>::findKey(btreenode<T>* node, int key)
{
    int index = 0;

    while (index < node->n_of_elements && node->keys[index] < key)
        index++;

    return index;
};

template <class T>
void BTree<T>::removeFromNode(btreenode<T>* node, int key)
{
    int index = findKey(node, key);

    if (index < node->n_of_elements && node->keys[index] == key) //se a chave está nesse nó
    {
        if (node->is_leaf)
            removeFromLeaf(node, index);
        else
            removeFromInternal(node, index);
    }
    else //se não está
    {
        if(node->is_leaf) //chave não esta no nó e este é folha
            std::cerr << "Key not in the tree.\n";
        else
        {
            //caso nó em que a chave pode estar dem degree - 1 nós
            if (node->children[index]->n_of_elements < degree)
                fill(node, index);

            //se o filho que foi fundido estava na ultima posição, esta foi
            //fundida com o filho anterior
            if (index == node->n_of_elements && index > node->n_of_elements)
                removeFromNode(node->children[index - 1], key);
            else //se não, chamanos no filho que terá pelo menos degree chaves
                removeFromNode(node->children[index], key);
        }
    }
};

template <class T>
void BTree<T>::removeFromLeaf(btreenode<T>* node, int index)
{
    for (int i = index + 1; i < node->n_of_elements; i++) //move os elementos
    {
        node->keys[i - 1] = node->keys[i];
        node->data[i - 1] = node->data[i];
    }

    node->n_of_elements--; //reduz o número de elementos no nó
};

template <class T>
void BTree<T>::removeFromInternal(btreenode<T>* node, int index)
{
    int key = node->keys[index];

    //se o filho em index tem pelomenos degree chaves, acha o predecessor nele
    if(node->children[index]->n_of_elements >= degree)
    {
        std::pair<btreenode<T>*, int> pred = getPred(node, index);
        int pred_key = pred.first->keys[pred.second];
        T pred_data = pred.first->data[pred.second];
        //troca o elemento por seu predecessor
        node->keys[index] = pred_key;
        node->data[index] = pred_data;
        removeFromNode(node->children[index], pred_key);
    }
    //se o filho em index + 1 tem pelomenos degree chaves, acha o sucessor nele
    else if(node->children[index + 1]->n_of_elements >= degree)
    {
        std::pair<btreenode<T>*, int> succ = getSucc(node, index);
        int succ_key = succ.first->keys[succ.second];
        T succ_data = succ.first->data[succ.second];
        //troca o elemento por seu sucessor
        node->keys[index] = succ_key;
        node->data[index] = succ_data;
        removeFromNode(node->children[index + 1], succ_key);
    }
    //se ambos tem menos de degree elementos, fundimos esses e procuramos nesse novo nó
    else
    {
        merge(node, index);
        removeFromNode(node->children[index], key);
    }
};


template <class T>
std::pair<btreenode<T>*, int> BTree<T>::getPred(btreenode<T>* node, int index)
{
    btreenode<T> *current = node->children[index];

    while (!current->is_leaf) //move no filho mais a direita até chegar numa folha
        current = current->children[current->n_of_elements];

    int n = current->n_of_elements - 1;

    return std::make_pair(current, n); //retorna o nó e a posição do sucessor
};

template <class T>
std::pair<btreenode<T>*, int> BTree<T>::getSucc(btreenode<T>* node, int index)
{
    btreenode<T> *current = node->children[index + 1];

    while (!current->is_leaf) //move no filho mais a esquerda até chegar numa folha
        current = current->children[0];

    return std::make_pair(current, 0); //retorna o nó e a posição do sucessor
};

template <class T>
void BTree<T>::fill(btreenode<T>* node, int index)
{
    //se o filho anterior tem mais de degree + 1 elementos, pega um emprestado
    if (index != 0 && node->children[index - 1]->n_of_elements >= degree)
        borrowFromPrev(node, index);
    //se o filho posteriot tem mais de degree + 1 elementos, pega um emprestado
    else if (index != node->n_of_elements && node->children[index + 1]->n_of_elements >= degree)
        borrowFromNext(node, index);
    //reazila a fusão dos irmãos
    else
    {
        if (index != node->n_of_elements) //se for o ultimo filho funde com o anterior
            merge(node, index);
        else //se não une com o posterior
            merge(node, index-1);
    }
};

template <class T>
void BTree<T>::merge(btreenode<T>* node, int index)
{
    btreenode<T> *child = node->children[index];
    btreenode<T> *sibling = node->children[index + 1];

    //pega um elemento do nó e insere no em child
    child->keys[degree - 1] = node->keys[index];
    child->data[degree - 1] = node->data[index];

    for (int i = 0; i < sibling->n_of_elements; i++) //copia as chave de um filho para o outro
    {
        child->keys[i + degree] = sibling->keys[i];
        child->data[i + degree] = sibling->data[i];
    }

    if (!child->is_leaf) //se não forem folha
    {
        for(int i = 0; i <= sibling->n_of_elements; i++) //copia os nós de um filho para o outro
            child->children[i + degree] = sibling->children[i];
    }

    //preenche o espaço criado ao mover o elemento de node para child
    for (int i = index + 1; i < node->n_of_elements; i++)
    {
        node->keys[i - 1] = node->keys[i];
        node->data[i - 1] = node->data[i];
    }

    for (int i = index + 2; i <= node->n_of_elements; i++) //move os nós
        node->children[i - 1] = node->children[i];

    //atualiza a quantidade de elementos em child e nó
    child->n_of_elements += sibling->n_of_elements + 1;
    node->n_of_elements--;

    delete sibling; //libera o nó agora vazio
};

template <class T>
void BTree<T>::borrowFromPrev(btreenode<T>* node, int index)
{
    btreenode<T> *child = node->children[index];
    btreenode<T> *sibling = node->children[index-1];

    for (int i = child->n_of_elements - 1; i >= 0; i--) //cria espaço para o novo elemento
    {
        child->keys[i + 1] = child->keys[i];
        child->data[i + 1] = child->data[i];
    }

    if (!child->is_leaf) //se não for uma folha move os nós
    {
        for(int i = child->n_of_elements; i >= 0; i--)
            child->children[i + 1] = child->children[i];
    }

    //copia a ultima chave de node para child
    child->keys[0] = node->keys[index - 1];
    child->data[0] = node->data[index - 1];

    //move o ultimo nó do irmão para child se não for folha
    if(!child->is_leaf)
        child->children[0] = sibling->children[sibling->n_of_elements];

    //move a chave do irmão para o parente
    node->keys[index - 1] = sibling->keys[sibling->n_of_elements - 1];
    node->data[index - 1] = sibling->data[sibling->n_of_elements - 1];

    //atualiza a quanditade de elementos nos nós
    child->n_of_elements++;
    sibling->n_of_elements--;
};

template <class T>
void BTree<T>::borrowFromNext(btreenode<T>* node, int index)
{
    btreenode<T> *child = node->children[index];
    btreenode<T> *sibling = node->children[index + 1];

    //copia a chave de node para a ultima posição de child
    child->keys[child->n_of_elements] = node->keys[index];
    child->data[child->n_of_elements] = node->data[index];

    if (!child->is_leaf) //copia o primeiro filho de sibling para a ultima posiçao de child
        child->children[child->n_of_elements + 1] = sibling->children[0];

    //copia a primeira chave de silbing para node
    node->keys[index] = sibling->keys[0];
    node->data[index] = sibling->data[0];

    //move os elementos de sibling
    for (int i = 1; i < sibling->n_of_elements; i++)
    {
        sibling->keys[i - 1] = sibling->keys[i];
        sibling->data[i - 1] = sibling->data[i];
    }

    if (!sibling->is_leaf) //move os filhos
    {
        for(int i = 1; i <= sibling->n_of_elements; i++)
            sibling->children[i - 1] = sibling->children[i];
    }

    //atualiza a quanditade de elementos nos nós
    child->n_of_elements++;
    sibling->n_of_elements--;
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
void BTree<T>::showBtree(btreenode<T>* node)
{
    std::queue<btreenode<T>*> nodes;
    btreenode<T> *current;
    int i, n;
    nodes.push(node);

    while(!nodes.empty())
    {
        current = nodes.front();
        nodes.pop();
        n = current->n_of_elements;
        std::cout << '[';
        for (i = 0; i < n; i++)
        {
            std::cout << current->keys[i]  << ',';
        }
        std::cout << ']';

        if(!current->is_leaf)
        {
            for (i = 0; i <= n; i++)
            {
                nodes.push(current->children[i]);
            }
        }
    }
};

#endif
