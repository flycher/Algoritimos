/*
Ao compararmos duas versões de um arquivo de texto, podemos imaginar que somos
capazes gerar a segunda versão a partir da primeira através de uma sequência de
operações sobre seus caracteres. Imagine que essas operações sejam aplicadas
tendo a versão original como entrada, sendo a saída um outro arquivo, com o
objetivo de que esse outro arquivo seja fielmente a segunda versão.
As operações são:
    MANTER: Consumimos um caractere da entrada e o escrevemos na saída.
    INSERIR: Não consumimos nada da entrada, porém escrevemos um novo caractere na saída.
    REMOVER: Consumimos um caractere da entrada, sem escrevermos nada na saída.
Vamos então tentar determinar, dadas duas versões de um texto, quais foram
as alterações realizadas em função dessas operações.
*/

#include <bits/stdc++.h>

int dif(char a, char b)
{
    return a == b ? 0 : 1;
}

void distanciaDeEdicao(std::string A, std::string B)
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
            T[i][j] = std::min(std::min(1 + T[i - 1][j], 1 + T[i][j - 1]), dif(A[i - 1], B[j - 1]) + T[i - 1][j - 1]);
        }
    }

    int distancia = T[n][m]; // distancia de edição
    int adicoes = 0, remocoes = 0; // numero de adicoes e remocoes
    int i = n, j = m; // marca o indice na tabela de memorização
    while(distancia) // enquanto existe diferenca entre as palavras
    {
        if(A[i - 1] == B[j - 1]) // caracteres iguais, diferenca e a mesma, olhamos os anteriores
        {
            i--;
            j--;
        }
        else if(T[i - 1][j] > T[i][j - 1]) // a distacia e maior se tirarmos o caractere de A
        {
            distancia--; // diminuimos a distancia
            remocoes++; // "removemos" esse caractere de A
            j--; // olhamos o caractere anterior de B
        }
        else // a distancia não e maior se tirarmos o caractere de A
        {
            distancia--; // diminuimos a distancia
            adicoes++; // "adicionamos" esse caractere de A
            i--; // olhamos o caractere anterior de A
        }
    }

    std::cout << "Distância: " << T[n][m] << " | Remoções: " << remocoes << " | Adições: " << adicoes << '\n';
}

int main()
{
    int i, j;
    std::cin >> i >> j;
    std::string A, B, C;

    std::getline(std::cin, C); // bugs to stdin

    std::getline(std::cin, A);
    i--;
    while(i)
    {
        i--;
        std::getline(std::cin, C);
        A += ' ';
        A += C;
    }
    std::getline(std::cin, B);
    j--;
    while(j)
    {
        j--;
        std::getline(std::cin, C);
        B += ' ';
        B += C;
    }
    distanciaDeEdicao(A, B);
}
