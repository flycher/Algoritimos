/*
O problema da maior subsequência comum é para encontrar a
maior subsequência comum entre as duas sequências X e Y.
*/

#include <bits/stdc++.h>

int** lcs(std::string x, std::string y)
{
    int a = x.length(), b = y.length(); // tamanhos das strings
    int** T = new int*[a + 1];

    for(int i = 0; i <= a; i++)
    {
        T[i] = new int[b + 1];
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
            else T[i][j] = std::max(T[i - 1][j], T[i][j - 1]);
        }
    }

    // o ultimo elemento da matriz armazena o tamanho da maior subsequencia
    return T;
}

std::string maior_subsequencia_comum(std::string x, std::string y)
{
    int **T = lcs(x, y);
    int i = x.length(), j = y.length();
    std::cout << T[i][j] << std::endl; //t tamanhp da maior subsequencia comum
    std::string s(T[i][j], '$'); // string em que a subsequencia sera armazenada

    while(i > 0 && j > 0) // enquanto os indices forem válidos
    {
        if(x[i - 1] == y[j - 1]) // se os caracteres nos indices forem iguais
        {
            s[T[i][j] - 1] = x[i - 1]; // estes fazem parte da subsequencia
            // olhamos os proximos caracteres
            i--;
            j--;
        }
        else // senão, olhamos o carectere dependendo do valor na tabela, diminuindo do que guarda o menor valor
        {
            T[i - 1][j] > T[i][j - 1] ? i-- : j--;
        }
    }

    return s; // retorna a maior subsequencia comum
}

int main()
{
    std::string x, y;
    std::cin >> x >> y;
    std::cout << maior_subsequencia_comum(x, y) << std::endl;
}
