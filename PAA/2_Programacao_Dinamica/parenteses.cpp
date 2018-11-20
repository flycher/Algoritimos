/*
Dada uma sequencia de parenteses, podemos uma parentização errada.
Podemos apenas trocar um '(' por um ')' ou vice-versa, de forma a conseguirmos
uma parentização consistente. As regras que definem uma parentização consistente são:
1. Uma sequência vazia é consistente.
2. Se uma sequência S é consistente, então a sequência (S) também é.
3. Se duas sequências S e T são consistentes, a concatenação ST também é.
Determine o mínimo de trocas necessárias para tornar uma parentização consistente.
*/

#include <bits/stdc++.h>
#define INF 999999

int equilibra(std::string parens, int i, int n, int aberto, int** & T){

	if(i > n){ // indice invalido
		if(aberto == 0) // nenhum parentese errado
			return 0;
		else
			return INF; // sequencia invalida
	}

	if(aberto == -1) // sequencia invalida
        return INF;

	if(T[i][aberto] != -1) // subproblema ja resolvido
		return T[i][aberto];

	int minimo = INF;

	if(parens[i] == '(') // se for um parentese abrindo
	{
		minimo = std::min(minimo, equilibra(parens, i + 1, n, aberto + 1, T));
		minimo = std::min(minimo, equilibra(parens, i + 1, n, aberto - 1, T) + 1);
		// minimo será o menor entre manter o parentese abrindo, ou mudar para um fechando
	}
	else // se for um parentese abrindo
	{
		minimo = std::min(minimo, equilibra(parens, i + 1, n, aberto + 1, T) + 1);
		minimo = std::min(minimo, equilibra(parens, i + 1, n, aberto - 1, T));
		// minimo será o menor entre manter o parentese fechando, ou mudar para um abrindo
	}

	return T[i][aberto] = minimo;
}

int parenteses(std::string parens)
{
    int n = parens.length();
	int **T = new int*[n]; // tabela de memorização
	for(int i = 0; i < n; i++)
	{
		T[i] = new int[n];
		for(int j = 0; j < n; j++)
			T[i][j] = -1;
	}

	return equilibra(parens, 0, n - 1, 0, T);
}

int main()
{
	std::string parens;
	std::cin >> parens;

	std::cout << parenteses(parens) << '\n';
}
