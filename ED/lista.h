#include <iostream>

template <class T>
struct listnode
{
    int key; //guarda a chave do nó
    T data; //guarda o valor do no
    list<T> *next = nullptr; //ponteiro para o próximo no da lista
};

template <class T>
class Lista
{
private:
    listnode<T> *head; //cabeça da lista
public:
    Lista();
    ~Lista();
    bool checkEmpty(); //verifica se a list esta vazia
    void insert(int key, T data); //insere na lista o valor associado a chave
    void remove(int key); //remove da lista pela
    listnode<T> getNode(int key); //pega um nó da lista
    void displayItems(); //exibe os itens guardados na lista
};

template <class T>
Lista<T>::Lista()
{
    head = new listnode<T>;
};

template <class T>
Lista<T>::~Lista()
{
    listnode<T> *temp = head->next;
    while(head->next != nullptr)
    {
        head->next = temp->next;
        delete temp;
        temp = head->next;
    }
    delete head;
};

template <class T>
bool Lista<T>::checkEmpty()
{
    return head->next == nullptr;
};

template <class T>
void Lista<T>::insert(int key, T data)
{
    listnode<T> *temp = new listnode<T>;
    head->key = key;
    head->data = data;
    temp->next = head;
    head = temp;
};

template <class T>
void Lista<T>::remove(int key)
{
    listnode <T>*temp = head;
    while(temp->next != nullptr && temp->next->key != key)
        temp = temp->next;
    if(temp->next != nullptr) {
        listnode<T> *old = temp->next;
        temp->next = old->next;
        delete old;
    }
};

template <class T>
listnode<T> Lista<T>::getNode(int key)
{
    listnode<T> *temp = head->next;
    while(temp != nullptr && temp->key != key)
        temp = temp->next;
    return *temp;
};

template <class T>
void Lista<T>::displayItems()
{
    listnode<T> *temp = head->next;
    while(temp != nullptr)
    {
        std::cout << "| (" << temp->key << " , " << temp->data << ") |";
        temp = temp->next;
    }
};
