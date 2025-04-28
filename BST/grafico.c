#include <stdio.h>
#include <stdlib.h>

typedef struct Arvore {
    int valor;
    struct Arvore *esquerda;
    struct Arvore *direita;
} Arvore;

Arvore* criarNo(int valor) {
    Arvore* novo = (Arvore*)malloc(sizeof(Arvore));
    novo->valor = valor;
    novo->esquerda = NULL;
    novo->direita = NULL;
    return novo;
}

Arvore* construirArvoreExemplo() {
    Arvore* raiz = criarNo(10);
    
    // Subárvore esquerda
    raiz->esquerda = criarNo(5);
    raiz->esquerda->esquerda = criarNo(3);
    raiz->esquerda->direita = criarNo(7);
    
    // Subárvore direita
    raiz->direita = criarNo(15);
    raiz->direita->direita = criarNo(20);
    
    return raiz;
}

void gerarDOT(Arvore* no, FILE* arquivo) {
    if (no == NULL) return;
    
    // Declara o nó atual (opcional - Graphviz declara automaticamente)
    fprintf(arquivo, "  %d;\n", no->valor);
    
    // Conexão com filho esquerdo
    if (no->esquerda != NULL) {
        fprintf(arquivo, "  %d -> %d;\n", no->valor, no->esquerda->valor);
    }
    
    // Conexão com filho direito
    if (no->direita != NULL) {
        fprintf(arquivo, "  %d -> %d;\n", no->valor, no->direita->valor);
    }
    
    // Recursão para os filhos
    gerarDOT(no->esquerda, arquivo);
    gerarDOT(no->direita, arquivo);
}

int main() {
    // Construir a árvore de exemplo
    Arvore* raiz = construirArvoreExemplo();
    
    // Criar arquivo DOT
    FILE* dotFile = fopen("arvore.dot", "w");
    if (dotFile == NULL) {
        printf("Erro ao criar arquivo DOT\n");
        return 1;
    }
    
    // Escrever cabeçalho do DOT
    fprintf(dotFile, "digraph ArvoreBinaria {\n");
    fprintf(dotFile, "  Arvore [shape=circle, fontname=\"Arial\"];\n");
    
    // Gerar conteúdo do DOT
    gerarDOT(raiz, dotFile);
    
    // Fechar o arquivo DOT
    fprintf(dotFile, "}\n");
    fclose(dotFile);
    
    // Converter para imagem (requer Graphviz instalado)
    system("dot -Tpng arvore.dot -o arvore.png");
    
    printf("Árvore gerada com sucesso no arquivo 'arvore.png'\n");
    
    return 0;
}