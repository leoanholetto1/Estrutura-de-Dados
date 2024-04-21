#include<stdio.h>
#include<stdlib.h>

const int k = 2;

struct Node{
    int ponto[k];
    Node *esq, *dir;
};

Node* criaNo(int ponto[]){
    Node *novo = (Node*) malloc(sizeof(Node));
    novo->esq = NULL;
    novo->dir = NULL;
    for(int i=0;i<k;i++) 
        novo->ponto[i] = ponto[i];
    return novo;
}

Node* inserir(Node *Arv,int ponto[],int tl = 0){
    if(Arv == NULL) return criaNo(ponto);

    if(ponto[tl] > Arv -> ponto[tl]) Arv->dir = inserir(Arv->dir,ponto,(tl+1)%k);
    else Arv->esq = inserir(Arv->esq,ponto,(tl+1)%k);
    return Arv;
}

char compara(Node *Arv,int ponto[]){
    for (int i = 0; i < k; ++i)
        if (Arv->ponto[i] != ponto[i])
            return 0;
    return 1;
}

char busca(Node *Arv,int ponto[],int tl = 0){
    if(Arv == NULL) return 0;
    else{
        if(compara(Arv,ponto)) return 1;
        else{
            if(ponto[tl] > Arv -> ponto[tl]) return busca(Arv->dir,ponto,(tl+1)%k);
            else return busca(Arv->esq,ponto,(tl+1)%k);
        }
    }
}


int main(){
    Node *Arv = NULL;
    return 0;   
}