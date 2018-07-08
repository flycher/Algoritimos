#include <list>
#include <math.h>

template <class T>
class DirectAdress //tabela de dispersão por endereçamento direto
{
private:
    T *table; //tablela de dispersão
    int tablesize; //tamanho da tabela

public:
    DirectAdress(int size) //cria a tabela de tamanho n
    {
        tablesize = size;
        table = new T[tablesize];
    };

    ~DirectAdress() //libera a tabela
    {
        delete [] table;
    };

    T searchDirectAdress(int k) //procura na tabela pela chave
    {
        return table[k];
    };

    void insertDirectAdress(T node) //insere na tabela pela chave do nó
    {
        table[node.key] = node;
    };

    void deleteDirectAdress(T node) //remove da tabela pela chave do nó
    {
        table[node.key] = nullptr;
    };
};


template <class T>
class ChainedHash //tabela de disperção por endereçamento indireto
{
private:
    std::list<T> *table; //array de listas
    int tablesize; //tamanho da tabela
    int hashfunction(int key) //função de dispersão
    {
        return tablesize * fmod((key * 0.61803), 1.0);
    };

public:
    ChainedHash(int size) //cria a tabela de tamanho n
    {
        tablesize = size;
        table = new std::list<T>[tablesize];
    };

    ~ChainedHash() //libera as listas e a tabela
    {
        for(int i = 0; i < tablesize; i++)
        {
            if(!table[i].empty())
                table[i].clear();
        }

        delete [] table;
    };

    T searchChainedHash(int key) //procura na lista do array[h(key)] pelo no com chave key
    {
        std::list<T> temp = table[hashfunction(key)];

        for(auto it : temp)
        {
            if(it.key == key)
                return it;
        }
    };

    void insertChainedHash(T node) //insere o nó na lista do array[h(key)]
    {
        table[hashfunction(node.key)].push_front(node);
    };

    void deleteChainedHash(T node) //remove o nó da lista do array[h(key)]
    {
        table[hashfunction(node.key)].remove(node);
    };
};
