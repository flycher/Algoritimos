/*
Dados um vetor ordenado V com n elementos distintos e dois valores a e b
com a <= b, desejamos obter o par de índices de V que define um intervalo
de elementos tais que seus valores recaem na faixa de valores [a, b].
Seu algoritmo deve ter complexidade Θ(lg n)
*/

#include <bits/stdc++.h>

// Retorna o indice de x ou de seu antecessor em V
int lower(int V[], int p, int q, int x)
{
    int ant = -1;
    int m;
    while(p <= q)
    {
        m = (p + q) / 2;
        if(V[m] < x)
        {
            ant = m;
            p = m + 1;
        }
        else if(V[m] > x)
            q = m - 1;
        else
            return m;
    }
    return ant;
}

// Retorna o indice de x ou de seu antecessor em V
int upper(int V[], int p, int q, int x)
{
    int suc = -1;
    int m;
    while(p <= q)
    {
        m = (p + q) / 2;
        if(V[m] < x)
            p = m + 1;
        else if(V[m] > x)
        {
            suc = m;
            q = m - 1;
        }
        else
            return m;
    }
    return suc;
}

std::pair<int, int> buscaIntervalo(int V[], int n, int a, int b)
{
    return std::make_pair(upper(V, 0, n, a), lower(V, 0, n, b));
}

int main()
{
    int n;
    std::cin >> n;
    int V[n];
    for(int i = 0; i < n; i++)
        std::cin >> V[i];
    int a, b;
    std::cin >> a >> b;
    std::pair<int, int> interv = buscaIntervalo(V, n - 1, a, b);
    std::cout << '[' << interv.first << ',' << interv.second << ']' << '\n';
}
