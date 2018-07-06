#include <iostream>

struct node
{
    int data; //guarda o valor no nó
    node *next = nullptr; //ponteiro para o próximo no da lista
};

class Lista
{
private:
    node *head; //cabeça da lista
public:
    Lista();
    ~Lista();
    bool checkEmpty(); //verifica se a list esta vazia
    void insert(int data); //insere na lista
    void remove(int data); //remove da lista
    node getNode(int data); //pega um nó da lista
    void displayData(); //exibe os valores guardados na lista
};

Lista::Lista()
{
    head = new node;
};

Lista::~Lista()
{
    node *temp = head->next;
    while(head->next != nullptr)
    {
        head->next = temp->next;
        delete temp;
        temp = head->next;
    }
    delete head;
};

bool Lista::checkEmpty()
{
    return head->next == nullptr;
};

void Lista::insert(int data)
{
    node *temp = new node;
    head->data = data;
    temp->next = head;
    head = temp;
};

void Lista::remove(int data)
{
    node *temp = head;
    while(temp->next != nullptr && temp->next->data != data)
        temp = temp->next;
    if(temp->next != nullptr) {
        node *old = temp->next;
        temp->next = old->next;
        delete old;
    }
};

node Lista::getNode(int data)
{
    node *temp = head->next;
    while(temp != nullptr && temp->data != data)
        temp = temp->next;
    return *temp;
};

void Lista::displayData()
{
    node *temp = head->next;
    while(temp != nullptr)
    {
        std::cout << temp->data << ' ';
        temp = temp->next;
    }
};
