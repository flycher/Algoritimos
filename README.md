
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
