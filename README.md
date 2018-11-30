
# Algoritimos

## *Estrutura de Dados:*

* Ordenação
  * Bubble Sort
    * Ω(n) | θ(n²) | O(n²)
  * Insertion Sort
    * Ω(n) | θ(n²) | O(n²)
  * Merge Sort
    * Ω(n log(n)) |  θ(n log(n)) | O(n log(n))
  * Heap Sort
    * Ω(n log(n)) | θ(n log(n)) | O(n log(n))
  * Quick Sort
    * Ω(n log(n)) | θ(n log(n)) | O(n²)
  * Counting Sort
    * Ω(n) | θ(n) | O(n)
* Pilha
  * LIFO
    * Topo: O(1) | Inserir: O(1) | Remover: O(1)
* Fila
  * FIFO
    * Cabeça: O(1) | Inserir: O(1) | Remover: O(1)
* Lista
  * Guarda valores, onde a ordem dos valores não importa
    * Buscar: O(n) | Inserir: O(1) | Remover: O(n)
* Árvore Binária de Busca
  * Guarda valores mantendo-os em ordem, com o maior a direita e o menor a esquerda
    * Buscar: O(h) | Inserir: O(h) | Remover: O(h)

## *Estrutura de Dados Avançada:*

* Árvore Rubro Negra
  * Árvore binária balanceada em que a altura e mantida sempre proxima de log n
    * Buscar: O(log n) | Inserir: O(log n) | Remover: O(log n)
* Tabela de Dispersão
  * Associa chaves de pesquisa a valores com objetivo de fazer uma busca rápida a partir da chave.
    * Buscar: θ(1) / O(n) | Inserir: θ(1) / O(n) | Remover: θ(1) / O(n)
* Lista de Prioridade
  * Guarda elementos a partir de sua prioridade
    * Mais Prioritário: O(1) | Inserir: O(log n) | Remover: O(log n) | Modificar Chave: O(log n)
* Conjunto Disjunto
  * Rastreia um conjunto de elementos particionados em vários subconjuntos disjuntos.
    * União: O(1) | Junção: O(1)
* Árvore B
  * Uma árvore balanceada em que um nó pode ter mais de um elemento e filhos. Usada para armazenamento em memória secundária.
    * Buscar: O(log n) | Inserir: O(log n) | Remover: O(log n)
* Grafos
  * Matriz de Adjacências
    * Os elementos da matriz indicam se os pares são adjacentes no grafo.
  * Lista de Adjacências
    * Cada elemento da lista indica um par adjacente.
  * Busca Em Largura
    * Descobre cada vértice que e alcançado por u, calculando sua menor distância para cada vértice v
  * Busca em Profundidade
    * Avança no grafo até alcançar um vértice que não possui nenhum vértice adjacente incalcançado. Após percorrer este vértice, retorna ao vértice anterior repetindo o processo.

## *Projeto e Análise de Algoritimos:*

* Problema e Instância, Algoritimos, Completude e Corretude, Eficiência de Algoritimos
* Divisão e Conquista: Esta técnica consiste em dividir um problema maior recursivamente em problemas menores até que o problema possa ser resolvido diretamente. Então a solução do problema inicial é dada através da combinação dos resultados de todos os problemas menores computados. O algoritimo é dividido em 3 fases:
    1. Divisão: o problema maior é dividido em problemas menores e os problemas menores obtidos são novamente divididos sucessivamente de maneira recursiva.
    2. Conquista: o resultado do problema é calculado quando o problema é pequeno o suficiente.
    3. Combinação: o resultado dos problemas menores são combinados até que seja obtida a solução do problema maior.
* Programação Dinâmica: Programação dinâmica é um método para a construção de algoritmos para a resolução de problemas computacionais, em especial os de otimização combinatória.Ela é aplicável a problemas nos quais a solução ótima pode ser computada a partir da solução ótima previamente calculada e memorizada - de forma a evitar recálculo - de outros subproblemas que, sobrepostos, compõem o problema original. O que um problema de otimização deve ter para que a programação dinâmica seja aplicável são duas principais características: subestrutura ótima e superposição de subproblemas. Podemos seguir 4 etapas para construir um algoritimo de PD:
    1. Caracterizar a estrutura de uma solução ótima.
        * Imaginar como se estruturar os dados de uma solucao ótima.
    2. Definir recursivamente o valor de uma solução ótima.
        * Aqui deve ocorrer subestrutura otima.
    3. Computar o valor de uma solução ótima algoritmicamente
        * D&C -> Memorização -> PD
    4. Construir uma solução ótima a partir de informações computadas sobre as decisões tomadas pelo algoritmo anterior.
        * Qual a melhor escolha tomada para cada sub-instancia?
* Algoritmos Gulosos: Aplicáveis no contexto de problemas de otimização. Funcionam de forma similar aos de PD no que se refere à forma de construção de soluções, tentado economizar tempo ao definir critérios de escolha para a construção de uma solução, em vez de testar várias possibilidades. Os critérios de escolha constituem o que chamamos de escolha gulosa, que podem ou não culminar em uma solução ótima, a depender das escolhas feitas. Escolhas gulosas sempre devem construir uma solução viável.

  * Para que um algoritmo guloso seja considerado correto devemos observar:
    1. Caracterização de uma solução ótima.
    2. Critérios de escolha gulosa.
    3. Subestrutura ótima do problema
  * Nem todos os problemas de otimização aceitam algoritmos gulosos corretos.
