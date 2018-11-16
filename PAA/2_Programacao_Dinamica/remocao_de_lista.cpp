/*
Seja L uma lista de n números inteiros. A cada momento você pode escolher dois números adjacentes
na lista, eliminá-los e pôr em seu lugar o resultado da subtração do primeiro pelo segundo número
escolhido, na ordem em que estavam na lista. Depois de realizar essa operação n − 1 vezes, na lista
restará um único número m. Escreva um algoritmo de Programação Dinâmica que determina qual é o
maior valor possível para m ao final dessas operações dados os números na lista inicial.
Por exemplo: a sequência de operações a seguir gera o menor dos resultados para a lista L = [2 3 1 4],
com os números escolhidos a cada passo destacados.
[2, (3, 1), 4] → [2, (2, 4)] → [(2, -2)] → [4].
*/

#include <bits/stdc++.h>

int max(int a, int b)
{
    return a > b ? a : b;
}

int remove_lista(int E[], int n, int i, int j, int** & T)
{
    if(i > n || j > n) // passando indices invalidos
        return 0;
    if(i == j) // se temos apenas 1 elemento na faixa
        return E[i];
    if(T[i][j] != -1) // se ja calculamos os indices i, j
        return T[i][j];

    int maximo = -INT_MAX;
    for(int k = i; k < j; k++)
        // guardaremos o maior para cada possivel sequencia de subtração
        maximo = max(maximo, remove_lista(E, n, k + 1, j, T) - remove_lista(E, n, i, k, T));

    return T[i][j] = maximo; // retornamos a maior encontrada
}

int main()
{
    int n;
    std::cin >> n;
    int v[n];
    for(int i = 0; i < n; i++)
        std::cin >> v[i];

    int** T = new int*[n];
    for(int i = 0; i < n; i++)
    {
        T[i] = new int[n];
        for(int j = 0; j < n; j++)
            T[i][j] = -1;
    }

    std::cout << remove_lista(v, n - 1, 0, n - 1, T) << '\n';
}
