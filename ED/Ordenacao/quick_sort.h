
#ifndef GUARD_quick_sort_h
#define GUARD_quick_sort_h

#include <cstdlib>
#include <iostream>

//troca os elementos de posição
void interchange(int *a, int *b)
{
    int temp = *a;
    *a = *b;
    *b = temp;
}

//particiona o array em 2 subarrays, onde
//todos os elementos da esquerda são menores ou iguais a arr[i + 1]
//e todos os elementos da direita são maiores que arr[i + 1]
int partition(int* arr, int left, int right)
{
    //selectiona elemento aleatorio do array como pivô
    srand(time(NULL));
    int random = left + rand() % (right - left);
    interchange(&arr[random], &arr[right]);

    int pivot = arr[right];
    int i = left - 1;

    for(int j = left; j < right; j++)
    {
        if(arr[j] <= pivot)
        {
            i++;
            interchange(&arr[i], &arr[j]);
        }
    }

    i++;
    interchange(&arr[i], &arr[right]);

    return i;
}

//q sera o elemento que dividira em dois subarrays
//a primeira chamada left ser 0 e right o tamanho do array - 1
void quickSort(int* arr, int left, int right)
{
    if(left < right)
    {
        int q = partition(arr, left, right);
        quickSort(arr, left, q - 1);
        quickSort(arr, q + 1, right);
    }
}

#endif
