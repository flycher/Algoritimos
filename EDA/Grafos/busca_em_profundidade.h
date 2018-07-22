#include "lista_de_adjacencia.h"
#include <list>

enum color { WHITE, GRAY, BLACK }; //cores representando vértices alcançado e percorrido

int *discovered; //array guardando quando o vértices foi descoberto
int *finished; //array guardando quando o vértices foi percorrido
int *parents; //array guardando os pais dos vértices na árvore gerada
color *colors; //array guardando as cores dos vértices na busca
int times = 0; //marca em que momento o vértices foi descoberto

void DFSvisit(ListaDeAdjacencia& G, int u)
{
    times++; //aumenta o tempo
    discovered[u] = times; //adiciona o tempo de descoberta do vértice
    colors[u] = GRAY; //muda a cor do vértice para cinza

    int v;
    for(auto it : G.getAdjacent(u)) //para cada vértices na lista de u
    {
        v = it.first; //olha o vértices v
        if(colors[v] == WHITE) //se ele ainda não foi alcançado
        {
            parents[v] = u; //põe u como seu pai
            DFSvisit(G, v); //percorre o vértice
        }
    }
    
    colors[u] = BLACK; //muda a cor do vértice para preto
    times++; //aumenta o tempo
    finished[u] = times; //adiciona o tempo de percorrimento do vértice
};

std::pair<int*, int*> DFS(ListaDeAdjacencia& G)
{
    int V = G.getVertices(); //numero de vértices no grafo
    discovered = new int[V];
    finished = new int[V];
    parents = new int[V];
    colors = new color[V];

    //inicializa todos os vértices pai inexistente e cor branca
    for(int i = 0; i < V; i++)
    {
        parents[i] = -1;
        colors[i] = WHITE;
    }

    for(int u = 0; u < V; u++)
    {
        if(colors[u] == WHITE) //caso o vértice não foi descoberto
            DFSvisit(G, u); //percorre o vértice
    }

    delete [] colors;
    delete [] parents;
    return std::make_pair(discovered, finished); //retorna os arrays de tempo de descoberta e percorrimento
};
