//recebe o array que queremos ordenar e seu tamanho
void insertionSort(int* A, int size)
{
    int key, i, j;

    for(j = 1; j < size; j++)
    {
        key = A[j];
        i = j - 1;

        //procura a posicao correta do elemento no array
        //movendo os elementos maiores para a direita
        while(i >= 0 && A[i] > key){
            A[i + 1] = A[i];
            i = i - 1;
        }

        //posiciona o elemento em seu lugar correto
        A[i + 1] = key;

    }
}
