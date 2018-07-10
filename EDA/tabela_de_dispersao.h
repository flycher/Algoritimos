#include <map>
#include <math.h>

template <class T>
class DirectAdress //tabela de dispersão por endereçamento direto
{
private:
    T *table; //tablela de dispersão
    int *colors;
    int tablesize; //tamanho da tabela

public:
    DirectAdress(int size) //cria a tabela de tamanho n
    {
        tablesize = size;
        table = new T[tablesize];
        colors = new int[tablesize];
    };

    ~DirectAdress() //libera a tabela
    {
        delete [] table;
        delete [] colors;
    };

    T searchDirectAdress(int key) //procura na tabela pela chave
    {
        if(colors[key] == 1)
            return table[key];
        else
            std::cerr << "Key not in use.\n";
        T aux;
        return aux;
    };

    void insertDirectAdress(int key, T data) //insere na tabela pela chave do nó
    {
        if(colors[key] == 0)
        {
            table[key] = data;
            colors[key] = 1;
        }
        else
            std::cerr << "Key already in use.\n";
    };

    void deleteDirectAdress(int key) //remove da tabela pela chave do nó
    {
        if(colors[key] == 1)
        {
            colors[key] = 0;
        }
        else
            std::cerr << "Key not in use.\n";
    };

    void updateKeyDirectAdress(int key, int new_key)
    {
        if(colors[new_key] == 0)
        {
            table[new_key] = table[key];
            colors[key] = 0;
            colors[new_key] = 1;
        }
        else
            std::cerr << "Key already in use.\n";
    }

    void printColors()
    {
        for(int i = 0; i < tablesize; i++)
            std::cout << colors[i] << ' ';
    }
};


template <class T>
class ChainedHash //tabela de disperção por endereçamento indireto
{
private:
    std::map<int, T> *table; //array de listas
    int tablesize; //tamanho da tabela
    int hashfunction(int key) //função de dispersão
    {
        return tablesize * fmod((key * 0.61803), 1.0);
    };

public:
    ChainedHash(int size) //cria a tabela de tamanho n
    {
        tablesize = size;
        table = new std::map<int, T>[tablesize];
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
        T aux;
        try {
            return table[hashfunction(key)].at(key);
        }
        catch (const std::out_of_range& oor) {
            std::cerr << "Key not in the table!\n";
            return aux;
        }
    };

    void insertChainedHash(int key, T data) //insere o nó na lista do array[h(key)]
    {
        table[hashfunction(key)].insert(std::pair<int,T>(key,data));
    };

    void deleteChainedHash(int key) //remove o nó da lista do array[h(key)]
    {
        table[hashfunction(key)].erase(key);
    };

    void updateKeyChainedHash(int key, int new_key)
    {
        try {
            T aux = table[hashfunction(key)].at(key);
            insertChainedHash(new_key, aux);
            deleteChainedHash(key);
        }
        catch (const std::out_of_range& oor) {
            std::cerr << "Key not in the table!\n";
        }
    }
};
