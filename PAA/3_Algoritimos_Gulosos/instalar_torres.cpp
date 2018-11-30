/*
Considere o trecho da BR-122 entre Quixadá e Quixeramobim, onde as casas ao longo das margens
se distribuem bem esparsamente. Os moradores dessa região, para não ficarem de fora das novidades
do mundo, são ávidos usuários de celulares. Uma empresa de telecomunicações deseja espalhar suas
antenas em certos pontos ao longo dessa rodovia para atender os clientes dessa região de forma que
todos estejam a um máximo de 4km de alguma antena.
Forneça uma algoritmo que, dadas a quantidade n de residências e as distâncias de cada uma delas, em
km, até o ponto inicial do trecho, determina em que pontos da estrada devem ser instaladas antenas de
forma a minimizar a quantidade necessária.
Retornaremos uma lista com as posições em que as torres devem ser instaladas.
*/

#include <bits/stdc++.h>

bool ordena(int a, int b)
{
    return a < b;
}

std::vector<int> instalar_torres(int* & C, int n)
{
    std::sort(C, C + n, ordena);
    std::vector<int> T;
    int alcance = -1;
    for(int i = 0; i < n; i++)
    {
        if(C[i] > alcance)
        {
            T.push_back(C[i] + 4);
            alcance = C[i] + 8;
        }
    }
    return T;
}

int main()
{
    int n;
    std::cin >> n;
    int* C = new int[n];
    for(int i = 0; i < n; i++)
        std::cin >> C[i];
    std::vector<int> T = instalar_torres(C, n);
    for(auto &e: T)
        std::cout << e << ' ';
    std::cout << std::endl;
}
