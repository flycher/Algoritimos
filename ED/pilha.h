#include <iostream>

template <class T>
class Pilha
{
private:
    T* stack; //array com elementos na pilha
    int top; //onde no array esta o ultimo elemento
    int size; //tamanho maximo da pilha
public:
    Pilha(int size); //constroi o array que guarda os elementos
    ~Pilha(); //destroi o array
    bool checkEmpty(); //verifica se a pilha esta vazia
    T checkTop(); //verifica o topo da pilha
    void push(T elem); //insere um elemento na pilha
    void pop(); // remove um elemento da pilha
};

template <class T>
Pilha<T>::Pilha(int size)
{
    this->stack = new T[size];
    this->top = 0;
    this->size = size;
};

template <class T>
Pilha<T>::~Pilha()
{
    delete [] stack;
};

template <class T>
bool Pilha<T>::checkEmpty()
{
    return !top;
};

template <class T>
T Pilha<T>::checkTop()
{
    return stack[top - 1];
};

template <class T>
void Pilha<T>::push(T elem)
{
    if(this->top == this->size)
        std::cerr << "Overflow!\n";
    else
        stack[top++] = elem;
};

template <class T>
void Pilha<T>::pop()
{
    if(this->checkEmpty())
        std::cerr << "Underflow!\n";
    else
        top--;
};
