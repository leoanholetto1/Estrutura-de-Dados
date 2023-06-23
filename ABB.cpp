#include<stdio.h>
#include<stdlib.h>

struct arvore{
	int info;
	struct arvore *e,*d;
};
typedef arvore Arv;

Arv* criaNo(int x){
	Arv *novo = (Arv*) malloc(sizeof(Arv));
	novo->info = x;
	novo->e = NULL;
	novo->d = NULL;
	return novo;
}

void preordemR(Arv *raiz){
	if(raiz!=NULL){
		printf("%d\n",raiz->info);
		preordemR(raiz->e);
		preordemR(raiz->d);
	}
}

void inordemR(Arv *raiz){
	if(raiz!=NULL){
		inordemR(raiz->e);
		printf("%d\n",raiz->info);
		inordemR(raiz->d);
	}
}

void posordemR(Arv *raiz){
	if(raiz!=NULL){
		posordemR(raiz->e);
		posordemR(raiz->d);
		printf("%d\n",raiz->info);
	}
}

Arv* buscaR(Arv *raiz,int x){
	if(raiz==NULL){
		return NULL;	
	}
	else{
		if(x == raiz->info){
			return raiz;
		}
		else if(x < raiz->info){
			return buscaR(raiz->e,x);
		}
		else{
			return buscaR(raiz->d,x);
		}
	}
}

void inserirR(Arv **raiz,int x){
	if(*raiz == NULL){
		*raiz = criaNo(x);
	}
	else{
		if( x > (*raiz)->info){
			inserirR(&(*raiz)->d,x);
		}
		else{
			inserirR(&(*raiz)->e,x);
		}
	}
	
}

int levelR(Arv *raiz,int x){
	if(x==raiz->info){
		return 0;
	}
	else{
		if(x > raiz->info){
			return 1 + levelR(raiz->d,x);
		}
		else{
			return 1 + levelR(raiz->e,x);
		}
	}	
}

int alturaR(Arv *raiz){
	int altE,altD;
	if(raiz == NULL){
		return 0;
	}
	else{
		altE = alturaR(raiz->e);
		altD = alturaR(raiz->d);
		if(altE > altD){
			return 1 + altE;
		}
		else{
			return 1 + altD;
		}
	}
}

void limparR(Arv *raiz){
	if(raiz!=NULL){
		limparR(raiz->e);
		limparR(raiz->d);
		free(raiz);
	}
}

Arv* buscaI(Arv *raiz,int x){
	while(raiz!=NULL && raiz->info!=x){
		if(x > raiz->info){
			raiz = raiz ->d;
		}
		else{
			raiz = raiz ->e;
		}
	}
	return raiz;
}

void inserirI(Arv **raiz,int x){
	Arv *novo,*aux,*pai;
	if(*raiz == NULL){
		*raiz = criaNo(x);
	}
	else{
		aux = *raiz;
		novo = criaNo(x);
		while(aux != NULL){
			pai = aux;
			if( x > aux -> info){
				aux = aux->d;
			}
			else{
				aux = aux->e;
			}
		}
		if(x > pai->info){
			pai->d = novo;
		}
		else{
			pai->e = novo;
		}
	}
}

void exibeLevel(Arv *raiz){
	FilaArv *F;
	int c, quant = 1,i;	
	initFila(&F);
	enqueue(&F,raiz);
	while(!emptyFila(F)){
		c=0;
		for(i=0;i < quant ; i++){
			dequeue(&F,&raiz);
			printf("%d\n",raiz->info);
			if(raiz->e != NULL){
				c++;
				enqueue(&F,raiz->e);
			}
			if(raiz->d != NULL){
				c++;
				enqueue(&F,raiz->d);
			}
		}
		quant = c;
	}
}

void preordemI(Arv *raiz){
	PilhaArv *P;
	initPilha(&P);
	push(&P,raiz);
	while(!emptyPilha(P)){
		pop(&P,&raiz);
		while(raiz!=NULL){
			printf("%d\n",raiz->info);
			if(raiz->d != NULL){
				push(&P,raiz->d);
			}
			raiz = raiz -> e;
		}
	}
}

void inordemI(Arv *raiz){
	PilhaArv *P;
	initPilha(&P);
	push(&P,raiz);
	while(!emptyPilha(P)){
		while(raiz!=NULL){
			push(&P,raiz); 
			raiz = raiz -> e;
		}
		pop(&P,&raiz);
		printf("%d\n",raiz->info);
		raiz = raiz -> d;
	}
}

