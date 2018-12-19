/*
Duas cidades irão competir juntas na regional de ciclismo este ano. As equipes são de duas pessoas, que
usarão uma bicicleta de dois lugares para a corrida. As duplas devem ser formadas com um membro
de cada cidade. A velocidade de uma dupla é determinada pela velorcidade da pessoa mais rápida, já
que a mais lenta não conseguirá acompanhar o ritmo das pedaladas. Desejamos escolher as equipes
de forma que a soma das velocidades das suplas formadas seja a máxima possível, na esperança que
essas cidades vençam a competição. Considere que conhecemos as velocidades das pessoas de ambas
as cidades, disponíveis em A e B, onde cada um representa uma cidade.
Pareamos a pessoa mais rápida dentre as duas cidades com a pessoa mais lenta da outra
cidade.
*/

#include <bits/stdc++.h>
using namespace std;

typedef vector<pair<int, int>> vpii;

vpii ciclistas(int A[], int B[], int n)
{
    sort(A, A + n);
    sort(B, B + n);
    vpii duplas;
    for(int i = 0; i < n; i++)
    {
        duplas.push_back(make_pair(A[i], B[n - i - 1]));
    }
    return duplas;
}

int main()
{
    int n;
    cin >> n;
    int A[n], B[n];
    for(int i = 0; i < n; i++)
        cin >> A[i];
    for(int i = 0; i < n; i++)
        cin >> B[i];
    for(auto &dupla: ciclistas(A, B, n))
        cout << dupla.first << ',' << dupla.second << ' ';
    cout << endl;
}
