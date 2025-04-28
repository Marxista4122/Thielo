#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct Arvore {
    int valor;
    struct Arvore* esquerda;
    struct Arvore* direita;
} Arvore;

void inserir_nodo(Arvore** arvore, int valor){

    if((*arvore) == NULL) {
        Arvore* aux = (Arvore*) malloc(sizeof(Arvore));
        aux->valor = valor;
        aux->esquerda = NULL;
        aux->direita = NULL;
        (*arvore) = aux;
        return;
    }

    if(valor > (*arvore)->valor)
    {
        inserir_nodo(&(*arvore)->direita, valor);
    } else {
        inserir_nodo(&(*arvore)->esquerda, valor);
    }
    
}

/////////////////////Graphviz paranaues//////////////////////////////////
void gerarDOT(Arvore* no, FILE* arquivo) {
    if (no == NULL) return; 
    
    fprintf(arquivo, "  %d;\n", no->valor);
    
    if (no->esquerda != NULL) {
        fprintf(arquivo, "  %d -> %d;\n", no->valor, no->esquerda->valor);
    }
    
    if (no->direita != NULL) {
        fprintf(arquivo, "  %d -> %d;\n", no->valor, no->direita->valor);
    }
    
    gerarDOT(no->esquerda, arquivo);
    gerarDOT(no->direita, arquivo);
}

void gerarGraphviz(Arvore* raiz) 
{
    FILE* dotFile = fopen("arvore.dot", "w");
    if(dotFile == NULL)
    {
        printf("Erro ao criar o arquivo \n");
        return;
    }

    //Escrevendo o cabeçalho
    fprintf(dotFile, "digraph ArvoreBinaria {\n" );
    fprintf(dotFile, "Nodos [shape=circle, fontname=\"Arial\"];\n");

    gerarDOT(raiz, dotFile);

    //Fechando o arquivo
    fprintf(dotFile, "}\n");
    fclose(dotFile);

    //Convertendo para image (graphviz)
    system("dot -Tpng arvore.dot -o arvore.png");
    printf("Árvore gerada com sucesso no arquivo 'arvore.png'\n");

    return;

}
//////////////////////////////////////////////////////////


int main(void)
{
    Arvore* raiz = NULL;

    for (int i = 1; i <= 31; i++) {
        inserir_nodo(&raiz, i);
    }

    //gerarGraphviz(raiz);

    ///////////////////// Segunda parte da atividade //////////////////////////
    //Preciso preencher um vetor com números de 1 a 31 e trocar todos de lugar com rand J
    srand((unsigned int)time(NULL));

    Arvore* raiz2 = NULL;
    int vetor[31], valor_temp, j;

    for(int i = 1; i <= 31; i++) 
    {
        vetor[i] = i;
    }

    for(int i = 1; i <= 31; i++)
    {
        valor_temp = vetor[i];
        j = (rand() % 31) + 1;
        vetor[i] = vetor[j];
        vetor[j] = valor_temp;
    }

    for(int i = 1; i <= 31; i++) 
    {
        inserir_nodo(&raiz2, vetor[i]);
    }

    gerarGraphviz(raiz2);

    return 0;
}