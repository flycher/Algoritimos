/*
Suponha que você foi contratado por uma empresa administradora de rodovias para solucionar o se-
guinte problema. A empresa deseja instalar postos de pedágio na rodovia BR-000 que sai de Quixadá
e atravessa o país na direção sul por M kilômetros. Os possíveis lugares de instalação desses postos
ficam nos marcos dados por x[1] < x[2] < · · · < x[n], onde cada x[i] representa a quantos quilômetros de
Quixadá fica o possível local de instalação i. Se for construído um posto de pedágio no marco x[i], o
valor a ser cobrado é dado por r[i] > 0. As regras impostas pela ANTT impedem que quaisquer dois
postos de pedágio sejam instalados a uma distância inferior a 5km.
Assim, a empresa deseja instalar pedágios na estrada de forma a obter o maior ganho possível. Por
exemplo, se tivéssemos M = 10 e n = 5, com os valores:
x = <6, 7, 12, 13, 14> e r = <5, 6, 5, 3, 1>
a melhor das opções seria instalar pedágios nos marcos x[2] e x[3], pois obteríamos um ganho de 11.
*/

#include <bits/stdc++.h>

int max(int a, int b)
{
    return a > b ? a : b;
}

std::vector<int> maior_pedagio(int X[], int R[], int n)
{
    int T[n][2]; // tabela de memorização
    int S[n]; // guarda o indice do posto valido de anterior a X[i]
    for(int i = 0; i < n; i++)
        S[i] = -1;

    T[0][0] = R[0];
    T[0][1] = 0;

    int com, sem, j;
    for(int i = 1; i < n; i++)
    {
        com = R[i]; // guarda o valor maximo ate i com X[i]
        sem = 0; // guarda o valor maximo ate i sem X[i]
        j = i;
        while(j >= 0) // a quantidade máxima de execuções desse loop é 5
        {
            if(X[i] - X[j] >= 5) // se temos uma distância em distâcia válida
            {
                com += T[j][0]; // adiconamos o valor de com ao valor maxímo possivel de j salvo na tabela
                S[i] = j; // guardamos o indice valido anterior a i
                break; // encerramos o loop
            }
            else // se a distância não é valida
            {
                sem = max(sem, T[j][0]); // atualizamos o valor de maxímo sem com o valor em j se maior
                j--; // olharemos o próximo posto
            }
        }
        T[i][0] = com; // guardamos o valor máximo ate i com este
        T[i][1] = sem; // guardamos o valor máximo ate i sem este
    }

    std::vector<int> solucao; // guardará os pontos em que devemos construir
    j = n - 1;
    while(j >= 0)
    {
        if(T[j][0] > T[j][1])
        {
            solucao.push_back(X[j]);
            j = S[j];
        }
        else
            j--;
    }

    return solucao;
}

int main()
{
    int n;
    std::cin >> n;
    int X[n];
    for(int i = 0; i < n; i++)
        std::cin >> X[i];
    int R[n];
    for(int i = 0; i < n; i++)
        std::cin >> R[i];

    std::vector<int> pedagios = maior_pedagio(X, R, n);
    for(auto &e: pedagios)
        std::cout << e << ' ';
    std::cout << '\n';
}
