/*
Imagine que serializamos uma árvore binária de busca T em um vetor V
através de um percurso em pré-ordem. Ou seja, o vetor V contém os elementos
de T na ordem em que os obtivemos nesse percurso. Escreva um algoritmo de
Divisão e Conquista que, dado esse vetor V e um elemento x, determina se x ∈ T .
*/

#include <bits/stdc++.h>

int filhoDireito(int V[], int r, int p, int q)
{
    int m;
    while(p < q)
    {
        m = (p + q) / 2;
        if(V[m] > r)
            q = m;
        else
            p = m + 1;
    }
    if(V[q] > r)
        return q;
    return -1;
}

bool buscaPreOrdem(int V[], int p, int q, int x)
{
    if(p <= q)
    {
        int r = V[p];
        if(r == x)
            return true;
        int e = p + 1;
        int d = filhoDireito(V, r, p + 1, q);
        if(r < x)
        {
            if(d != -1)
                return buscaPreOrdem(V, d, q, x);
            return false;
        }
        if(d == -1)
            d = q;
        return buscaPreOrdem(V, e, d, x);
    }
    return false;
}

int main()
{
    int n;
    std::cin >> n;
    int V[n];
    for(int i = 0; i < n; i++)
        std::cin >> V[i];
    int x;
    std::cin >> x;
    if(buscaPreOrdem(V, 0, n - 1, x))
        std::cout << 'V' << '\n';
    else
        std::cout << 'F' << '\n';
}