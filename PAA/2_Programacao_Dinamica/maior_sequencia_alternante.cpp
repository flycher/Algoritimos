/*
Dado um vetor de N inteiros não-nulos, você deve determinar o tamanho da maior
subsequência alternante contida neste vetor. Uma sequência alternante é uma
sequência que possui as seguintes propriedades:
    b1 < b2 < b3 < ... < bk
    Os sinais alternam entre elementos adjacentes, isto é:
         se b1 > 0  então  b2 < 0, b3 > 0  etc.
         se  b1 < 0  então b2 > 0, b3 < 0  etc.
Uma subsequência de um vetor V é uma sequência obtida através da eliminação de
alguns elementos do vetor, porém sem alterar a ordem relativa entre os que restarem.
*/

#include <bits/stdc++.h>

bool dif(int a, int b)
{
    return abs(a) > abs(b) && ((a > 0 && b < 0) || (a < 0 && b > 0));
}

int msa(int V[], int n)
{
    int T[n];
    int max, sol = 1;
    T[0] = 1;
    for(int i = 0; i < n; i++)
    {
        max = 0;
        for(int j = 0; j < i; j++)
        {
            if(dif(V[i], V[j]) && T[j] > max)
                max = T[j];
        }
        max++;
        T[i] = max; // tamanho da maior sequencia até i
        if(max > sol)
            sol = max;
    }
    return sol;
}

int main()
{
    int n;
    std::cin >> n;
    int V[n];
    for(int i = 0; i < n; i++)
        std::cin >> V[i];
    std::cout << msa(V, n) << std::endl;
}
