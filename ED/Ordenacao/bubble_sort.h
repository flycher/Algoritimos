//recebe o array que queremos ordenar e seu tamanho
void bubbleSort(int* A, int size)
{
    int key, i, j;
    bool sorted = false;

    //percorre todos os elementos, caso nenhuma troca aconteca, finaliza o loop
    for(i = 0; i < size - 1 && !sorted; i++)
    {
        sorted = true;
        //compara cada elemento com o restante
        for(j = 0; j < size - i - 1; j++)
        {
            if(A[j] > A[j + 1])
            {
                key = A[j];
                A[j] = A[j + 1];
                A[j + 1] = key;
                sorted = false;
            }
        }
    }
}
