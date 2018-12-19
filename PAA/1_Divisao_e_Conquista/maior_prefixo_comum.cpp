/*
Dada uma lista de palavras com pelo menos um caractere cada, você deve escrever
uma função de Divisão e Conquista que determina o maior prefixo comum a todas
as palavras da lista. Seu algoritmo deve possuir complexidade  Theta(m lg n),
onde n é o número de palavras na lista e m é o comprimento da maior delas.
Uma palavra A é prefixo de outra B se A está completamente contida no início
de B, ou seja, B é formada por A seguida de zero ou mais caracteres.
*/

#include <bits/stdc++.h>
using namespace std;

string prefixoComum(string l, string r)
{
    int n, i = 0;
    l.length() < r.length() ? n = l.length() : n = r.length(); // menor string
    string s = "";
    while(i < n && l[i] == r[i]) // adiciona prefixos a s
    {
        s += l[i];
        i++;
    }
    return s;
}

string maiorPrefixoComum(string words[], int p, int q)
{
    if(p == q) return words[p];
    int m = (p + q)/2;
    string l = maiorPrefixoComum(words, p, m);
    string r = maiorPrefixoComum(words, m + 1, q);
    return prefixoComum(l, r);
}

int main()
{
    int n;
    cin >> n;
    string words[n];
    for(int i = 0; i < n; i++)
        cin >> words[i];
    cout << maiorPrefixoComum(words, 0, n - 1).length() << endl;
}
