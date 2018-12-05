/*
Dada uma sequencia de parenteses, podemos uma parentização errada.
Podemos apenas trocar um '(' por um ')' ou vice-versa, de forma a conseguirmos
uma parentização consistente. As regras que definem uma parentização consistente são:
1. Uma sequência vazia é consistente.
2. Se uma sequência S é consistente, então a sequência (S) também é.
3. Se duas sequências S e T são consistentes, a concatenação ST também é.
Determine o mínimo de trocas necessárias para tornar uma parentização consistente.
*/

#include <bits/stdc++.h>

int parenteses(std::string s)
{
    int n = s.size();
    int T[2][n + 1]; // guardaremos os parenteses abrindo na linha 0 e as inversões na 1
    T[0][0] = 0;
    T[1][0] = 0;

    for(int i = 1; i <= n; i++)
    {
        if(s[i - 1] == '(')
        {
            T[0][i] = T[0][i - 1] + 1; // aumenta a quantidade de parenteses abrindo
            T[1][i] = T[1][i - 1]; // mantem as inversões
        }
        else
        {
            if(T[0][i - 1] == 0) // se não temos nenhum abrindo
            {
                T[0][i] = 1;
                T[1][i] = T[1][i - 1] + 1; // invertemos o parentese fechando
            }
            else
            {
                T[0][i] = T[0][i - 1] - 1; // caso tenhamos parenteses abrindo
                T[1][i] = T[1][i - 1]; // mantemos as inversões
            }
        }
    }

    return (T[0][n] / 2) + T[1][n]; // se temos mais de um abrindo, metade destes serão invertidos
}

int main()
{
    std::string s;
    std::cin >> s;
    std::cout << parenteses(s) << std::endl;
}
