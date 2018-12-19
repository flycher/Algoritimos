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
using namespace std;

int lcs_K(string A, string B, int k)
{
    int a = A.length(), b = B.length(); // tamanhos das strings
    int** T = new int*[a + 1];

    for(int i = 0; i <= a; i++)
    {
        T[i] = new int[b + 1];
    }

    // não percorremos a linha e coluna 0
    // preenchemos a matriz inteira da esquerda para direita, de cima para baixo
    for(int i = k; i <= a; i++)
    {
        for(int j = k; j <= b; j++)
        {
            int c = 0;
            while(i - c > 0 && j - c > 0 && A[i - c - 1] == B[j - c - 1])
                c++;
            // caso os caracteres sejam iguais
            if(c >= k) T[i][j] = max(T[i - c][j - c] + c, T[i - 1][j - 1] + 1);
            // caso contrario, adicionamos o valor maior entre acima e a esquerda
            else T[i][j] = max(T[i - 1][j], T[i][j - 1]);
        }
    }

    // o ultimo elemento da matriz armazena o tamanho da maior subsequencia
    return T[a][b];
}


int main()
{
    int k;
    string A, B;
    cin >> k >> A >> B;
    cout << lcs_K(A, B, k) << endl;
}
