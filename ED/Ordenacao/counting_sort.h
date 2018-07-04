//maior numero no array
const int MAX = 1000001;

//recebe o array com numeros naturais até MAX e seu tamanho
void countingSort(int* A, int k)
{
    int C[MAX] = {0};

    for(int i = 0; i < k; i++) {
        C[A[i]]++;
    }

    int j = 0;
    for(int i = 0; i < MAX; i++)
    {
        while(C[i])
        {
            A[j] = i;
            C[i]--;
            j++;
        }
    }
}
