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
using namespace std;

typedef struct
{
    int adicoes, remocoes;
} mudancas;

mudancas diff(string A, string B)
{
    // percorreremos as strings e matriz do final para o começo
    int n = A.size(), m = B.size();
    mudancas T[n + 1][m + 1];

    // preenchemos a coluna m com as alterações para transformar A em vazio
    for(int i = n; i >= 0 ; i--)
    {
        mudancas def;
        def.adicoes = 0;
        def.remocoes = n - i;
        T[i][m] = def;
    }

    // preenchemos a linha n com as alterações para transformar vazio em A
    for(int j = m; j >= 0; j--)
    {
        mudancas def;
        def.adicoes = m - j;
        def.remocoes = 0;
        T[n][j] = def;
    }

    for(int i = n - 1; i >= 0; i--)
    {
        for(int j = m - 1; j >= 0; j--)
        {
            if(A[i] == B[j]) // mantemos o caractere caso forem iguais
                T[i][j] = T[i + 1][j + 1];
            else
            {
                mudancas remover = T[i + 1][j]; // removemos o caractere de A
                remover.remocoes++;
                mudancas adicionar = T[i][j + 1]; // adicionamos o caractere a A
                adicionar.adicoes++;
                int rem = remover.remocoes + remover.adicoes;
                int add = adicionar.remocoes + adicionar.adicoes;
                T[i][j] = rem < add ? remover : adicionar; // adicionamos a matriz o que gera o menor resultado
            }
        }
    }

    return T[0][0]; // retornamos a diferença
}

int main()
{
    int i, j;
    cin >> i >> j;
    string A, B, C;
    getline(cin, C);
    //substituiremos as quebras de linha por um caractere, transformando o texto em uma string
    getline(cin, A);
    i--;
    while(i)
    {
        i--;
        getline(cin, C);
        A += '$';
        A += C;
    }

    getline(cin, B);
    j--;
    while(j)
    {
        j--;
        getline(cin, C);
        B += '$';
        B += C;
    }

    mudancas resp = diff(A, B);
    cout << resp.adicoes << ' ' << resp.remocoes << endl;
}
