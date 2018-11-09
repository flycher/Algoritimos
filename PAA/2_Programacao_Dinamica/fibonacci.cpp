/*
Calcula o numero de fibonacci usando programação dinâmica.
*/

#include <bits/stdc++.h>

int fibPD(int n)
{
    int T[n + 1];
    T[0] = 0;
    T[1] = 1;
    for(int i = 2; i <= n; i++)
        T[i] = T[i - 1] + T[i - 2];
    return T[n];
}

int main()
{
    int n;
    std::cin >> n;
    std::cout << fibPD(n) << '\n';
}
