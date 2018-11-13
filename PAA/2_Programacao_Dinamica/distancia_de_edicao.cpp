/*
A distância de edição ou (distância de Levenshtein) entre duas palavras p1 e p2
consiste no número mínimo de operações de adição, remoção ou substituição de letras
em p1 de forma a obtermos a palavra p2 . Por exemplo, a distância entre as palavras
casa e carroça é no máximo 4, pois podemos realizar a seguinte sequência de
operações para obter a segunda a partir da primeira:
        casa → cara → carra → carroa→ carroça
Desenvolva um algoritmo de Programação Dinâmica que calcula, dadas duas palavras,
a distância de Levenshtein entre elas.
*/

#include <bits/stdc++.h>

int min3(int a, int b, int c)
{
    if(a < b && a < c)
        return a;
    else if(b < c)
        return b;
    else
        return c;
}

int dif(char a, char b)
{
    return a == b ? 0 : 1;
}

int distanciaDeEdicao(std::string A, std::string B)
{
    int n = A.length(), m = B.length();
    int T[n + 1][m + 1]; // cria a matriz de memorização

    for(int i = 0; i <= n; i++)
        T[i][0] = i; // a distancia de B para vazio

    for(int j = 0; j <= m; j++)
        T[0][j] = j; // a distancia de A para vazio

    for(int i = 1; i <= n; i++)
    {
        for(int j = 1; j <= m; j++)
        {
            // guardamos o minimo entre os considerar os A[i] e B[j] distantes em 1
            // 'descartando' A[i] ou B[j] e comparando A[i] == A[j] e 'descartando' ambos
            // em dif, se A[i] == B[j], consideramos a distancia entre eles em 0
            T[i][j] = min3(1 + T[i - 1][j], 1 + T[i][j - 1], dif(A[i - 1], B[j - 1]) + T[i - 1][j - 1]);
        }
    }

    return T[n][m]; // retornamos a menor diferenca
}

int main()
{
    std::string A, B;
    std::cin >> A >> B;
    std::cout << distanciaDeEdicao(A, B) << '\n';
}
