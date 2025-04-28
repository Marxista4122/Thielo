#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>


typedef struct Disco 
{

    int tamanho;
    struct Disco* proximo_disco;

} Disco;

typedef struct Pino
{

    Disco* topo;
    struct Pino* proximo_pino;

} Pino;

typedef struct Tabuleiro
{

    Pino* frente;
    Pino* costas;

} Tabuleiro;

bool inicializar_jogo(int discos_iniciais, int pinos_iniciais, Disco** discos, Pino** pinos, Tabuleiro** tabuleiro)
{
    Disco* aux = NULL;
    for (int i = discos_iniciais; i >= 1; i--) {
        Disco* novo_disco = (Disco*) malloc(sizeof(Disco));
        novo_disco->tamanho = i;
        novo_disco->proximo_disco = aux;
        aux = novo_disco;
    }
    *discos = aux;

    *tabuleiro = (Tabuleiro*) malloc(sizeof(Tabuleiro));
    (*tabuleiro)->frente = NULL;
    (*tabuleiro)->costas = NULL;

    
    Pino* primeiro = NULL;
    Pino* ultimo = NULL;

    for (int i = 0; i < pinos_iniciais; i++) {
        Pino* novo_pino = (Pino*) malloc(sizeof(Pino));
        novo_pino->topo = NULL;
        novo_pino->proximo_pino = NULL;

        if (i == 0) {
            
            novo_pino->topo = *discos;
            primeiro = novo_pino;
            ultimo = novo_pino;

        } else {

            ultimo->proximo_pino = novo_pino;
            ultimo = novo_pino;
        }
    }

    (*tabuleiro)->frente = primeiro;
    (*tabuleiro)->costas = ultimo;
    *pinos = primeiro;

    return true;
}


void percorrer_discos(Disco* discos)
{
    Disco* aux = discos;
    
    while(aux)
    {
        printf("%d \n", aux->tamanho);
        aux = aux->proximo_disco;
    }
}

void mostrar_tabuleiro(Tabuleiro* tabuleiro)
{
    
}

int main(void)
{

    Pino* pinos;
    Disco* discos;
    Tabuleiro* tabuleiro;

    int pinos_iniciais, discos_iniciais = 0;

    printf("Bem-Vindo ao hanoi! \n");
    printf("Com quantos pinos vocês deseja jogar? ");

    scanf("%d", &pinos_iniciais);
    
    if(pinos_iniciais < 3){pinos_iniciais = 3;}

    printf("\n %d Pinos. Ótima escolha! \n", pinos_iniciais);
    printf("E com quantos discos? ");
    
    scanf("%d", &discos_iniciais);

    if(discos_iniciais < 3){discos_iniciais = 3;}

    printf("\n %d Discos. Ótima ecolha! \n", discos_iniciais);

    printf("---Que comece o jogo!--- \n");

    //Recebendo o número de discos e de pinos                                               

    bool execucao = inicializar_jogo(discos_iniciais, pinos_iniciais, &discos, &pinos, &tabuleiro);
    percorrer_discos(discos);
}      

