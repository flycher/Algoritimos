//recebe o array, os indices inicial, do meio e final
#ifndef GUARD_merge_sort_h
#define GUARD_merge_sort_h

void merge(int* arr, int left, int mid, int right)
{
    //l e r recebem os tamanhos dos subarray da esquerda e direita
    int l = mid - left + 1;
    int r = right - mid;
    int i, j, k;

    //cria os arrays da esquerda e da direita com l +1 e r + 1 posições
    int L[l + 1], R[r + 1];

    //preenchemos os arrays L e R com os subarrays esquerdo e direito de arr
    for(i = 0; i < l; i++)
        L[i] = arr[left + i];
    for(j = 0; j < r; j++)
        R[j] = arr[mid + j + 1];

    //na ultima posicao prechenchemos com um numero maior possivel do inteiro
    //este representa uma sentinela, para evitar ficar checando
    //se arrays estão vazios
    L[l] = 2147483647;
    R[r] = 2147483647;

    i = 0;
    j = 0;

    //paramos o loop quando executamos a mesma quantidade de passos
    //que o tamanho do array
    //"andamos" em L quando inserimos um elemento em arr
    //o mesmo acontece em R
    for(k = left; k <= right; k++)
    {
        if(L[i] <= R[j])
        {
            arr[k] = L[i];
            i++;
        }
        else
        {
            arr[k] = R[j];
            j++;
        }
    }
}

//recebe o array que queremos ordenar, os indices inicial e final
//na primeira chamada, left deve ser 0 e right o tamanho do array - 1
void mergeSort(int* arr, int left, int right)
{
    if(left < right)
    {
        //mid recebe o indice do meio no array
        //chamamos entao mergeSort novamente para o array do inicio ao meio
        //e do meio + 1 ao final
        //enfim chamamos merge para o array
        int mid = (left + right) / 2;
        mergeSort(arr, left, mid);
        mergeSort(arr, mid + 1, right);
        merge(arr, left, mid, right);
    }
}

#endif
