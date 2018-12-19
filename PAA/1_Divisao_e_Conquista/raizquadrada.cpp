/*
Escreva um algoritmo de Divisão e Conquista para determinar
o valor de sqrt(n) em Θ(lg n), dado n ∈ N.
Estamos procurando um número natural k tal que k² ≤ n e (k + 1)² > n.
*/

#include <bits/stdc++.h>
using namespace std;

int raizQuadrada(int n, double p, double q)
{
    double m = (p + q) / 2; // o real no meio da 'faixa'
    int x = m * m; // guarda sua potenciacao num inteiro
    if(x == n)
        return m; // a funçao irá convergir no valor correto
    if(n < x)
        return raizQuadrada(n, p, m - 1);
    return raizQuadrada(n, m + 1, q);
}

int main()
{
    int n;
    cin >> n;
    cout << raizQuadrada(n, 1, n) << endl;
}
