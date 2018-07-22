#include <climits>

class MatrizDeAdjacencia
{
private:
    int V; //quatidade de vértices
    int E; //quatidade de arestas
    bool directed; //se o grafo e direcionado
    bool weighted; //se as arestas possuem peso
    int **G; //representação do grafo

public:
    MatrizDeAdjacencia(int V, int E, bool directed, bool weighted);
    ~MatrizDeAdjacencia();
    int getVertices() { return V; };
    int getEdges() { return E; };
    int* getAdjacent(int u) { return G[u]; }; //retorna os adjacentes do vertice
    void addEdge(int u, int v, int weight); //adiciona uma aresta
    void removeEdge(int u, int v); //remove uma aresta
    bool checkEdge(int u, int v); //verifica se a aresta existe
};

MatrizDeAdjacencia::MatrizDeAdjacencia(int V, int E, bool directed, bool weighted)
{
    this->V = V;
    this->E = 0;
    this->directed = directed; //se não for direcinado, cria matriz triangular
    this->weighted = weighted; //se possui peso, não presença da aresta é representada por infinito(INT_MAX)

    G = new int*[V];
    for(int i = 0; i < V; i++)
    {
        if(!directed)
        {
            G[i] = new int[i + 1];
            if(weighted)
            {
                for(int j = 0; j < i + 1; j++)
                    G[i][j] = INT_MAX;
            }
        }
        else
        {
            G[i] = new int[V];
            if(weighted)
            {
                for(int j = 0; j < V; j++)
                    G[i][j] = INT_MAX;
            }
        }
    }
};

MatrizDeAdjacencia::~MatrizDeAdjacencia()
{
    for(int i = 0; i < V; i++)
        delete [] G[i];
    delete [] G;
};

void MatrizDeAdjacencia::addEdge(int u, int v, int weight = 1)
{
    if(directed)
        G[u][v] = weight;
    else
    {
        if(v > u)
            G[v][u] = weight;
        else
            G[u][v] = weight;
    }

    E++;
};

void MatrizDeAdjacencia::removeEdge(int u, int v)
{
    if(directed)
    {
        if(weighted)
            G[u][v] = INT_MAX;
        else
            G[u][v] = 0;
    }
    else
    {
        if(weighted)
        {
            if(v > u)
                G[v][u] = INT_MAX;
            else
                G[u][v] = INT_MAX;
        }
        else
        {
            if(v > u)
                G[v][u] = 0;
            else
                G[u][v] = 0;
        }
    }

    E--;
};

bool MatrizDeAdjacencia::checkEdge(int u, int v)
{
    if(weighted)
    {
        if(directed)
        {
            return G[u][v] != INT_MAX;
        }
        else
        {
            if(v > u)
                return G[v][u] != INT_MAX;
            else
                return G[u][v] != INT_MAX;
        }
    }
    else
    {
        if(directed)
        {
            return G[u][v];
        }
        else
        {
            if(v > u)
                return G[v][u];
            else
                return G[u][v];
        }
    }
};
