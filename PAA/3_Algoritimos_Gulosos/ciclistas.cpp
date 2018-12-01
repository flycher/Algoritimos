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

typedef std::vector<std::pair<int, int>> vpii;

vpii ciclistas(int A[], int B[], int n)
{
    std::sort(A, A + n);
    std::sort(B, B + n);
    vpii duplas;
    for(int i = 0; i < n; i++)
    {
        duplas.push_back(std::make_pair(A[i], B[n - i - 1]));
    }
    return duplas;
}

int main()
{
    int n;
    std::cin >> n;
    int A[n], B[n];
    for(int i = 0; i < n; i++)
        std::cin >> A[i];
    for(int i = 0; i < n; i++)
        std::cin >> B[i];
    for(auto &dupla: ciclistas(A, B, n))
        std::cout << dupla.first << ',' << dupla.second << ' ';
    std::cout << std::endl;
}
