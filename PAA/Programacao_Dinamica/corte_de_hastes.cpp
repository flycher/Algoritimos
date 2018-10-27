/*
Qual o melhor modo de cortar uma haste. Cada índice correspondente a um tamanho.
Insira o tamanho da haste e o preço de cada tamanho.
*/

#include <bits/stdc++.h>

std::pair<int*, int*> corteDeHastesPD(int p[], int n)
{
    int *r = new int[n + 1]; // tabela de respostas
    int *s = new int[n + 1]; // tabela de soluções
    r[0] = 0;
    for(int i = 1; i <= n; i++)
    {
        int q = INT_MIN; // o preço por tamanho de corte
        for(int j = 1; j <= i; j++)
        {
            if(q < (p[j] + r[i - j]))
            {
                // guardamos o melhor valor e o tamanho do corte
                q = p[j] + r[i - j];
                s[i] = j;
            }
        }
        r[i] = q;
    }
    return std::make_pair(r, s); // retorna as duas tabelas
}

int main()
{
    int n;
    std::cin >> n;
    int V[n + 1];
    V[0] = 0;

    for(int i = 1; i <= n; i++)
        std::cin >> V[i];

    std::pair<int*, int*> hastes = corteDeHastesPD(V, n);

    std::cout << "Ganho: \n\t[";
    for(int i = 1; i <= n; i++)
        std::cout << hastes.first[i] << ", ";
    std::cout << "]\n";

    std::cout << "Primeiro Corte: \n\t[";
    for(int i = 1; i <= n; i++)
        std::cout << hastes.second[i] << ", ";
    std::cout << "]\n";
}