void posordemI(Arv *raiz){
	PilhaArv *P1,*P2;
	initPilha(&P1);
	initPilha(&P2);
	push(&P1,raiz);
	while(!emptyPilha(P1)){
		pop(&P1,&raiz);
		push(&P2,raiz);
		if(raiz->e != NULL){
			push(&P1,raiz->e);
		}
		if(raiz->d != NULL){
			push(&P1,raiz->d);
		}
	}
	while(!emptyPilha(P2)){
		pop(&P2,&raiz);
		printf("%d\n",raiz->info);
	}
}

int contaNo(Arv *raiz,int *cont){
	if(raiz!=NULL){
		(*cont)++;
		contaNo(raiz->e,cont);
		contaNo(raiz->d,cont);
	}
}

void exclusaoABB(Arv **raiz,Arv *filho,Arv *pai){
	Arv *paisub,*sub;
	if(filho->e==NULL && filho->d==NULL){ //folha
		if(filho!=raiz){
			if(filho == pai->e ){
				pai->e = NULL;
			}
			else{
				pai->d = NULL;
			}
		}
		else
			*raiz = NULL;
		free(filho);
	}
	else{
		if(filho->e==NULL || filho->d==NULL){ //tem um filho
			if(filho!=raiz){
				if(filho == pai -> e){
					if(filho->e == NULL){
						pai->e = filho->d;
					}
					else{
						pai->e = filho->e;
					}
				}
				else{
					if(filho->e == NULL){
						pai->d = filho->d;
					}
					else{
						pai->d = filho->e;
					}
				}
			}
			else{
				if(filho->e == NULL){
					*raiz = filho->d;
				}
				else{
					*raiz = filho->e;
				}
			}
			free(filho);
		}
		else{	//tem dois filhos
			paisub = filho;
			sub = filho->d;
			while(sub->e!=NULL){
				paisub = sub;
				sub = sub -> e;
			}
			filho->info = sub ->info;
			if(sub == filho->d){
				paisub->d = sub->d;
			}
			else{
				paisub->e = sub->d;
			}
			free(sub);
		}
	}
}

void exclusaoABBBalanceada(Arv **raiz,Arv *filho,Arv *pai,char lado){
	Arv *paisub,*sub;
	if(filho->e==NULL && filho->d==NULL){ //folha
		if(filho!=raiz){
			if(filho == pai->e ){
				pai->e = NULL;
			}
			else{
				pai->d = NULL;
			}
		}
		else
			*raiz = NULL;
		free(filho);
	}
	else{
		if(filho->e==NULL || filho->d==NULL){ //tem um filho
			if(filho!=raiz){
				if(filho == pai -> e){
					if(filho->e == NULL){
						pai->e = filho->d;
					}
					else{
						pai->e = filho->e;
					}
				}
				else{
					if(filho->e == NULL){
						pai->d = filho->d;
					}
					else{
						pai->d = filho->e;
					}
				}
			}
			else{
				if(filho->e == NULL){
					*raiz = filho->d;
				}
				else{
					*raiz = filho->e;
				}
			}
			free(filho);
		}
		else{	//tem dois filhos
			if(lado == 'd'){
				paisub = filho;
				sub = filho->d;
				while(sub->e!=NULL){
					paisub = sub;
					sub = sub -> e;
				}
				filho->info = sub ->info;
				if(sub == filho->d){
					paisub->d = sub->d;
				}
				else{
					paisub->e = sub->d;
				}
				free(sub);
			}
			else{
				paisub = filho;
				sub = filho->e;
				while(sub->d!=NULL){
					paisub = sub;
					sub = sub -> d;
				}
				filho->info = sub ->info;
				if(sub == filho->e){
					paisub-> e = sub->e;
				}
				else{
					paisub -> d = sub->e;
				}
				free(sub);
			}
		}
	}
}

void balanceamento(Arv* raiz)
{
	int qd, qe, fb, aux;
	ArvBin r = *raiz, *e, *pai;
	Fila *f;
	init(&f);
	enqueue(&f, *raiz);
	
	while(!isEmpty(f))
	{
		dequeue(&f, &r);
		do
		{
			qd = contaNo(r->dir);
			qe = contaNo(r->esq);
			fb = qd - qe;

			busca(r, r->info, &e, &pai);
			if(r->esq == NULL)
				r= r->dir;
			else
				if(r->dir == NULL)
					r = r->esq;
			if(fb > 0)
				exclusaoABBBalanceada(&*raiz, e, pai, 'd');
			else
				exclusaoABBBalanceada(&*raiz, e, pai, 'e');
			inserirI(&*r, aux);
		}while(abs(fb) > 1);
	
		if(r->esq != NULL)
			enqueue(&f, r->esq);
		if(r->dir != NULL)
			enqueue(&f, r->dir);
	}
}


int main(){
	Arv *raiz = NULL;
	return 0;
}
