/*
Dada uma expressão aritmética não-parentizada, onde ocorrem as operações de adição e multiplica-
ção, escreva um algoritmo de Programação Dinâmica para determinar qual é o maior valor que essa
expressão pode assumir se decidirmos parentizá-la, dentre todas as parentizações possíveis. Imagine
que a expressão será dada em uma lista onde o primeiro índice é um operando numérico e, a partir
do segundo, temos alternadamente uma operação e outro operando numérico (em outras palavras, nos
índices ímpares há operandos e nos pares há operações).
Por exemplo: Se a expressão for E = [1 + 2 ∗ 3 + 4 ∗ 5], uma das possíveis parentizações
dessa expressão seria (1 + 2) ∗ (3 + (4 ∗ 5)), resultando em 69, porém a que gera o maior dos resultados
seria ((1 + 2) ∗ (3 + 4)) ∗ 5, resultando em 105.
*/

#include <bits/stdc++.h>

typedef std::vector<int> vi;
typedef std::vector<char> vc;

int parentisa(vi &nums, vc &ops){
    int n = nums.size();
    int T[n][n];

    for(int i = 0; i < n; i++){
        T[i][i] = nums[i]; // preenchemos a diagonal principal com os numeros
    }

    // preenchemos o triangulo superior da matriz de baixo para cima, esquerda para direita
    for(int i = n - 1; i >= 0; i--)
    {
        for(int j = i + 1; j < n; j++)
        {
            int maior = INT_MIN; // maior valor possivel das operações
            for(int k = i; k < j; k++) // testamos todas as operações nessa faixa
            {
                if(ops[k] == '+')
                {
                    maior = std::max(maior, T[i][k] + T[k + 1][j]);
                }
                else
                {
                    maior = std::max(maior, T[i][k] * T[k + 1][j]);
                }

                T[i][j] = maior; // guardamos o maior valor possivel
            }
        }
    }

    return T[0][n - 1]; // retorna o maior valor possivel
}


int main()
{
    std::string E;
    std::cin >> E;
    int n = E.length();

    int** T = new int*[n];
    for(int i = 0; i < n; i++)
    {
        T[i] = new int[n];
        for(int j = 0; j < n; j++)
            T[i][j] = -1;
    }

    vi nums;
    vc ops;
    std::string numero = "";

    for(int i = 0; i < n; i++)
    {
        if(E[i] == '+' || E[i] == '*')
        {
            nums.push_back(std::stoi(numero));
            numero = "";
            ops.push_back(E[i]);
        }
        else
            numero += E[i];
    }

    nums.push_back(std::stoi(numero));

    std::cout << parentisa(nums, ops) << std::endl;
}
