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
    int T[n][n];

    for(int i = 0; i < n; i++){
        T[i][i] = E[i]; // preenche a diagonal principal com os numeros
    }

    // preenchemos o triangulo superior da matriz de baixo para cima, esquerda para direita
    for(int i = n - 1; i >= 0; i--){
        for(int j = i + 1; j < n; j++)
        {
            int maior = INT_MIN; // maior valor possivel das operações
            for(int k = i; k < j; k++) // testamos todas as operações nessa faixa
                if(k < n - 1)
                {
                    maior = std::max(maior, T[k + 1][j] - T[i][k]);
                }
            T[i][j] = maior; // guardamos o maior valor possivel
        }
    }

    return T[0][n - 1]; // retorna o maior valor possivel
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
