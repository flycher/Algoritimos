#include <iostream>

class Pilha
{
private:
    int* stack; //array com elementos na pilha
    int top; //onde no array esta o ultimo elemento
    int size; //tamanho maximo da pilha
public:
    Pilha(int size); //constroi o array que guarda os elementos
    ~Pilha(); //destroi o array
    bool checkEmpty(); //verifica se a pilha esta vazia
    int checkTop(); //verifica o topo da pilha
    void push(int elem); //insere um elemento na pilha
    void pop(); // remove um elemento da pilha
};

Pilha::Pilha(int size)
{
    this->stack = new int[size];
    this->top = 0;
    this->size = size;
};

Pilha::~Pilha()
{
    delete [] stack;
};

bool Pilha::checkEmpty()
{
    return !top;
};

int Pilha::checkTop()
{
    return stack[top - 1];
};

void Pilha::push(int elem)
{
    if(this->top == this->size)
        std::cerr << "Overflow!\n";
    else
        stack[top++] = elem;
};

void Pilha::pop()
{
    if(this->checkEmpty())
        std::cerr << "Underflow!\n";
    else
        top--;
};
