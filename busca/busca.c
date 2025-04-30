#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>


typedef struct Arvore 
{
    int valor;
    struct Arvore* esquerda;
    struct Arvore* direita;
} Arvore;

Arvore* Criar(int i) 
{

    Arvore* raiz = NULL;
    int valores[i];
    int temp, sorteado;

    for(int j = 1; j <= i; j++)
    {
        valores[j - 1] = j;
    }

    for(int j = 0; j < i; j++)
    {
        sorteado = (rand() % i);
        temp = valores[j];
        valores[j] = valores[sorteado];
        valores[sorteado] = temp;
    }

    
    
}


int main(void) {
    srand((unsigned int)time(NULL));

    Arvore* raiz = Criar(10);

    return 0;
}