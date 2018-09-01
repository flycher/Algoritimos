#ifndef GUARD_counting_sort_h
#define GUARD_counting_sort_h
//maior numero no array

const int MAX = 1000010;

//recebe o array com numeros naturais até MAX e seu tamanho
void countingSort(int* arr, int size)
{
    int count[MAX] = {0};

    for(int i = 0; i < size; i++)
    {
        count[arr[i]]++;
    }

    int j = 0;

    for(int i = 0; i < MAX; i++)
    {
        while(count[i])
        {
            arr[j] = i;
            count[i]--;
            j++;
        }
    }
}

#endif
