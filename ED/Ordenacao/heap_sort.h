//troca os elementos de posição
void exchange(int *a, int *b)
{
    int temp = *a;
    *a = *b;
    *b = temp;
}

int pai(int i)
{
    return i / 2;
}

int left(int i)
{
    return 2 * i;
}

int right(int i)
{
    return 2 * i + 1;
}

//assume que i esta fora de posição no heap
void max_heapify(int* A, int i)
{
    int l = left(i);
    int r = right(i);
    int largest;

    if(l <= A[0] && A[l] > A[i])
        largest = l;
    else
        largest = i;

    if(r <= A[0] && A[r] > A[largest])
        largest = r;

    if(largest != i) {
        exchange(&A[i], &A[largest]);
        max_heapify(A, largest);
    }
}

//constroi um heap de maximo a partir de um array
void build_max_heap(int* A)
{
    for(int i = A[0] / 2; i >= 1; i--)
        max_heapify(A, i);
}

//recebe o array que queremos ordenar e seu tamanho
void heapSort(int* A, int size)
{
    //usamos um array auxiliar para as propriedades de heap começando em 1
    int i;
    int heap[size + 1]; //o array auxiliar e destruido ao sair da funçao
    heap[0] = size; //guarda o tamanho do heap

    //copia os valores de A para o heap
    for(i = 0; i < size; i++)
        heap[i + 1] = A[i];

    build_max_heap(heap);
    //a cada chamada, joga o maior elemento do array para o final do heap
    //considerando como ordenado, e diminui o tamanho do heap
    for(i = size; i >= 2; i--)
    {
        exchange(&heap[1], &heap[i]);
        heap[0]--;
        max_heapify(heap, 1);
    }

    //copia os valores de heap para o A, agora ordenados
    for(i = 0; i < size; i++)
        A[i] = heap[i + 1];
}
