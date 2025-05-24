//Texto explicando as chamadas resursivas já foi mostrado em aula
#include <stdio.h>
#include <stdlib.h>


typedef struct Arv
{
    int info;
    struct Arv* esq;
    struct Arv* dir;
} Arv;

Arv* Busca(Arv* r, int v)
{
    if(r == NULL) return NULL;
    else if(r->info > v) return Busca(r->esq, v);
    else if(r->info < v) return Busca(r->dir, v);
    else return r;
}

Arv* insere (Arv* a, int v)
{
    if(a == NULL)
    {
        a = (Arv*) malloc(sizeof(Arv));
        a->info = v;
        
        a->esq = NULL;
        a->dir = NULL;
        
        return a;
    }
    
    if(v < a->info)
    {
        a->esq = insere(a->esq, v);
        return a;
    } else 
    {
        a->dir = insere(a->dir, v);
        return a;
    }
    
}

Arv* retira(Arv* r, int v)
{
    if(!r)
    {
        return NULL;
    }
    else if (r->info > v)
    {
        r->esq = retira(r->esq, v);
    } else if(r->info < v)
    {
        r->dir = retira(r->dir, v);
    } else 
    {
        if(r->esq == NULL && r->dir == NULL)
        {
            free(r);
            r = NULL;
        } else if(r->esq == NULL)
        {
            Arv* t = r;
            r = r->dir;
            free(t);
        } else if(r->dir == NULL)
        {
            Arv* t = r;
            r = r->esq;
            free(t);
        } else 
        {
            Arv* pai = r;
            Arv* f = r->esq;
            while(f->dir != NULL) 
            {
                pai = f;
                f = f->dir;
            }
            
            r->info = f->info;
            f->info = v;
            r->esq = retira(r->esq, v);
            
        }
    }
    return r;
}

void imprime(Arv* nodo)
{
    if(nodo)
    {
        imprime(nodo->esq);
        printf("%d\n", nodo->info);
        imprime(nodo->dir);
    }
}

int main()
{
    Arv* arvore = NULL;
    
    arvore = insere(arvore, 7);
    arvore = insere(arvore, 2);
    arvore = insere(arvore, 12);
    arvore = insere(arvore, 3);
    arvore = insere(arvore, 9);
    arvore = insere(arvore, 14);
    
    imprime(arvore);

    return 0;
}