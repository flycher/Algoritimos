/*
Calcular x^n, onde x pertence aos reais e n aos naturais.
(Supondo que x e n não são nulos simultaneamente)
*/

#include <bits/stdc++.h>

long potNatural(int x, int n)
{
    if(n == 0)
        return 1;
    if(n % 2 == 0)
    {
        long pot = potNatural(x, n / 2);
        return pot * pot;
    }
    long pot = potNatural(x, (n - 1) / 2);
    return pot * pot * x;
}

int main()
{
    int x, n;
    std::cin >> x >> n;
    std::cout << potNatural(x, n) << std::endl;
}
