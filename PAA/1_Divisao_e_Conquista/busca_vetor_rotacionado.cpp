/*
Considere um vetor V construído com o seguinte processo: iniciamos com
n elementos distintos, os ordenamos em ordem crescente e então tomamos os
k primeiros elementos e os deslocamos para o fim do vetor.
Por exemplo, poderíamos iniciar com o vetor ordenado [3, 6, 8, 17, 20] e,
escolhendo k = 3, obteríamos V = [17, 20, 3, 6, 8].
Escreva um algoritmo de complexidade Θ(lg n) que recebe um vetor obtido
através desse processo, porém sem saber que k foi escolhido,
e encontra o índice em V em que se encontra um valor x buscado.
*/

#include <bits/stdc++.h>
using namespace std;

int buscaBinaria(int V[], int p, int q, int x)
{
    int m;
    while(p <= q)
    {
        m = (p + q) / 2;
        if(V[m] > x)
            q = m - 1;
        else if(V[m] < x)
            p = m + 1;
        else
            return m;
    }
    return -1;
}

// Encontra o indice em que o vetor foi deslocado
int achaK(int V[], int p, int q)
{
    if((V[q] >= V[p]) || p == q)
        return p;
    int m = (p + q) / 2;
    if(m > 0 && V[m - 1] > V[m])
        return m;
    if(V[m] >= V[0])
        return achaK(V, m + 1, q);
    return achaK(V, p, m - 1);
}

int buscaRot(int V[], int n, int x)
{
    int k = achaK(V, 0, n);
    int l = buscaBinaria(V, 0, k - 1, x); // vetor ordenado esquerdo
    int r = buscaBinaria(V, k, n - 1, x); // vetor ordenado direito
    return (l + r) + 1;
}

int main()
{
    int n;
    cin >> n;
    int V[n];
    for(int i = 0; i < n; i++)
        cin >> V[i];
    int x;
    cin >> x;
    cout << buscaRot(V, n - 1, x) << endl;
}
