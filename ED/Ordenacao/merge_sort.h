//recebe o array, os indices inicial, do meio e final
void merge(int* A, int p, int q, int r)
{
    //n1 e n2 recebem os tamanhos dos subarray da esquerda e direita
    int n1 = q - p + 1;
    int n2 = r - q;
    int i, j, k;

    //cria os arrays da esquerda e da direita com n1 +1 e n2 + 1 posições
    int L[n1 + 1], R[n2 + 1];

    //preenchemos os arrays L e R com os subarrays esquerdo e direito de A
    for(i = 0; i < n1; i++)
        L[i] = A[p + i];
    for(j = 0; j < n2; j++)
        R[j] = A[q + j + 1];

    //na ultima posicao prechenchemos com um numero maior possivel do inteiro
    //este representa uma sentinela, para evitar ficar checando
    //se arrays estão vazios
    L[n1] = 2147483647;
    R[n2] = 2147483647;

    i = 0;
    j = 0;

    //paramos o loop quando executamos a mesma quantidade de passos
    //que o tamanho do array
    //"andamos" em L quando inserimos um elemento em A
    //o mesmo acontece em R
    for(k = p; k <= r; k++)
    {
        if(L[i] <= R[j]) {
            A[k] = L[i];
            i++;
        } else {
            A[k] = R[j];
            j++;
        }
    }
}

//recebe o array que queremos ordenar, os indices inicial e final
//na primeira chamada, p deve ser 0 e r o tamanho do array - 1
void mergeSort(int* A, int p, int r)
{
    if(p < r) {
        //q recebe o indice do meio no array
        //chamamos entao mergeSort novamente para o array do inicio ao meio
        //e do meio + 1 ao final
        //enfim chamamos merge para o array
        int q = (p + r) / 2;
        mergeSort(A, p, q);
        mergeSort(A, q + 1, r);
        merge(A, p, q, r);
    }
}
