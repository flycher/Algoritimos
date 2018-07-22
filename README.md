
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

## *Estrutuda de Dados Avançada:*

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
    * Cada elemento da lista indica um vizinho do vértice.
  * Busca Em Largura
    * Discobre cada vértice que e alcançado por u, calculando sua menor distância para cada vértice v
