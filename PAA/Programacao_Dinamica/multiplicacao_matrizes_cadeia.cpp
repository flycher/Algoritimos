#include <bits/stdc++.h>

int mcm(int D[], int n)
{
    n--;
    int T[n + 1][n + 1];
    int min, val;

   for(int i = 1; i <= n; i++)
    {
        T[i][i] = 0;
    }

    for(int i = n - 1; i >= 1; i--)
    {
        for(int j = i + 1; j <= n; j++)
        {
            min = INT_MAX;
            for(int k = i; k <= j - 1; k++)
            {
                val = T[i][k] + T[k + 1][j] + D[i - 1]*D[k]*D[j];
                if(val < min)
                {
                    min = val;
                }
            }
            T[i][j] = min;
        }
    }

    return T[1][n];
}

int main()
{
    int n;
    std::cin >> n;
    int D[n];
    for(int i = 0; i < n; i++)
        std::cin >> D[i];
    std::cout << mcm(D, n) << '\n';
}
