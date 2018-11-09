/*
Um vetor é unimodal quando este está organizado de forma que do início do vetor
até um dado índice i, que chamamos de pico, os elementos estão dispostos
em ordem crescente e, a partir de i até o fim do vetor, os demais elementos
estejam em ordem decrescente. Dao um vetor unimodal de n elementos,
retorne o índice em que ocorre o pico desse vetor.
*/

#include <bits/stdc++.h>

int buscaPico(int V[], int p, int q)
{
    if(p == q - 1) // Quando existe apenas 2 elementos na faixa, retorna o maior
    {
        if(V[p] > V[q])
            return p;
        return q;
    }
    if(p == q || V[p] > V[p + 1])
        return p;
    int m = (p + q) / 2;
    if(V[m] < V[m - 1]) // O pico esta na esquerda
        return buscaPico(V, p , m - 1);
    else if(V[m] < V[m + 1]) // O pico esta na direita
        return buscaPico(V, m + 1, q);
    return m; // Se V[m] e maior que seus adjacentes, encontramos o pico
}

int main()
{
    int n;
    std::cin >> n;
    int V[n];
    for(int i = 0; i < n; i++)
        std::cin >> V[i];
    std::cout << buscaPico(V, 0, n - 1) <<'\n';
}
