#ifndef GUARD_fila_h
#define GUARD_fila_h

#include <iostream>

template <class T>
class Fila
{
private:
    T* queue; //array com elementos na pilha
    int head; //onde no array esta o primeiro elemento
    int tail; //onde no array esta o ultimo elemento
    int size; //tamanho maximo da fila

public:
    Fila(int size); //constroi o array que guarda os elementos
    ~Fila(); //destroi o array
    bool checkEmpty(); //verifica se a fila esta vazia
    T checkHead(); //verifica o inicio da fila
    void enqueue(T elem); //insere um elemento na fila
    void dequeue(); // remove um elemento da fila
};

template <class T>
Fila<T>::Fila(int size)
{
    this->queue = new T[size + 1];
    this->head = 0;
    this->tail = 1;
    this->size = size + 1;
};

template <class T>
Fila<T>::~Fila()
{
    delete [] this->queue;
}

template <class T>
bool Fila<T>::checkEmpty()
{
    return (head == tail - 1 || head == tail - 1 + size);
};

template <class T>
T Fila<T>::checkHead()
{
    return queue[(head + 1) % size];
};

template <class T>
void Fila<T>::enqueue(T elem)
{
    if(this->head == this->tail)
        std::cerr << "Overflow!\n";
    else
    {
        queue[tail++] = elem;
        tail = tail % size;
    }
};

template <class T>
void Fila<T>::dequeue()
{
    if(this->checkEmpty())
        std::cerr << "Underflow!\n";
    else
    {
        head++;
        head = head % size;
    }
};

#endif
