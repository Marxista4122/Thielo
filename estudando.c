#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

void printar_vetor(int* vetor, int tamanho)
{
    for(int i = 0; i < tamanho; i++)
    {
        printf("Número %d: %d \n", i + 1, vetor[i]);
    }
}

void preencher_vetor(int** vetor, int tamanho)
{
    *(vetor) = (int*) malloc(sizeof(int) * tamanho);
    
    for(int i = 0; i < tamanho; i++)
    {

        (*vetor)[i] = (rand() % 100) + 1;

    }
}

void liberar(int **vetor){
    free(*vetor);
    *vetor = NULL;
}


int main (void)
{

    srand(time(NULL));

    int* vetor;

    preencher_vetor(&vetor, 45);

    printar_vetor(vetor, 45);


}