#include<bits/stdc++.h>

std::string prefixoComum(std::string l, std::string r)
{
    int n, i = 0;
    l.length() < r.length() ? n = l.length() : n = r.length();
    std::string s = "";
    while(l[i] == r[i])
    {
        s += l[i];
        i++;
    }
    return s;
}

std::string maiorPrefixoComum(std::string words[], int p, int q)
{
    if(p == q) return words[p];
    int m = (p + q)/2;
    std::string l = maiorPrefixoComum(words, p, m);
    std::string r = maiorPrefixoComum(words, m + 1, q);
    return prefixoComum(l, r);
}

int main()
{
    int n;
    std::cin >> n;
    std::string words[n];
    for(int i = 0; i < n; i++)
        std::cin >> words[i];
    std::cout << maiorPrefixoComum(words, 0, n - 1).length() << '\n';
}
