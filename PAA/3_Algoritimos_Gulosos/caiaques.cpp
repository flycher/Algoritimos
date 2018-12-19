/*
Existem n caiaquistas que precisamos distribuir em caiaques de dois lugares de forma a respeitar o
peso máximo suportado pelos caiaques. Desejamos usar o mínimo possível de caiaques possível.
Você deve considerar que:
• O peso máximo suportado por cada caiaque é K,
• Conhecemos os pesos dos n caiaquistas, disponíveis em P ,
• Nenhum caiaquista pesa mais que o máximo suportado por um caiaque.
Devemos parear o caiaquista mais pesado com o caiaquista mais leve. Se esse par não for
possível, deixamos o caiaquista mais pesado sozinho e continuamos.
*/

#include <bits/stdc++.h>
using namespace std;

typedef vector<pair<int, int>> vpii;

vpii caiaquistas(int P[], int n,int K)
{
    sort(P, P + n);
    vpii caiaques;
    int i = 0, j = n - 1;
    while(i < j)
    {
        if(P[j] + P[i] <= K)
        {
            caiaques.push_back(make_pair(P[j], P[i]));
            i++;
            j--;
        }
        else
        {
            caiaques.push_back(make_pair(P[j], 0));
            j--;
        }
    }
    if(i == j)
    {
        caiaques.push_back(make_pair(P[j], 0));
    }
    return caiaques;
}

int main()
{
    int n, k;
    cin >> n >> k;
    int P[n];
    for(int i = 0; i < n; i++)
        cin >> P[i];
    for(auto &c: caiaquistas(P, n, k))
        cout << c.first << ',' << c.second << ' ';
    cout << endl;
}
