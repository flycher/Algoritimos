#include <bits/stdc++.h>

unsigned long fibDC(unsigned long n)
{
    if(n == 0)
        return 0;

    unsigned long Fib[2][2] = {{1,1},{1,0}};
    unsigned long x, y, z, w;

    for (int i = 2; i <= n; i++)
    {
        x =  Fib[0][0] + Fib[0][1];
        y =  Fib[0][0];
        z =  Fib[1][0] + Fib[1][1];
        w =  Fib[1][0];

        Fib[0][0] = x;
        Fib[0][1] = y;
        Fib[1][0] = z;
        Fib[1][1] = w;
    }

    return Fib[0][1];
}

int main()
{
    int n;
    std::cin >> n;
    std::cout << fibDC(n) << std::endl;
}
