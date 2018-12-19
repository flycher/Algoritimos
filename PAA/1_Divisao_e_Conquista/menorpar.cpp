/*
dado um vetor ordenado
V de n elementos distintos, determinar os índices do par de elementos
V [i] e V [j] cuja diferença é a menor dentre todos os elementos do vetor.
*/

#include <bits/stdc++.h>
using namespace std;

typedef pair<int, int> pii;

// Retorna os indices dos pares de menor diferença
pii min3(int V[], pii x, pii y, pii z)
{
    int a = V[x.first] - V[x.second];
    int b = V[y.first] - V[y.second];
    int c = V[z.first] - V[z.second];

    if(a < b && a < c)
        return x;
    else if(b < c)
        return y;
    return z;
}

pii menorPar(int V[], int p, int q)
{
    if(q - p == 1) // retorna o par quando a faixa possui apenas 2 elementos
        return make_pair(q, p);
    int m = (q + p) / 2;
    return min3(V, make_pair(m + 1, m),
                menorPar(V, p, m), menorPar(V, m, q));
}

int main()
{
    int n;
    cin >> n;
    int V[n];
    for(int i = 0; i < n; i++)
        cin >> V[i];
    pii mp = menorPar(V, 0, n - 1);
    cout << '(' << mp.second << ',' << mp.first << ')' << endl;
}
