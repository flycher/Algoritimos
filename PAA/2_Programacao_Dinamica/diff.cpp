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

typedef struct
{
    int adicoes, remocoes;
} mudancas;

mudancas diff(int i, int j, int n, int m, std::string A, std::string B, mudancas** & T)
{
    if(i > n)
    {
        mudancas resp;
        resp.remocoes = 0;
        resp.adicoes = std::max(m - j + 1, 0);
        return resp;
    }
    if(j > m)
    {
        mudancas resp;
        resp.adicoes = 0;
        resp.remocoes = std::max(n - i + 1, 0);
        return resp;
    }
    if(T[i][j].adicoes != -1)
        return T[i][j];

    if(A[i] == B[j])
        return T[i][j] = diff(i + 1, j + 1, n, m, A, B,  T);

    mudancas remover = diff(i + 1, j, n, m, A, B, T);
    remover.remocoes++;
    mudancas adicionar = diff(i, j + 1, n, m, A, B, T);
    adicionar.adicoes++;

    if(remover.remocoes + remover.adicoes < adicionar.remocoes + adicionar.adicoes)
        return T[i][j] = remover;
    else
        return T[i][j] = adicionar;

}

int main()
{
    int i, j;
    std::cin >> i >> j;
    std::string A, B, C;

    std::getline(std::cin, C);
    std::getline(std::cin, A);
    i--;
    while(i)
    {
        i--;
        std::getline(std::cin, C);
        A += '$';
        A += C;
    }

    std::getline(std::cin, B);
    j--;
    while(j)
    {
        j--;
        std::getline(std::cin, C);
        B += '$';
        B += C;
    }

    int n = A.size(), m = B.size();

    mudancas** T = new mudancas*[n];
    for(int i = 0; i < n; i++)
    {
        T[i] = new mudancas[m];
        for(int j = 0; j < m; j++)
            T[i][j].adicoes = -1;
    }

    mudancas resp = diff(0, 0, n - 1, m - 1, A, B, T);
    std::cout << resp.adicoes << ' ' << resp.remocoes << std::endl;
}
