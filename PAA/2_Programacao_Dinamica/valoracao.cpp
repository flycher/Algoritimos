/*
Seja L uma lista de n números inteiros. A cada momento você pode escolher dois números adjacentes
na lista, eliminá-los e pôr em seu lugar o resultado da subtração do primeiro pelo segundo número
escolhido, na ordem em que estavam na lista. Depois de realizar essa operação n − 1 vezes, na lista
restará um único número m. Escreva um algoritmo de Programação Dinâmica que determina qual é o
maior valor possível para m ao final dessas operações dados os números na lista inicial.
Por exemplo: a sequência de operações a seguir gera o menor dos resultados para a lista L = [2 3 1 4],
com os números escolhidos a cada passo destacados.
[2, (3, 1), 4] → [2, (2, 4)] → [(2, -2)] → [4].
*/

#include <bits/stdc++.h>

int remove_lista(int E[], int n){
    int Tmin[n][n]; // guardaremos o maior valor possível das operações
    int Tmax[n][n]; // guardaremos o menor valor possível das operações

    for(int i = 0; i < n; i++){
        // preenche a diagonal principal com os numeros do vetor
        Tmin[i][i] = E[i];
        Tmax[i][i] = E[i];
    }

    // preenchemos o triangulo superior da matriz de baixo para cima, esquerda para direita
    for(int i = n - 1; i >= 0; i--){
        for(int j = i + 1; j < n; j++)
        {
            int menor = INT_MAX; // menor valor possível das operações
            int maior = INT_MIN; // maior valor possivel das operações
            for(int k = i; k < j; k++) // testamos todas as operações nessa faixa
            {
                menor = std::min(menor, Tmin[i][k] - Tmax[k + 1][j]);
                maior = std::max(maior, Tmax[i][k] - Tmin[k + 1][j]);
            }
            Tmin[i][j] = menor; // guardamos o maior valor possivel
            Tmax[i][j] = maior; // guardamos o menor valor possível
        }
    }
    return Tmax[0][n - 1]; // retorna o maior valor possivel
}

int main()
{
    int n;
    std::cin >> n;
    int v[n];
    for(int i = 0; i < n; i++)
        std::cin >> v[i];

    std::cout << remove_lista(v, n) << std::endl;
}
