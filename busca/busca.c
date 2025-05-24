#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <locale.h>
#include <limits.h>


typedef struct Lista 
{
    int valor;
    struct Lista* antigo;
    struct Lista* novo;
} Lista;

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
    fprintf(dotFile, "Nodos [shape=circle, fontname=\"Arial\", style=filled, fillcolor=lightblue];\n");

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

int Procura(Arvore* raiz, int valor1, int valor2)
{
    if(!raiz)
        return 0;
    if(raiz->valor == valor1 || raiz->valor == valor2)
        return 1 + Procura(raiz->direita, valor1, valor2) + Procura(raiz->esquerda, valor1, valor2);
    return Procura(raiz->direita, valor1, valor2) + Procura(raiz->esquerda, valor1, valor2);
}

void EsquerdaDireita(Arvore* nodo, int valor1, int valor2)
{
    int achou_esq, achou_dir;

    achou_esq = Procura(nodo->esquerda, valor1, valor2);
    achou_dir = Procura(nodo->direita,valor1, valor2);

    if(achou_dir == 2 || achou_esq == 2)
        printf("Sim");
    else 
        printf("Não");
    
    return;
}

Lista* Converter(Arvore* raiz) 
{
    static Lista* ANTERIOR = NULL;
    static Lista* TOPO = NULL;
    //Variáveis static sobrevivem a várias chamadas da função e mantém seu valor
    //Não sei se é a melhor abordagem, mas achei o conceito interessante
    //PS.: Não é o melhor jeito. Deveria só ter passado anterior e topo como parâmetros

    if(!raiz)
        return TOPO;
    
    Converter(raiz->esquerda);

    Lista* atual = (Lista*) malloc(sizeof(Lista));
    atual->valor = raiz->valor;
    atual->novo = NULL;


    if(ANTERIOR)
    {
        ANTERIOR->novo = atual;
    }
    else
    {
        TOPO = atual;
    }
    atual->antigo = ANTERIOR;
    ANTERIOR = atual;

    Converter(raiz->direita);
    
    return TOPO;
    
}

void PercorrerLista(Lista* lista)
{
    while(lista)
    {
        printf("Valor da lista: %d \n", lista->valor);
        lista = lista->novo;
    }
}

int main(void) {
    setlocale(LC_ALL, ""); //Tava dando erro na formatação do terminal e tentei ver se isso resolvia. Não resolveu
    srand((unsigned int)time(NULL));

    Arvore* raiz = Criar(6);

    gerarGraphviz(raiz);
    //PosOrdem(raiz); Comentado porque polui muito o terminal
    int quantidade_nodos = ContarNodos(raiz);
    printf("Quantidade de nodos da árvore: %d \n", quantidade_nodos);

    int maior_valor = Maior(raiz);
    printf("Maior valor na árvore: %d \n", maior_valor);

    EsquerdaDireita(raiz, 20, 2);

    Lista* lista = Converter(raiz);
    PercorrerLista(lista);

    return 0;
}