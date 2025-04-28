#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void exibir_vetor(int *vetor, int tamanho)
{
    for(int i = 0; i < tamanho; i++)
        printf("%d \n", vetor[i]);
    printf("---------------------------------------- \n");
}

void preencher_vetor(int *vetor, int tamanho)
{
    srand(time(NULL));
    for(int i = 0; i < tamanho; i++)
        vetor[i] = (rand() % 100) + 1;
}

void selection_sort(int *vetor, int tamanho)
{
    int aux;
    int menor;

    for(int i = 0; i < tamanho - 1; i++)
    {
        menor = i;

        for(int j = i + 1; j < tamanho; j++)
        {
            if(vetor[menor] > vetor[j])
                menor = j;
        }

        aux = vetor[i];
        vetor[i] = vetor[menor];
        vetor[menor] = aux;

    }

}

void bubble_sort(int *vetor, int tamanho)
{
    int aux, continua;

    do {
        continua = 0;

        for(int i = 0; i < tamanho - 1; i++)
        {
            if(vetor[i] > vetor[i + 1])
            {
                continua = 1;
                aux = vetor[i];
                vetor[i] = vetor[i + 1];
                vetor[i + 1] = aux;
            }
        }
        tamanho--;

    } while(continua);

}

void insertion_sort(int *vetor, int tamanho)
{
    int aux;
    int i, j;

    for(i = 1; i < tamanho; i++)
    {
        aux = vetor[i];

        for(j = i; (j>0) && (aux < vetor[j - 1]); j--)
            vetor[j] = vetor[j - 1];
        vetor[j] = aux;

    }

}

int partition(int *arr, int left, int right)
{

    int pivot = arr[right];
    int i = left - 1;
    int aux;

    for(int j = left; j < right; j++)
    {
        if(arr[j] <= pivot)
        {
            i++;
            aux = arr[i];
            arr[i] = arr[j];
            arr[j] = aux;
        }
    }

    return i + 1;

}

void quick_sort(int *arr, int left, int right)
{

    int pi = right;

    if (left < right)
    {
        pi = partition(arr, left, right);
        quick_sort(arr, left, pi - 1);
        quick_sort(arr, pi + 1, right);
    }
}

int main(void)
{
    int vetor[5];
    int tamanho = 5;

    preencher_vetor(vetor, tamanho);

    exibir_vetor(vetor, tamanho);

    quick_sort(vetor, 0, 4);

    exibir_vetor(vetor, tamanho);
}