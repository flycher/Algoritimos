//troca os elementos de posição
void exchange(int *a, int *b)
{
    int temp = *a;
    *a = *b;
    *b = temp;
}

int parent(int i)
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
void max_heapify(int* arr, int i)
{
    int left_child = left(i);
    int right_child = right(i);
    int largest;

    if(left_child <= arr[0] && arr[left_child] > arr[i])
        largest = left_child;
    else
        largest = i;

    if(right_child <= arr[0] && arr[right_child] > arr[largest])
        largest = right_child;

    if(largest != i)
    {
        exchange(&arr[i], &arr[largest]);
        max_heapify(arr, largest);
    }
}

//constroi um heap de maximo a partir de um array
void build_max_heap(int* arr)
{
    for(int i = arr[0] / 2; i >= 1; i--)
        max_heapify(arr, i);
}

//recebe o array que queremos ordenar e seu tamanho
void heapSort(int* arr, int size)
{
    //usamos um array auxiliar para podermos usar
    //das propriedades de heap começando em 1
    int i;
    int heap[size + 1]; //o array auxiliar e destruido ao sair da funçao
    heap[0] = size; //guarda o tamanho do heap

    //copia os valores de arr para o heap
    for(i = 0; i < size; i++)
        heap[i + 1] = arr[i];

    build_max_heap(heap);
    //a cada chamada, joga o maior elemento do array para o final do heap
    //considerando como ordenado, e diminui o tamanho do heap
    for(i = size; i >= 2; i--)
    {
        exchange(&heap[1], &heap[i]);
        heap[0]--;
        max_heapify(heap, 1);
    }

    //copia os valores de heap para o arr, agora ordenados
    for(i = 0; i < size; i++)
        arr[i] = heap[i + 1];
}
