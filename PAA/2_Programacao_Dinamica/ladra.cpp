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
using namespace std;

int ladra(int** & M, int h, int w)
{
    int T[h][w];

    // preencheremos a matriz de baixo para cima
    for(int j = 0; j < w; j++)
        T[h - 1][j] = M[h - 1][j]; // a ultima linha tem os mesmos valores da matriz de joias

    for(int i = h - 2; i >= 0; i--)
    {
        for(int j = 0; j < w; j++)
        {
            // para cada um, olhamos o maior entre os de baixo possiveis e somamos ao atual
            int a = j - 1 >= 0 ? T[i + 1][j - 1] : -1;
            int b = T[i + 1][j];
            int c = j + 1 < w ? T[i + 1][j + 1] : -1;
            T[i][j] = M[i][j] + max(a, max(b, c));
        }
    }

    // no fim, percorremos a primeira linha e salvamos o maior valor possivel
    int maior = -1;
    for(int i = 0; i < w; i++)
        maior = max(maior, T[0][i]);

    return maior;
}


int main()
{
    int h, w;
    cin >> h >> w; // linhas e colunas da matriz
    int** M = new int*[h]; //
    for(int i = 0; i < h; i++)
        M[i] = new int[w];

    for(int i = 0; i < h; i++)
        for(int j = 0; j < w; j++)
            cin >> M[i][j]; // preenche a matriz

    cout << ladra(M, h, w) << endl;
}
