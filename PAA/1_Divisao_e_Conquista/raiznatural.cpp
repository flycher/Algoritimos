/*
Você deve escrever uma função de Divisão e Conquista para determinar, dados
dois números naturais v e n, determine se existe algum número natural 
k tal que v^k = n. Sua função deve ter complexidade O(lg n).
*/

#include <bits/stdc++.h>

bool root(int v, int n, int l, int r)
{
    if(l <= r)
    {
        int m = (l + r)/2;
        int x = pow(v, m);

        if(x > n)
            return root(v, n, l, m - 1);
        else if(x < n)
            return root(v, n, m + 1, r);
        else
            return true;
    }
    return false;
}

char raizDC(int v, int n)
{
    if(n == 1)
        return 'V';
    if(v == 1 || v == 0)
        return 'F';

    int l = 0, r = 1, x = 1;

    while(x < n)
    {
        x = pow(v, r);
        l = r;
        r = r * 2;
    }
    // encontramos os expoentes de 2 em que a raiz se encontra
    if(root(v, n, l, r))
        return 'V';
    return 'F';
}

int main()
{
    int v, n;
    std::cin >> v >> n;
    std::cout << raizDC(v, n) << std::endl;
}
