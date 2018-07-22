#include <list>

class ListaDeAdjacencia
{
private:
    int V; //quatidade de vertices
    int E; //quatidade de arestas
    bool directed; //se o grafo e direcionado
    bool weighted; //se as arestas possuem peso
    std::list<std::pair<int, int> > *G; //representação do grafo

public:
    ListaDeAdjacencia(int V, int E, bool directed, bool weighted);
    ~ListaDeAdjacencia();
    int getVertices() { return V; };
    int getEdges() { return E; };
    std::list<std::pair<int, int> > getAdjacent(int u) { return G[u]; }; //retorna os adjacentes do vertice
    void addEdge(int u, int v, int weight); //adiciona uma aresta
    void removeEdge(int u, int v); //remove uma aresta
    bool checkEdge(int u, int v); //verifica se a aresta existe
};

ListaDeAdjacencia::ListaDeAdjacencia(int V, int E, bool directed, bool weighted)
{
    this->V = V;
    this->E = 0;
    this->directed = directed;
    this->weighted = weighted;
    G = new std::list<std::pair<int, int> >[V];
}

ListaDeAdjacencia::~ListaDeAdjacencia()
{
    for(int i = 0; i < V; i++)
        G[i].clear();
    delete [] G;
}

void ListaDeAdjacencia::addEdge(int u, int v, int weight = 1)
{
    G[u].push_back(std::make_pair(v, weight));
    if(!directed)
        G[v].push_back(std::make_pair(u, weight));

    E++;
};

void ListaDeAdjacencia::removeEdge(int u, int v)
{
    std::list<std::pair<int, int> >::iterator it = G[u].begin();

    while(it != G[u].end())
    {
        if(it->first == v)
        {
            G[u].erase(it);
            break;
        }
        it++;
    }

    if(!directed)
    {
        it = G[v].begin();

        while(it != G[v].end())
        {
            if(it->first == u)
            {
                G[v].erase(it);
                break;
            }
            it++;
        }
    }

    E--;
};

bool ListaDeAdjacencia::checkEdge(int u, int v)
{
    std::list<std::pair<int, int> >::iterator it = G[u].begin();

    while(it != G[u].end())
    {
        if(it->first == v)
        {
            return true;
        }
        it++;
    }

    return false;
};
