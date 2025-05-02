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


Arvore* Inserir(Arvore* raiz, int valor)
{
    if(raiz == NULL)
    {
        raiz = (Arvore*) malloc(sizeof(Arvore));
        raiz->valor = valor;
        raiz->esquerda = NULL;
        raiz->direita = NULL;
    }
    else if(valor < raiz->valor)
    {
        raiz->esquerda = Inserir(raiz->esquerda, valor);
    }
    else 
    {
        raiz->direita = Inserir(raiz->direita, valor);
    }

    return raiz;
}

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

    for(int j = 0; j < i; j++)
    {
        raiz = Inserir(raiz, valores[j]);
    }

    return raiz;
    
}

void PosOrdem(Arvore* raiz)
{
    if(!raiz)
        return;
    PosOrdem(raiz->esquerda);
    PosOrdem(raiz->direita);
    printf("%d \n", raiz->valor);
}

int ContarNodos(Arvore* raiz)
{
    if(!raiz)
        return 0;

    int total = 0;
    total++;
    total += ContarNodos(raiz->esquerda) + ContarNodos(raiz->direita);

    return total;
}

int Maior(Arvore* raiz)
{
    if(!raiz)
    {
        printf("A árvore é vazia!");
        return INT_MIN;
    }

    while(raiz->direita)
        raiz = raiz->direita;
    return raiz->valor;
}

int main(void) {
    srand((unsigned int)time(NULL));

    Arvore* raiz = Criar(40);

    gerarGraphviz(raiz);
    //PosOrdem(raiz);
    int quantidade_nodos = ContarNodos(raiz);
    printf("Quantidade de nodos da árvore: %d \n", quantidade_nodos);

    int maior_valor = Maior(raiz);
    printf("Maior valor na árvore: %d \n", maior_valor);

    return 0;
}