/*
Dado um conjunto de atividades A, representados por intervalos semiabertos,
determinar o maior subconjunto de A que contém apenas atividades compatíveis,
ou seja, cujos intervalos não se interceptam.
Escolher a atividade que termina primeiro, desconsiderar as atividades que chocam
com a escolhida, repetir o processo para as atividades restantes.
*/

#include <bits/stdc++.h>

typedef struct
{
    int n, inicio, fim;
} atividade;

bool ordena(atividade a, atividade b)
{
    return a.fim < b.fim;
}

std::vector<bool> escolha(std::vector<atividade> atividaddes, int tempo)
{
    std::sort(atividaddes.begin(), atividaddes.end(), ordena);
    std::vector<bool> escolhidas(atividaddes.size(), false);
    int inicio = -1;
    std::cout << std::endl;
    for(auto &a: atividaddes)
    {
        if(a.inicio > inicio && a.fim <= tempo)
        {
            escolhidas[a.n] = true;
            inicio = a.fim;
        }
    }
    return escolhidas;
}

int main()
{
    int n, i, f, tempo;
    std::cin >> tempo >> n;
    std::vector<atividade> atividades;
    for(int i = 0; i < n; i++)
    {
        atividade a;
        a.n = i;
        std::cin >> a.inicio >> a.fim;
        atividades.push_back(a);
    }

    std::vector<bool> greedy = escolha(atividades, tempo);
    for(auto e: greedy)
        std::cout << e << ' ';
    std::cout << std::endl;
}
