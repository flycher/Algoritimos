/*
dado um vetor ordenado
V de n elementos distintos, determinar os índices do par de elementos
V [i] e V [j] cuja diferença é a menor dentre todos os elementos do vetor.
*/

#include <bits/stdc++.h>

typedef std::pair<int, int> pii;

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
    if(q - p == 1)
        return std::make_pair(q, p);
    int m = (q + p) / 2;
    return min3(V, std::make_pair(m + 1, m),
                menorPar(V, p, m), menorPar(V, m, q));
}

int main()
{
    int n;
    std::cin >> n;
    int V[n];
    for(int i = 0; i < n; i++)
        std::cin >> V[i];
    pii mp = menorPar(V, 0, n - 1);
    std::cout << '(' << mp.second << ',' << mp.first << ')' << '\n';
}
