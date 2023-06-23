#include <bits/stdc++.h>
struct Palavras {
    char info[30];
    int cod;
    struct Palavras* prox;
    char dig[30];
    int freq;
};

struct Arvh {
    int freq;
    int cod;
    struct Arvh* e;
    struct Arvh* d;
};

struct Prioridade {
    int cod;
    int freq;
    struct Arvh* arv;
    struct Prioridade* prox;
};

typedef struct Palavras Palavras;
typedef struct Arvh Arvh;
typedef struct Prioridade Prioridade;


Prioridade* criaNoL(Arvh *A){
    Prioridade *novo = (Prioridade*) malloc(sizeof(Prioridade));
    novo->arv = A;
    novo->prox = NULL;
    novo->freq = A->freq;
    novo->cod = A->cod;
    return novo;
}

void insf(Arvh *A, Prioridade **L){
    Prioridade *novo,*ant,*atu;
    novo = criaNoL(A);
    if(*L==NULL){
        *L=novo;
    }
    else{
        if(novo->freq < (*L) -> freq ){
            novo->prox = *L;
            *L = novo;
        } 
        else{
            ant = *L;
            atu = ant -> prox;
            while(atu!=NULL && novo->freq > atu->freq ){
                ant = atu;
                atu = atu -> prox;
            }
            ant->prox = novo;
            novo->prox = atu;
        }
    }
}


Palavras* criaNO(char aux[],int cod){
    Palavras *novo = (Palavras*) malloc(sizeof(Palavras));
    novo->prox= NULL;
    novo->cod = cod;
    strcpy(novo->info,aux);
    novo-> freq = 1;
    return novo;
}

void inserePalavra(char aux[],Palavras **L,int *cod){
    Palavras *novo, *p;
    if(*L==NULL){
        novo = criaNO(aux,*cod);
        (*cod)++;
        *L=novo;
    }
    else{
        p = *L;     
        while(p!=NULL && strcmp(aux,p->info)!=0) 
            p=p->prox;   
        if(p==NULL){
            novo = criaNO(aux,*cod);
            (*cod)++;
            novo->prox = *L;
            *L = novo;
        }
        else{
            p->freq++;
        }
    }
}

void quebraPalavras(char frase[],Palavras **L){
    int i=0,tl=0,cod=0;
    char aux[30];
    while(i<strlen(frase)){
        while(i<strlen(frase) && frase[i]==' ') {
            inserePalavra(" ",&(*L),&cod);
            i++;
        }
        tl=0;
        while(i<strlen(frase) && frase[i]!=' '){
            aux[tl] = frase[i];
            tl++;
            i++;
        }
        if(tl!=0){
            aux[tl]='\0';
            inserePalavra(aux,&(*L),&cod);
        }
    }
}

Arvh* criaNoA(int cod,int freq,Arvh *e,Arvh *d){
    Arvh *novo = (Arvh*) malloc(sizeof(Arvh));
    novo->e = e;
    novo->d = d; 
    novo->cod = cod;
    novo->freq =freq;
    return novo;
} 

Arvh* remf(Prioridade **L){
    Prioridade *excluido;
    Arvh *aux = (*L)->arv;
    excluido = *L;
    *L = (*L)->prox;
    free(excluido);
    return aux;
}


Arvh* huffman(Palavras *L){
    Prioridade *LP=NULL;
    Arvh *e,*d,*novo;
    while(L!=NULL){
        insf(criaNoA(L->cod,L->freq,NULL,NULL),&LP);
        L=L->prox;
    }
    while(LP->prox!=NULL){
        e= remf(&LP);
        d = remf(&LP);
        novo =  criaNoA(-1, e->freq + d->freq ,e,d);
        insf(novo,&LP);
    }
    return remf(&LP);
}

void codigo(Arvh *A,char cod[],int tl,Palavras *L){
    if(A->e==NULL && A->d==NULL){
        while(L->cod!=A->cod) 
            L=L->prox;
        cod[tl]='\0';
        strcpy(L->dig,cod);
    }
    else{
        cod[tl]='0';
        codigo(A->e,cod,tl+1,L);
        cod[tl]='1';
        codigo(A->d,cod,tl+1,L);
    }
}

void buscaPalavra(Palavras *L,char aux[],char cod[]){
    while(strcmp(L->info,aux)!=0){
        L=L->prox;
    }
    strcpy(cod,L->dig);
}

void comprimir(Palavras *L,char frase[],char comp[]){
	char aux[30],cod[30];
    int i=0,tl=0;
    while(i<strlen(frase)){
        while(i<strlen(frase) && frase[i]==' ') {
            buscaPalavra(L," ",cod);
            strcat(comp,cod);
            i++;
        }
        tl=0;
        while(i<strlen(frase) && frase[i]!=' '){
            aux[tl] = frase[i];
            tl++;
            i++;
        }
        if(tl!=0){
            aux[tl]='\0';
            buscaPalavra(L,aux,cod);
            strcat(comp,cod);
        }
    }
}

void descomprimir(Arvh *A,Palavras *L,char comp[]){
    Palavras *p;
    Arvh *aux=A;
    for(int i=0; i<strlen(comp);i++){
        if(comp[i]=='0') aux = aux->e;
        else aux = aux->d;
        if(aux->e==NULL && aux->d==NULL){

            p=L;
            while(p->cod!=aux->cod){
            	 p=p->prox;
            }
            printf("%s",p->info);
            aux=A;
        }
    }
}

int main() {
    char frase[] = "texto";
    char comp[1000] =""; 
    Palavras *L = NULL;
    Arvh *huff;
    char cod[30];
    quebraPalavras(frase,&L);
    huff = huffman(L);
    codigo(huff,cod,0,L);
    comprimir(L,frase,comp);
    printf("%s\n",comp);
    descomprimir(huff,L,comp);
    return 0;
}

