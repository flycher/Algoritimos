/*
Dada uma memoria cache com M posições, um conjunto D = {d1,d2,...,dm} de posições
de memória e uma sequencia L determinando a ordem de leitura das posições D para
realizar uma computação queremos determinar uma estrategia de cache eviction para
garantir o mínimo de cache misses para L.
Jogaremos fora a o posição cujo próximo acesso na computação está o mais no futuro.
(Farthest-in-Future)
*/

#include <bits/stdc++.h>
using namespace std;
#define INF 99999

typedef vector<int> vi;

bool in_cache(int instrucao, vi & cache)
{
    for(int i = 0; i < cache.size(); i++)
    {
        if(cache[i] == instrucao)
            return true;
    }
    return false;
}

void evict(int farthest, int instrucao, vi & cache)
{
    for(int i = 0; i < cache.size(); i++)
    {
        if(cache[i] == farthest)
            cache[i] = instrucao;
            break;
    }
}

int fathest_in_future(int L[], int n, int C)
{
    vi cache;
    int evictions = 0;

    for(int i = 0; i < n; i++)
    {
        if((cache.size() < C) && (!in_cache(L[i], cache)))
            cache.push_back(L[i]);

        if(!in_cache(L[i], cache))
        {
            evictions++;
            int farthest;
            int future = -1;
            for(auto instrucao: cache)
            {
                int ocorrencia = INF;
                for(int k = i + 1; k < n; k++)
                {
                    if(L[k] == instrucao)
                    {
                        ocorrencia = k;
                        break;
                    }
                }
                if(ocorrencia > future)
                {
                    future = ocorrencia;
                    farthest = instrucao;
                }
            }
            evict(farthest, L[i], cache);
        }
    }
    return evictions;
}

int main()
{
    int n, C;
    cin >> n >> C;
    int L[n];
    for(int i = 0; i < n; i++)
        cin >> L[i];
    cout << fathest_in_future(L, n, C) << endl;
}
