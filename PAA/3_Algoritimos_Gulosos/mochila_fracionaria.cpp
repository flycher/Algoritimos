/*
Um ladrão vai entrar num deposito e precisa calcular que joias levar para ganhar mais
dinheiro, diante do limite de carga que ele possui.
- Mochila com capacidade M
- Conjunto de itens com n itens
*Cada item i possui um valor Vi e um peso pi.
*E diretamente proporcional a relação entre uma fração fi de um item e seus
parâmetros.
fi ----------> (fi*pi) (peso ocupado)
(função obtida) '--> (fi*vi) (ganho obtido)
Desejamos maximizar o ganho do que podemos levar na mochila.
Vamos considerar que sempre vamos poder levar a mochila cheia, pois, mesmo que algo
possua um peso que ultrapasse capacidade, ele pode ser fracionado para ser carregado.
* Se a soma dos pesos dos itens e menor que a capacidade total da mochila, a sol.
ótima é trivialmente levar 100% de todos os itens.
* Se a soma dos pesos dos itens for maior ou igual a M, podemos garantir que a
solução ótima preenche a mochila completamente.
Escolher o item de maior custo/beneficio, Vi/Pi, tomando o máximo que couber, ou seja,
incluir o maior sempre, e quando ele não couber mais, incluir o 2o maior
sob a mesma regra.
*/

#include <bits/stdc++.h>

bool ordena(std::pair<int, double> a, std::pair<int, double> b)
{
    return a.second > b.second;
}

std::pair<double, std::vector<double>> mochila_fracionaria(double v[], double p[], int n, double M)
{
    std::vector<std::pair<int, double>> itens;
    for(int i = 0; i < n; i++)
    {
        itens.push_back(std::make_pair(i, v[i] / p[i]));
    }

    std::sort(itens.begin(), itens.end(), ordena);

    double total = 0;
    std::vector<double> pegar(n, 0);
    int i = 0;
    while(i < n)
    {
        if(p[itens[i].first] <= M)
        {
            pegar[itens[i].first] = 1;
            total += v[itens[i].first];
            M -= p[itens[i].first];
        }
        else
        {
            pegar[itens[i].first] = M / p[itens[i].first];
            total += (M / p[itens[i].first]) * v[itens[i].first];
            break;
        }
        i++;
    }

    return std::make_pair(total, pegar);
}

int main()
{
    int M, n;
    std::cin >> M >> n;
    double v[n], p[n];
    for(int i = 0; i < n; i++)
        std::cin >> v[i] >> p[i];
    std::pair<double, std::vector<double>> greedy = mochila_fracionaria(v, p, n, M);
    std::cout << greedy.first << std::endl;
    for(auto &e: greedy.second)
        std::cout << e << ' ';
    std::cout << std::endl;
}
