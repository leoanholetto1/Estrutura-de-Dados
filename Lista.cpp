#include<stdio.h>
#include<stdlib.h>

struct Lista{
    int valor;
    Lista *prox;
};

Lista* criaCaixa(int valor){
    Lista *novo = (Lista*) malloc(sizeof(Lista));
    novo -> valor = valor;
    novo -> prox = NULL;
    return novo; 
}

Lista* inserirInicio(Lista *L,int valor){
    Lista *novo = criaCaixa(valor);
    if(L == NULL) L = novo;
    else{
        novo -> prox = L;
        L = novo;
    }
    return L;
}

Lista* inserirFim(Lista *L,int valor){
    Lista *novo = criaCaixa(valor),*aux;
    if(L == NULL) L = novo;
    else{
        aux = L;
        while(aux->prox != NULL) aux = aux->prox;
        aux -> prox = novo;
    }
    return L;
}

char busca(Lista *L,int valor){
    while(L!=NULL && L->valor!=valor) L = L->prox;
    return L==NULL;
}

Lista* remover(Lista *L,int valor){
    Lista *aux,*ant;
    if(L->valor == valor){
        aux = L;
        L = L->prox;
        free(aux);
    }
    else{
        ant = L;
        aux = L->prox;
        while(aux!=NULL && aux->valor != valor){
            ant = aux;
            aux = aux -> prox;
        }
        if(aux != NULL){
            ant->prox = aux->prox;
            free(aux);
        }
    }
    return L;
}

int main(){
    Lista *L = NULL;
    L = inserirInicio(L,10);
    L = inserirInicio(L,12);
    L = inserirFim(L,22);
    if(busca(L,10)){
        L = remover(L,10);
    }
    else{
        printf("Nao achou!");
    }
    return 0;
}