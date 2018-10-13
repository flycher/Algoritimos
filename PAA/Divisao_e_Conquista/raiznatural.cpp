#include <bits/stdc++.h>

bool aux(int v, int n, int l, int r)
{
    if(l <= r)
    {
        int m = (l + r)/2;
        int x = pow(v, m);

        if(x > n)
            return aux(v, n, l, m - 1);
        else if(x < n)
            return aux(v, n, m + 1, r);
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

    if(aux(v, n, l, r))
        return 'V';
    return 'F';
}

int main()
{
    int v, n;
    std::cin >> v >> n;
    std::cout << raizDC(v, n) << '\n';
}
