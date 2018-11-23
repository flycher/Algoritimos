/*
Dada uma cadeia de matrizes <A1, A2, A3, …,  An>, em que para i = [1, 2, …, n],
Ai tem dimensões [pi-1 x pi], determine os parênteses do produto
A1 * A2 * A3 * … * An para minimizar a quantidade de multiplicações escalares.
*/

#include <bits/stdc++.h>

std::pair<int, int**> mcm(int D[], int n)
{
    int T[n + 1][n + 1]; // matriz de multplicações escalares
    int **S = new int*[n + 1]; // matriz de soluções
    int min, val;

   for(int i = 1; i <= n; i++)
    {
        T[i][i] = 0;
        S[i] = new int[n + 1];
    }

    // percorreremos a matriz de baixo para cima, esquerda para direita
    for(int i = n - 1; i >= 1; i--)
    {
        for(int j = i + 1; j <= n; j++)
        {
            min = INT_MAX;
            // possiveis multiplicações na subinstancia
            for(int k = i; k <= j - 1; k++)
            {
                val = T[i][k] + T[k + 1][j] + D[i - 1]*D[k]*D[j];
                if(val < min) // numero de multiplicações comparado com menor atual
                {
                    min = val;
                    S[i][j] = k; // produto que gera melhor solução para i:j
                }
            }
            T[i][j] = min;
        }
    }

    return std::make_pair(T[1][n], S); // numero minimo de multiplicações e matriz de solução
}

void print_parens(int **S, int i, int j)
{
    if(i == j) std::cout << 'A' << i;
    else
    {
        std::cout << '(';
        print_parens(S, i, S[i][j]);
        print_parens(S, S[i][j] + 1, j);
        std::cout << ')';
    }
}

void mult_mat_cadeia(int D[], int n)
{
    std::pair<int, int**> ans = mcm(D, n);
    std::cout << ans.first << std::endl;
    print_parens(ans.second, 1, n);
}

int main()
{
    int n;
    std::cin >> n;
    int D[n]; // vetor de dimensões, onde D[0] == lin(A1), D[i] = col(Ai)
    for(int i = 0; i < n; i++)
        std::cin >> D[i];
    mult_mat_cadeia(D, n - 1); // existem n - 1 matrizes
    std::cout << std::endl;
}
