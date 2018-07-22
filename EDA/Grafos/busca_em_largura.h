#include "lista_de_adjacencia.h"
#include <climits>
#include <queue>
#include <list>

enum color { WHITE, GRAY, BLACK }; //cores representando vertice alcançado e percorrido

std::pair<int*, int*> BFS(ListaDeAdjacencia G, int s)
{
    int V = G.getVertices(); //numero de vertices no grafo
    int *distances = new int[V]; //array guardando a distância dos vertices para s
    int *parents = new int[V]; //array guardando os pais dos vertices na arvore gerada
    color colors[V]; //array guardando as cores dos vertices na busca

    //inicializa todos os vertices com distância infinita, pai inexistente e cor branca
    for(int i = 0; i < V; i++)
    {
        distances[i] = INT_MAX;
        parents[i] = -1;
        colors[i] = WHITE;
    }

    //define distância, pai e cor do vertice s
    distances[s] = 0;
    parents[s] = -1;
    colors[s] = GRAY;

    std::queue<int> Q; //cria fila de alcançados
    Q.push(s); //adiciona o vertice s  a fica

    int u, v; //vertices percorrido e alcançado

    while(!Q.empty()) //enquanto a fila não estiver vazia
    {
        u = Q.front(); //percorre o primeiro vertice da fila
        Q.pop();

        for(auto it : G.getAdjacent(u)) //para cada vertice na lista de u
        {
            v = it.first; //olha o vertice v
            if(colors[v] == WHITE) //se ele ainda não foi alcançado
            {
                colors[v] = GRAY; //marca como alcançado
                distances[v] = distances[u] + 1; //adiciona sua distância
                parents[v] = u; //põe u como seu pai
                Q.push(v); //adiciona v a fila
            }
        }

        colors[u] = BLACK; //marca u como percorrido
    }


    return std::make_pair(distances, parents); //retorna os arrays de distâncias e pais
}
