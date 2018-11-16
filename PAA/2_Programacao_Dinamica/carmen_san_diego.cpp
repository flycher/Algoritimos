/*
A ladra mais procurada do mundo, Carmen Sandiego, acabou de encontrar,
na casa de um famoso colecionador de jóias, uma sala repleta de pedras preciosas.
O chão da sala está coberto por ladrilhos quadrados dispostos em h linhas e w colunas,
e em cada ladrilho pode-se encontrar entre 1 e 100 pedras.
Após analisar bem a sala, percebeu que, para não ativar armadilhas e sair de lá
com a maior quantidade de pedras possível, Carmen só poderia pegar as pedras
seguindo as seguintes regras:
• Ela deve escolher apenas um dos ladrilhos em cada linha e pegar todas as pedras nele, começando
pela linha mais acima.
• Ao pegar as pedras de um ladrilho em uma linha, ela deve passar para um ladrilho na linha
imediatamente abaixo, até que chegue na última linha.
• Ao passar para a próxima linha, os únicos ladrilhos que não dispararão alarmes são o na mesma
coluna do anterior ou um dos adjacentes deste (diagonalmente à esquerda ou direita do anterior).
Escreva um algoritmo de Programação Dinâmica que, dados os valores de h, w e as quantidades de jóias
em cada ladrilho no chão da sala, retorna a maior quantidade de pedras que Carmen Sandiego poderá
obter sem disparar armadilhas.
*/

#include <bits/stdc++.h>

int max(int a, int b)
{
    return a > b ? a : b;
}

int ladrilhos(int** & M, int h, int w, int p, int q, int** & T)
{
    if(p >= h || q >= w || p < 0 || q < 0) // passando indices invalidos
        return 0;

    if(T[p][q] != -1) // se o resultado ja foi salvo na memorização
        return T[p][q];

    int a = ladrilhos(M, h, w, p + 1, q - 1, T); // diagonal inferior esquerda
    int b = ladrilhos(M, h, w, p + 1, q, T); // centro
    int c = ladrilhos(M, h, w, p + 1, q + 1, T); // diagonal inferior direita

    // salva na matriz de memorização o maior valor e retorna
    return T[p][q] = M[p][q] + max(a, max(b, c));
}

int ladra(int** & M, int h, int w)
{
    int maior = -1; // maior numero de joias atual
    int **T = new int*[h]; // matriz de memorização
    for(int i = 0; i < h; i++)
    {
        T[i] = new int[w];
        for(int j = 0; j < w; j++)
            T[i][j] = -1;
    }

    // com a função ladrilhos, veremos o melhor caminho que podemos tomar
    // se decidirmos começão por cada coluna, guardando o maior encontrado em maior
    for(int i = 0; i < w; i++)
        maior = max(maior, ladrilhos(M, h, w, 0, i, T));

    return maior;
}

int main()
{
    int h, w;
    std::cin >> h >> w; // linhas e colunas da matriz
    int** M = new int*[h]; //
    for(int i = 0; i < h; i++)
        M[i] = new int[w];

    for(int i = 0; i < h; i++)
        for(int j = 0; j < w; j++)
            std::cin >> M[i][j]; // preenche a matriz

    std::cout << ladra(M, h, w) << '\n';
}
