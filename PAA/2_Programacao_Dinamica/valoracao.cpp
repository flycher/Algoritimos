/*
Dada uma expressão aritmética não-parentizada, onde ocorrem as operações de adição e multiplica-
ção, escreva um algoritmo de Programação Dinâmica para determinar qual é o maior valor que essa
expressão pode assumir se decidirmos parentizá-la, dentre todas as parentizações possíveis. Imagine
que a expressão será dada em uma lista onde o primeiro índice é um operando numérico e, a partir
do segundo, temos alternadamente uma operação e outro operando numérico (em outras palavras, nos
índices ímpares há operandos e nos pares há operações).
Por exemplo: Se a expressão for E = [1 + 2 ∗ 3 + 4 ∗ 5], uma das possíveis parentizações
dessa expressão seria (1 + 2) ∗ (3 + (4 ∗ 5)), resultando em 69, porém a que gera o maior dos resultados
seria ((1 + 2) ∗ (3 + 4)) ∗ 5, resultando em 105.
*/

#include <bits/stdc++.h>

int parentisa(std::string E, int i, int j, int** & T)
{
    if(i == j)
        return E[i] - '0'; // transforma o indice em inteiro e retorna
    if(T[i][j] != -1)
        return T[i][j]; // se ja foi calculado

    int maior = -INT_MAX; // guardará o maior valor possivel dentre as parentizações

    for(int k = i + 1; k < j; k+=2) // o k marca apenas as operações
    {
        if(E[k] == '+')
            maior = std::max(maior, parentisa(E, i, k - 1, T) + parentisa(E, k + 1, j, T));
        if(E[k] == '*')
            maior = std::max(maior, parentisa(E, i, k - 1, T) * parentisa(E, k + 1, j, T));
    }

    return T[i][j] = maior;
}

int main()
{
    std::string E;
    std::cin >> E;
    int n = E.length();

    int** T = new int*[n];
    for(int i = 0; i < n; i++)
    {
        T[i] = new int[n];
        for(int j = 0; j < n; j++)
            T[i][j] = -1;
    }

    std::cout << parentisa(E, 0, n - 1, T) << '\n';
}
