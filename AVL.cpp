#include<stdio.h>
#include<stdlib.h>

struct arvore{
	int info;
	struct arvore *e,*d;
};
typedef arvore Avl;

Avl* criaNo(int x){
	Avl *novo = (Avl*) malloc(sizeof(Avl));
	novo->info = x;
	novo->e = NULL;
	novo->d = NULL;
	return novo;
}
void rotacaoEsquerda(Avl **no){
    Avl *temp,*d;
    d = (*no) -> d;
    temp = d->e;
    d -> e = *no;
    (*no) -> d = temp;
    *no = d;
}

void rotacaoDireita(Avl **no){
    Avl *temp,*e;
    e = (*no) -> e;
    temp = e->d;
    e-> d = *no;
    (*no) -> e = temp;
    *no = e;
}

int altura(Avl *raiz){
	int altE,altD;
	if(raiz == NULL){
		return 0;
	}
	else{
		altE = altura(raiz->e);
		altD = altura(raiz->d);
		if(altE > altD){
			return 1 + altE;
		}
		else{
			return 1 + altD;
		}
	}
}

void insereAVL(Avl **raiz,int info,char *flag){
    int FB,FB_filho;
    if(*raiz==NULL){
        *raiz = criaNo(info);
        *flag = 1;
    }
    else{
        if( info > (*raiz) -> info){
            insereAVL(&(*raiz)->d,info,&*flag);
        }
        else{
            insereAVL(&(*raiz)->e,info,&*flag);
        }
        if(*flag){
            FB = altura((*raiz)->d) - altura((*raiz)->e);
            if(FB==-2 || FB==2){
                *flag = 0;
                if(FB==2){
                    FB_filho = altura((*raiz)->d->d) - altura((*raiz)->d->d);
                    if(FB_filho == 1){
                        rotacaoEsquerda(&(*raiz));
                    }
                    else{
                        rotacaoDireita(&(*raiz)->d);
                        rotacaoEsquerda(&(*raiz));
                    }
                }
                else{
                    FB_filho = altura((*raiz)->e->d) - altura((*raiz)->e->d);
                    if(FB_filho == -1){
                        rotacaoDireita(&(*raiz));
                    }
                    else{
                        rotacaoEsquerda(&(*raiz)->e);
                        rotacaoDireita(&(*raiz));
                    }
                }
            }
        }
    }
}

int main(){
    return 0;
}