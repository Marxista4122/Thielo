#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

void exibir_vetor(char* vetor[], int tamanho)
{

    for(int j = 0; j < tamanho; j++)
        printf("%s \n", vetor[j]);
     printf("-------------------------------------------- \n");
    
}

int main()
{

    FILE *arquivo = fopen("nomes.txt", "r");

    int i, j;
    i = 0;

    char nome[100];
    char auxiliar[100];
    char* vetor[100];

    while(fgets(nome, sizeof(nome), arquivo) != NULL && i < 100)
    {
        nome[strcspn(nome, "\n")] = '\0';

        vetor[i] = (char*) malloc(strlen(nome) + 1);

        strcpy(vetor[i], nome);
        i++;
    }

    exibir_vetor(vetor, 6);

    i = 0;

    for(i  = 1; i < 6; i++)
    {
        strcpy(auxiliar, vetor[i]);

        for(j = i; (j > 0) && (strcmp(auxiliar, vetor[j - 1]) < 0); j--)
        {
            strcpy(vetor[j], vetor[j - 1]);
        }
        strcpy(vetor[j], auxiliar);
    }
    
    exibir_vetor(vetor, 6);

    return 0;
}