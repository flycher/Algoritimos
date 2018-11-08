/*
O problema da maior subsequência comum é para encontrar a
maior subsequência comum entre as duas sequências X e Y.
*/

#include <bits/stdc++.h>

int lcs(std::string x, std::string y)
{
    int a = x.length(), b = y.length(); // tamanhos das strings
    int T[a + 1][b + 1]; // matriz representando as strings

    for(int i = 0; i <= a; i++)
    {
        for(int j = 0; j <= b; j++)
        {
            T[i][j] = 0; // preenche a matriz com zeros
        }
    }

    // não percorremos a linha e coluna 0
    // preenchemos a matriz inteira da esquerda para direita, de cima para baixo
    for(int i = 1; i <= a; i++)
    {
        for(int j = 1; j <= b; j++)
        {
            // caso os caracteres sejam iguais, adicionamos o valor da diagonal superior esquerda + 1
            if(x[i - 1] == y[j - 1]) T[i][j] = T[i - 1][j - 1] + 1;
            // caso contrario, adicionamos o valor maior entre acima e a esquerda
            else T[i][j] = T[i - 1][j] > T[i][j - 1] ? T[i - 1][j] : T[i][j - 1];
        }
    }

    // o ultimo elemento da matriz armazena o tamanho da maior subsequencia
    return T[a][b];
}

int main()
{
    std::string x, y;
    std::cin >> x >> y;
    std::cout << lcs(x, y) << '\n';
}
