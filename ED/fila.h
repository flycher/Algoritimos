#include <iostream>

class Fila
{
private:
    int* queue; //array com elementos na pilha
    int head; //onde no array esta o primeiro elemento
    int tail; //onde no array esta o ultimo elemento
    int size; //tamanho maximo da pilha
public:
    Fila(int size);
    ~Fila();
    bool checkEmpty(); //verifica se a fila esta vazia
    int checkHead(); //verifica o inicio da fila
    void enqueue(int elem); //insere um elemento na fila
    void dequeue(); // remove um elemento da fila
};

Fila::Fila(int size)
{
    this->queue = new int[size + 1];
    this->head = 0;
    this->tail = 1;
    this->size = size + 1;
};

Fila::~Fila()
{
    delete [] queue;
}

bool Fila::checkEmpty()
{
    return (head == tail - 1 || head == tail - 1 + size);
};

int Fila::checkHead()
{
    return queue[(head + 1) % size];
};

void Fila::enqueue(int elem)
{
    if(this->head == this->tail)
        std::cerr << "Overflow!\n";
    else {
        queue[tail++] = elem;
        tail = tail % size;
    }
};

void Fila::dequeue()
{
    if(this->checkEmpty())
        std::cerr << "Underflow!\n";
    else {
        head++;
        head = head % size;
    }
};
