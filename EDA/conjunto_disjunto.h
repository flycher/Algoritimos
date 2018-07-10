#include <iostream>

class UnionFind
{
private:
    //guarda o pai de cada conjunto, o peso de casa elemento e a quantidade de dependentes
    int *pai, *peso, *qtd;

public:
    UnionFind(int max); //cria os arays de pai, peso e quantidade
    ~UnionFind(); //exclui os arrays
    int find(int x); //retorna pai do conjunto de x
    void join(int x, int y); //une os elementos a serem unidos
};

UnionFind::UnionFind(int max)
{
    pai = new int[max];
    peso = new int[max];
    qtd = new int[max];
}

UnionFind::~UnionFind()
{
    delete [] pai;
    delete [] peso;
    delete [] qtd;
}

int UnionFind::find(int x)
{

    if(pai[x] == x){
        return x;
    }
    return pai[x] = find(pai[x]); //compreensão de caminho
}

void UnionFind::join(int x, int y)
{
    //atribui a x e y seus pais
    x = find(x);
    y = find(y);

    if(x == y ){
        std::cout << "X and Y already the same set.\n";
    }
    else
    {
        if(peso[x] < peso[y]) //se x tem peso menor que y
        {
            pai[x] = y; //x passa a ser filho do y
            qtd[y] += qtd[x]; //atualiza o numero de descendentes de y
        }
        else if(peso[x] > peso[y]) //se x tem peso maior que y
        {
            pai[y] = x; //y passa a ser filho do x
            qtd[x] += qtd[y];
        }
        else //x e y tem o mesmo peso
        {
            pai[y] = x; //o da direita e escolhido como pai
            peso[x]++; //aumenta o peso de x
            qtd[x] += qtd[y]; //atualiza o numero de descendentes de x
        }
    }
}
