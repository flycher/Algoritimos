#include <iostream>

template <class T>
struct listnode
{
    T data; //guarda o dado do nó
    listnode<T> *next = nullptr; //ponteiro para o próximo nó da lista
};

template <class T>
class Lista
{
private:
    listnode<T> *head; //cabeça da lista

public:
    Lista();
    ~Lista();
    bool checkEmpty(); //verifica se a lista esta vazia
    void insert(T data); //insere o item na lista
    void remove(T data); //remove o item da lista
    listnode<T> getNode(T data); //pega um nó da lista
    void displayItems(); //exibe os itens guardados na lista
    void listshow();
};

template <class T>
Lista<T>::Lista()
{
    this->head = new listnode<T>;
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
    delete this->head;
};

template <class T>
bool Lista<T>::checkEmpty()
{
    return (head->next == nullptr);
};

template <class T>
void Lista<T>::insert(T data)
{
    listnode<T> *temp = new listnode<T>;
    head->data  = data;
    temp->next  = head;
    head        = temp;
};

template <class T>
void Lista<T>::remove(T data)
{
    listnode<T> *temp = head;

    while(temp->next != nullptr && temp->next->data != data)
        temp = temp->next;

    if(temp->next != nullptr)
    {
        listnode<T> *old = temp->next;
        temp->next = old->next;
        delete old;
    }
};

template <class T>
listnode<T> Lista<T>::getNode(T data)
{
    listnode<T> *temp = head->next;

    while(temp != nullptr && temp->data != data)
        temp = temp->next;

    return *temp;
};

template <class T>
void Lista<T>::displayItems()
{
    listnode<T> *temp = head->next;

    while(temp != nullptr)
    {
        std::cout << "| " << temp->data << " |";
        temp = temp->next;
    }
};

template <class T>
void Lista<T>::listshow()
{
    listnode<T> *temp = head->next;

    while(temp != nullptr)
    {
        std::cout << "[ " << temp->data << " |-]-> ";
        temp = temp->next;
    }

    std::cout << "NULL";
};
