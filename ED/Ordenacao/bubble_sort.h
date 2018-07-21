//troca os elementos de posição
void swap(int *a, int *b)
{
    int temp = *a;
    *a = *b;
    *b = temp;
}

//recebe o array que queremos ordenar e seu tamanho
void bubbleSort(int* arr, int size)
{
    int key, i, j;
    bool sorted = false;

    //percorre todos os elementos, caso nenhuma troca aconteca finaliza o loop
    for(i = 0; i < size - 1 && !sorted; i++)
    {
        sorted = true;
        //compara cada elemento com o restante
        for(j = 0; j < size - i - 1; j++)
        {
            if(arr[j] > arr[j + 1])
            {
                swap(&arr[j], &arr[j + 1]);
                sorted = false;
            }
        }
    }
}
