/*
Quem nunca foi surpreendido pela infame pergunta: "Aceita balinha?"?
O pior é que às vezes o pobre do caixa realmente não tem como nos fornecer o
valor que devemos receber por não ter as moedas necessárias!
Vamos ver se no nosso caso realmente vamos ter que receber balinhas ou não.
Imagine que o caixa tenha disponível moedas de valores dentre {v1, v2, v3, ..., vk},
em quantidade suficiente, e que ele tenha que nos devolver o valor N de troco.
Usando as moedas disponíveis, ele é capaz de nos dar o troco ou vamos ter que aceitar a balinha?
*/

#include <bits/stdc++.h>
using namespace std;

bool troco_ou_bala(int troco, int moedas[], int n)
{
    // tabela guarda os trocos que podemos dar para cada valor ate o troco que queremos passar
    int* T = new int[troco + 1];

    for (int i = 0; i <= troco; i++) // troco máximo para cada valor de troco
      for(int j = 0; j < n; j++) // as moedas disponiveis
         if(moedas[j] <= i) // se a moeda tem valor menor que o troco atual
            // guardamos no troco maximo atual o maior valor entre o atual e o troco
            // maximo possivel entre o troco maximo para um valor atual sem a moeda atual
            // somada com a moeda atual
            T[i] = max(T[i], T[i - moedas[j]] + moedas[j]);

    // se o troco maximo que podemos passar é igual ao troco que queremos
    return T[troco] == troco;
}

int main()
{
	int troco, n;
    cin >> troco >> n;
    int moedas[n];
    for(int i = 0; i < n; i++)
        cin >> moedas[i];
    if(troco_ou_bala(troco, moedas, n))
        cout << "troco" << endl;
    else
        cout << "balinha" << endl;
}
