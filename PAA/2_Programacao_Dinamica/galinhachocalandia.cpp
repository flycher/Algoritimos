/*
O vilarejo de Galinhachocalândia não é um lugar muito amigável. Nessa vila,
todo habitante detesta seus vizinhos de porta de ambos os lados.
Infelizmente, a praça do vilarejo está muito deteriorada e precisando de reparos,
por isso você foi contratado para coletar doações dos habitantes para a
campanha de restauração. Cada habitante i pode contribuir com D[i] reais.
Entretanto, ninguém irá contribuir para uma campanha em que um
de seus vizinhos tenha contribuído. Você, como um bom estudante das artes de
Projeto de Algoritmos, decidiu construir um algoritmo de Programação Dinâmica
que lhe permita decidir a que habitantes pedir doações de forma a obter o máximo
 de dinheiro possível. Imagine que seu algoritmo irá receber um vetor D com
 n posições, onde cada posição i representa a quantia que o habitante i irá
 contribuir se satisfeitas suas condições. Considere que o vetor está
disposto de forma que os vizinhos de i são exatamente i − 1 e i + 1,
à exceção do primeiro e do último, que têm apenas um vizinho.
*/

#include <bits/stdc++.h>

int max(int a, int b)
{
    return a > b ? a : b;
}

std::vector<int> vizinhos(int v[], int n)
{
    // a matriz de memorização guardará apenas 2 valores para cada elemento
    // o valor da subsequencia incluindo ele, na coluna 0, e sem ele, na coluna 1
    int T[n][2];
    T[0][0] = v[0];
    T[0][1] = 0;

    std::vector<int> pessoas; // guadará a resposta
    int sem;

    for(int i = 1; i < n; i++)
    {
        // o valor atual maximo não incluindo o elemento
        sem = max(T[i - 1][0], T[i - 1][1]);

        T[i][0] = T[i - 1][1] + v[i]; // inclui o elemento com o valor do anterior não incluido
        T[i][1] = sem;
    }

    // percorremos a matriz de memorização de baixo para cima
    int j = n - 1;
    while(j >= 0)
    {
        // comparamos o valor do elemento atual incluido ou não
        // se o valor incluido é maior, e por que este pertence a subsequencia
        if(T[j][0] > T[j][1])
        {
            // logo, o anterior a ele não pode pertencer
            // caso contrario checaremos o anterior normalmente
            pessoas.push_back(v[j]);
            j--;
        }
        j--;
    }

    return pessoas;
}

int main()
{
    int n;
    std::cin >> n;
    int v[n];
    for(int i = 0; i < n; i++)
        std::cin >> v[i];

    std::vector<int> pessoas = vizinhos(v, n);
    for(auto &e: pessoas)
        std::cout << e << ' ';
    std::cout << '\n';
}
