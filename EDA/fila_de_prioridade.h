#include <iostream>
#include <climits>

template <class T>
struct heapnode
{
    int key;
    T data;

    heapnode() {};

    heapnode(int key, T data)
    {
        this->key = key;
        this->data = data;
    }
};

template <class T>
class HeapMin
{
private:
    heapnode<T> *priority_queue; //array que guardara os elementos do heap
    int size; //tamanho maximo do heap
    int heap_size; //quantidade de elementos no heap

    void exchange(heapnode<T> *a, heapnode<T> *b) //troca nós de posição
    {
        heapnode<T> temp = *a;
        *a = *b;
        *b = temp;
    };

    void up(int i) //sobe nó apos inserção ou que diminuiu a chave
    {
        while(i > 0)
        {
            if(priority_queue[i].key < priority_queue[(i - 1) /  2].key)
            {
                exchange(&priority_queue[i], &priority_queue[(i - 1) /  2]);
                i = (i - 1) /  2;
            }
            else
                i = 0;
        }
    };

    void down(int i) //desce nó apos remoção ou que aumentou a chave
    {
        int j = 2 * i + 1;

        while(j <= heap_size)
        {
            if(j < heap_size)
            {
                if(priority_queue[j + 1].key < priority_queue[j].key)
                    j = j + 1;
            }

            if(priority_queue[i].key > priority_queue[j].key)
            {
                exchange(&priority_queue[i], &priority_queue[j]);
                i = j;
                j = 2 * i + 1;
            }
            else
                j = heap_size + 1;
        }
    };

public:
    HeapMin(int size)
    {
        this->size = size;
        this->priority_queue = new heapnode<T>[this->size];
        this->heap_size = 0;
    };

    ~HeapMin()
    {
        delete [] this->priority_queue;
    };

    T getHighestPrioriry() //devolve elemento com maior prioridade
    {
        return priority_queue[0].data;
    };

    void insert(int key, T data) //insere elemento no heap se há espaço
    {
        if(heap_size == size)
        {
            std::cerr << "Overflow!\n";
            return;
        }

        heapnode<T> node(key, data);
        priority_queue[heap_size] = node;
        up(heap_size);
        heap_size++;

    };

    void remove() //exclui elemento de maior prioridade
    {
        if(heap_size == 0)
        {
            std::cerr << "Underflow!\n";
            return;
        }

        heap_size--;
        priority_queue[0] = priority_queue[heap_size];
        down(0);
    };

    void decreaseKey(int i, int new_key) //diminui chave de um nó na posiçao i
    {
        priority_queue[i].key = new_key;
        up(i);
    };

    void increaseKey(int i, int new_key) //aumeta chave de um nó na posição i
    {
        priority_queue[i].key = new_key;
        down(i);
    };

    void deleteKey(int i) //exclui um nó na posição i
    {
        decreaseKey(i, INT_MIN);
        remove();
    }

    void printHeap() //imprime o heap
    {
        for(int i = 0; i < heap_size; i++)
        {
            std::cout << "[Index: " << i << "|Key: " << priority_queue[i].key << ", Data: " << priority_queue[i].data << "] ";
        }
    };
};

template <class T>
class HeapMax
{
private:
    heapnode<T> *priority_queue; //array que guardara os elementos do heap
    int size; //tamanho maximo do heap
    int heap_size; //quantidade de elementos no heap

    void exchange(heapnode<T> *a, heapnode<T> *b) //troca nós de posição
    {
        heapnode<T> temp = *a;
        *a = *b;
        *b = temp;
    };

    void up(int i) //sobe nó apos inserção ou que aumentou a chave
    {
        while(i > 0)
        {
            if(priority_queue[i].key > priority_queue[(i - 1) /  2].key)
            {
                exchange(&priority_queue[i], &priority_queue[(i - 1) /  2]);
                i = (i - 1) /  2;
            }
            else
                i = 0;
        }
    };

    void down(int i) //desce nó apos remoção ou que diminuiu a chave
    {
        int j = 2 * i + 1;

        while(j <= heap_size)
        {
            if(j < heap_size)
            {
                if(priority_queue[j + 1].key > priority_queue[j].key)
                    j = j + 1;
            }

            if(priority_queue[i].key < priority_queue[j].key)
            {
                exchange(&priority_queue[i], &priority_queue[j]);
                i = j;
                j = 2 * i + 1;
            }
            else
                j = heap_size + 1;
        }
    };

public:
    HeapMax(int size)
    {
        this->size = size;
        this->priority_queue = new heapnode<T>[this->size];
        this->heap_size = 0;
    };

    ~HeapMax()
    {
        delete [] this->priority_queue;
    };

    T getHighestPrioriry() //devolve elemento com maior prioridade
    {
        return priority_queue[0].data;
    };

    void insert(int key, T data) //insere elemento no heap se há espaço
    {
        if(heap_size == size)
        {
            std::cerr << "Overflow!\n";
            return;
        }

        heapnode<T> node(key, data);
        priority_queue[heap_size] = node;
        up(heap_size);
        heap_size++;
    };

    void remove() //exclui elemento de maior prioridade
    {
        if(heap_size == 0)
        {
            std::cerr << "Underflow!\n";
            return;
        }

        heap_size--;
        priority_queue[0] = priority_queue[heap_size];
        down(0);
    };

    void decreaseKey(int i, int new_key) //diminui chave de um nó na posiçao i
    {
        priority_queue[i].key = new_key;
        down(i);
    };

    void increaseKey(int i, int new_key) //aumeta chave de um nó na posição i
    {
        priority_queue[i].key = new_key;
        up(i);
    };

    void deleteKey(int i) //exclui um nó na posição i
    {
        increaseKey(i, INT_MAX);
        remove();
    };

    void printHeap() //imprime o heap
    {
        for(int i = 0; i < heap_size; i++)
        {
            std::cout << "[Index: " << i << "|Key: " << priority_queue[i].key << ", Data: " << priority_queue[i].data << "] ";
        }
    };
};
