/*
Nesse problema, dadas duas sequências X e Y , devemos encontrar o comprimento
da maior subsequência Z comum a ambas X e Y , porém com a restrição de que Z deve ser
formada por segmentos de pelo menos 2 elementos em X e em Y . Um segmento é uma subsequência
onde os elementos escolhidos são contíguos.
Por exemplo: sejam X = [c a s a x x x x x] e Y = [x c a x s a x x x]. As sub-
sequências Z1 = [c a s a] e Z2 = [x x x x x] são subsequências comuns a X e Y . Porém Z2
é obtida de Y através de dois segmentos de tamanho 1 e outro de tamanho 3. Como nesse caso há
segmentos de tamanho menor que 2 e essa é a única forma de obter Z2 de Y , temos que ela não é uma
subsequência 2-comum.
Escreva um algoritmo de Programação Dinâmica para o problema da Maior Subsequência k-Comum,
onde as subsequências consideradas são aquelas formadas por segmentos de pelo
menos k elementos nas sequências dadas.
*/

#include <bits/stdc++.h>

int max(int a, int b)
{
    return a > b ? a : b;
}

int lcsK(std::string x, int i, std::string y, int j, int k, int** & T)
{
    if(T[i][j] != -1) // se já calculamos para estes indices
        return T[i][j];

    // se um dos indices e menor que k nao podemos montar uma subsequencia de tamanho ao menos k
    if(i < k || j < k)
        return 0;

    int c = 0;
    // percorremos comparando indices decrescentes de x e y enquanto estes são iguais
    while(i - c > 0 && j - c > 0 && x[i - c - 1] == y[j - c - 1])
        c++;
    // se chegamos a caracteres diferentes, e temos pelomenos k iguais, estes podem formar a subsequencia
    if(c >= k)
        return T[i][j] = c + lcsK(x, i - c, y, j - c, k, T);
        // guardamos o resultado na matriz, fazendo a busca desconsiderando o que já contamos
    // não conseguindo a sequencia tamanho k procuramos o maior entre desconsiderar o ultimo de x ou y
    return max(lcsK(x, i - 1, y, j, k, T), lcsK(x, i, y, j - 1, k, T));
}

int maior_subsequencia_comum_k(std::string A, std::string B, int k)
{
    int n = A.length(), m = B.length();
    int **T = new int*[n + 1];
    for(int i = 0; i <= n; i++)
    {
        T[i] = new int[m + 1];
        for(int j = 0; j <= m; j++)
            T[i][j] = -1;
    }

    return lcsK(A, n, B, m, k, T); // passamos a matriz de memorização e as strings com os indices
}

int main()
{
    int k;
    std::string A, B;
    std::cin >> k >> A >> B;
    std::cout << maior_subsequencia_comum_k(A, B, k) << '\n';
}
