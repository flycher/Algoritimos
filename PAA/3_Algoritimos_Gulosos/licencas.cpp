/*
Você e seus amigos vão começar uma empresa de segurança e precisam obter licenças das autorida-
des de segurança para compor as partes do software que criaram. Por conta da regulamentação, as
empresas que não quiserem compartilhar com o governo detalhes do funcionamento do que estão de-
senvolvendo ficam limitadas a adquirir apenas uma licença por mês. Preocupados com questões de
privacidade e de direitos, vocês decidem que a melhor opção é realmente se submeter às limitações.
Cada licença atualmente está atrelada a um custo de R$100. Entretanto, os custos com cada licença
aumentam a cada mês de forma exponencial: em particular, o custo de uma licença j aumenta por
um fator rj > 1 a cada mês. Isso significa que se a licença j for comprada daqui a t meses, ela custará
R$100 · rj^t . Vamos assumir que os fatores de aumento de cada licença são distintos entre si.
A pergunta é: Obedecendo as restrições, dados o custo inicial de R$100, a quantidade n de licenças e
os fatores de aumento das n licenças que vocês precisam adquirir, em que ordem comprar as licenças
de forma a minimizar o custo total de sua aquisição? Forneça um algoritmo que determina essa ordem.
A complexidade do seu algoritmo deve ser polinomial em n.
Reordenaremos o vetor com a ordem em que as licencas devem ser comprados
*/

#include <bits/stdc++.h>
using namespace std;

typedef struct
{
    int n, r;
} licenca;

bool ordena(licenca a, licenca b)
{
    return a.r > b.r;
}

void* licencas(licenca* & R, int n)
{
    sort(R, R + n, ordena);
}

int main()
{
    int n;
    cin >> n;
    licenca* R = new licenca[n];
    for(int i = 0; i < n; i++)
    {
        R[i].n = i + 1;
        cin >> R[i].r;
    }
    licencas(R, n);
    for(int i = 0; i < n; i++)
        cout << R[i].n << ' ';
    cout << endl;
}
