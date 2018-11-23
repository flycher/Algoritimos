/*
Dado um vetor ordenado V , determina se existe alguma
identidade em V , ou seja, um índice i tal que V [i] = i.
*/

#include <bits/stdc++.h>

bool identidade(int V[], int p, int q)
{
    if(p <= q)
    {
        int m = (p + q) / 2;
        if(V[m] == m)
            return true;
        return identidade(V, p, m - 1) || identidade(V, m + 1, q);
    }
    return false;
}

int main()
{
    int n;
    std::cin >> n;
    int V[n];
    for(int i = 0; i < n; i++)
        std::cin >> V[i];
    if(identidade(V, 0, n - 1))
        std::cout << 'V' << std::endl;
    else
        std::cout << 'F' << std::endl;

}
