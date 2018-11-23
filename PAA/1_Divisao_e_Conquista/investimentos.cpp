/*
Imagine que você trabalha para uma empresa de investimentos, que lhe pede
consultoria para analisar a evolução da cotação de uma das ações com
as quais a empresa trabalha. Ela lhe informará uma sequência de valores
representando as cotações da ação a cada dia e deseja saber, dados aqueles
valores,em qual dia eles deveriam ter comprado papéis da ação e em qual dia
deveriam ter vendido esses papéis de forma a acumular o maior lucro possível.
Supondo que essa informação lhe seja passada em um vetor, escreva um algoritmo
de Divisão e Conquista que determina os índices correspondentes às
melhores datas de compra e venda.
*/

#include <bits/stdc++.h>

typedef std::pair<int, int> pii;

// Retorna o indice do menor elemento na faixa
int minimo(int V[], int p, int q)
{
    int m = q;
    for(int i = p; i < q; i++)
        V[i] < V[m] ? m = i : m;
    return m;
}

// Retorna o indice do maior elemento na faixa
int maximo(int V[], int p, int q)
{
    int m = q;
    for(int i = p; i < q; i++)
        V[i] > V[m] ? m = i : m;
    return m;
}

// Retorna os indices dos pares de maior diferença
pii max3(int V[], pii a, pii b, pii c)
{
    int x = V[a.second] - V[a.first];
    int y = V[b.second] - V[b.first];
    int z = V[c.second] - V[c.first];

    if(x > y && x > z)
        return a;
    else if(y > z)
        return b;
    else
        return c;
}

pii investimentos(int V[], int p, int q)
{
    if(q <= p)
        return std::make_pair(0, 0);
    int m = (p + q) / 2;
    int a = minimo(V, p, m); // menor elemento da esquera
    int b = maximo(V, m + 1, q); // maior elemento da direita
    // retorna a maior diferenca entre o par encontrado e as faixas
    return max3(V, std::make_pair(a, b), investimentos(V, p, m), investimentos(V, m + 1, q));
}

int main()
{
    int n;
    std::cin >> n;
    int V[n];
    for(int i = 0; i < n; i++)
        std::cin >> V[i];
    pii inv = investimentos(V, 0, n - 1);
    std::cout << inv.first << ',' << inv.second << std::endl;
}
