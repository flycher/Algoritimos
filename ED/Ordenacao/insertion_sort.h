//recebe o array que queremos ordenar e seu tamanho
void insertionSort(int* arr, int size)
{
    int key, i, j;

    for(j = 1; j < size; j++)
    {
        key = arr[j];
        i = j - 1;

        //procura a posição correta do elemento no array
        //movendo os elementos maiores para a direita
        while(i >= 0 && arr[i] > key)
        {
            arr[i + 1] = arr[i];
            i = i - 1;
        }

        //posiciona o elemento em seu lugar correto
        arr[i + 1] = key;
    }
}
