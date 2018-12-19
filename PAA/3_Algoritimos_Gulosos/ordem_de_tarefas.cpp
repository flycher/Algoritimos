/*
A superpopular ferramenta de buscas Q? precisa realizar uma grande quantidade de processamento a
cada vez que precisa recompilar seu índice. Felizmente, a companhia dispõe de um grande supercom-
putador, junto a uma quantidade essencialmente ilimitada de PCs de ótima configuração.
Eles dividiram a computação geral em n processamentos distintos, rotulados J1 , J2 , ... , Jn , que podem
ser realizados de forma completamente independente entre si. Cada tarefa de processamento consiste
de dois estágios: um preprocessamento no supercomputador e uma finalização em algum PC, cada um
consumindo uma certa quantidade de tempo dependendo da tarefa. Vamos dizer que J i necessita de p i
segundos no supercomputador seguidos de f i segundos em um PC.
Já que existem mais que n PCs disponíveis na empresa especificamente para essa atividade, as finali-
zações das tarefas podem ser ralizadas completamente em paralelo. Entretanto, o supercomputador só
pode trabalhar em uma tarefa por vez, sem preempção, de forma que os engenheiros precisam deter-
minar uma ordem na qual entregar as tarefas a ele. Assim que uma tarefa, na ordem, for finalizada, ela
poderá ser delegada a algum PC; nesse momento, a próxima tarefa pode ser enviada ao supercomputador.
Forneça um algoritmo polinomial em n para determinar uma ordem na qual o tempo final do proces-
samento seja minimizado. O tempo final é o tempo desde o início da recompilação até o momento em
que todas as tarefa tenham finalizado suas execuções.
*/

#include <bits/stdc++.h>
using namespace std;

typedef struct
{
    int t, p, f;
} tarefa;

bool ordena(tarefa a, tarefa b)
{
    return a.f > b.f;
}

void* processamento(tarefa* & J, int n)
{
    sort(J, J + n, ordena);
}

int main()
{
    int n;
    cin >> n;
    tarefa* J = new tarefa[n];
    for(int i = 0; i < n; i++)
    {
        J[i].t = i + 1;
        cin >> J[i].p >> J[i].f;
    }
    processamento(J, n);
    for(int i = 0; i < n; i++)
        cout << J[i].t << ' ';
    cout << endl;
}
