#include<stdio.h>
#include<stdlib.h>
#define RED 1
#define BLACK 0

struct RubroNegra{
	int valor;
	char cor;
	struct RubroNegra *e,*d,*pai;
};
typedef RubroNegra No;

No* criaNo(int valor){
	No *novo = (No*) malloc(sizeof(No));
	novo-> valor = valor;
	novo->e=NULL;
	novo->d=NULL;
	novo->pai=NULL;
	novo->cor = RED;
	return novo;
}

void rotacaoDireita(No **raiz,No *no){
	No *noE = no->e;
	no-> e  =  noE-> d;
	
	if(no->e != NULL){
		no->e->pai = no;
	}
	
	noE->pai = no->pai;
	if(no->pai==NULL)
		(*raiz) = noE;
	else 
		if(no->pai->e == no){
			no->pai->e = noE;
		}
		else{
			no->pai->d = noE;
		}
	noE->d = no;
	no->pai = noE;	
}

void rotacaoEsquerda(No **raiz,No *no){
	No *noD = no->d;
	no-> d  =  noD-> e;
	
	if(no->d != NULL){
		no->d->pai = no;
	}
	
	noD->pai = no->pai;

	if(no->pai == NULL){
		(*raiz) = noD;
	}
	else 
		if(no->pai->e == no){
			no->pai->e = noD;
		}
		else{
			no->pai->d = noD;
		}
	noD->e = no;
	no->pai = noD;	
}

void corrigir(No **raiz,No *no){
	No *tio;
	No *pai=NULL;
	No *avo=NULL;
	
	while(no != *raiz && no->cor == RED && no->pai->cor==RED){
		pai = no->pai;
		avo = pai->pai;
		//Caso 1: O pai do novo no e filho esquerdo do avo
		if(pai == avo->e){
			tio = avo->d;
			//Caso 1.1: O tio e vermelho
			if(tio!=NULL  && tio->cor==RED){
				pai->cor = BLACK;
				tio->cor = BLACK;
				avo->cor = RED;
				no = avo;
			}
			else{
				//Caso 1.2: O tio e preto e o novo no e filho direito
				if(pai->d == no){
					rotacaoEsquerda(&(*raiz),pai);
					no = pai;
					pai = no->pai;
				}
				//Caso 1.3:O tio e preto e o novo no e filho esquerdo
				rotacaoDireita(&(*raiz),avo);
				avo->cor=RED;
				pai->cor=BLACK;
				no = pai;
			}
		}
		else{//Caso 2: O pai do novo no e filho direito do avo
			tio = avo->e;
			// Caso 2.1: O tio é vermelho
			if(tio!=NULL  && tio->cor==RED){
				pai->cor = BLACK;
				tio->cor = BLACK;
				avo->cor = RED;
				no = avo;
			}
			else{
				//Caso 2.2:O tio e preto e o novo no e filho esquerdo
				if(pai->e == no){
					rotacaoDireita(&(*raiz),pai);
					no = pai;
					pai = no->pai;
					
				}
				//Caso 2.3:O tio e preto e o novo no e filho direito
				rotacaoEsquerda(&(*raiz),avo);
				avo->cor=RED;
				pai->cor=BLACK;
				no = pai;
			}
		}
	}
	(*raiz)->cor = BLACK;
}

void inserir(No **raiz, int valor){
	No *noPai=NULL,*noAtual=*raiz;
	No *novo = criaNo(valor);
	while(noAtual!=NULL){
		noPai = noAtual;
		if(valor < noAtual->valor)
			noAtual = noAtual->e;
		else 
			noAtual = noAtual->d;
	}
	novo->pai = noPai;
	if(*raiz==NULL)
		*raiz = novo;
	else 
		if(valor < noPai->valor)
			noPai->e = novo;
		else 
			noPai->d =novo;
	corrigir(raiz,novo);
}

No* buscarMenor(No* no) {
    No* atual = no;

    while (atual && atual->e)
        atual = atual->e;

    return atual;
}

No* sucessor(No* no) {
    if (no->d)
        return buscarMenor(no->d);

    No* pai = no->pai;
    while (pai && no == pai->d) {
        no = pai;
        pai = pai->pai;
    }

    return pai;
}

void transplantar(No** raiz, No* antigoNo, No* novoNo) {
    if (antigoNo->pai == NULL) {
        *raiz = novoNo;
    } else if (antigoNo == antigoNo->pai->e) {
        antigoNo->pai->e = novoNo;
    } else {
        antigoNo->pai->d = novoNo;
    }

    if (novoNo != NULL) {
        novoNo->pai = antigoNo->pai;
    }
}

void corrigirExclusao(No** raiz, No* no) {
    No* irmao;

    while (no != *raiz && no->cor == BLACK) {
        if (no == no->pai->e) {
            irmao = no->pai->d;

            if (irmao->cor == RED) {
                irmao->cor = BLACK;
                no->pai->cor = RED;
                rotacaoEsquerda(raiz, no->pai);
                irmao = no->pai->d;
            }

            if ((!irmao->e || irmao->e->cor == BLACK) && (!irmao->d || irmao->d->cor == BLACK)) {
                irmao->cor = RED;
                no = no->pai;
            } else {
                if (!irmao->d || irmao->d->cor == BLACK) {
                    if (irmao->e)
                        irmao->e->cor = BLACK;

                    irmao->cor = RED;
                    rotacaoDireita(raiz, irmao);
                    irmao = no->pai->d;
                }

                irmao->cor = no->pai->cor;
                no->pai->cor = BLACK;
                if (irmao->d)
                    irmao->d->cor = BLACK;

                rotacaoEsquerda(raiz, no->pai);
                no = *raiz;
            }
        } else {
            irmao = no->pai->e;

            if (irmao->cor == RED) {
                irmao->cor = BLACK;
                no->pai->cor = RED;
                rotacaoDireita(raiz, no->pai);
                irmao = no->pai->e;
            }

            if ((!irmao->d || irmao->d->cor == BLACK) && (!irmao->e || irmao->e->cor == BLACK)) {
                irmao->cor = RED;
                no = no->pai;
            } else {
                if (!irmao->e || irmao->e->cor == BLACK) {
                    if (irmao->d)
                        irmao->d->cor = BLACK;

                    irmao->cor = RED;
                    rotacaoEsquerda(raiz, irmao);
                    irmao = no->pai->e;
                }

                irmao->cor = no->pai->cor;
                no->pai->cor = BLACK;
                if (irmao->e)
                    irmao->e->cor = BLACK;

                rotacaoDireita(raiz, no->pai);
                no = *raiz;
            }
        }
    }

    no->cor = BLACK;
}

void excluir(No** raiz, No* no) {
    No* substituto = no;
    No* filhoSubstituto = NULL;
    No* noFilho = NULL;

    bool corOriginalSubstituto = substituto->cor;

    if (no->e == NULL) {
        noFilho = no->d;
        transplantar(raiz, no, no->d);
    } else if (no->d == NULL) {
        noFilho = no->e;
        transplantar(raiz, no, no->e);
    } else {
        substituto = buscarMenor(no->d);
        corOriginalSubstituto = substituto->cor;
        noFilho = substituto->d;

        if (substituto->pai == no) {
            if (noFilho != NULL) {
                noFilho->pai = substituto;
            }
        } else {
            transplantar(raiz, substituto, substituto->d);
            substituto->d = no->d;
            substituto->d->pai = substituto;
        }

        transplantar(raiz, no, substituto);
        substituto->e = no->e;
        substituto->e->pai = substituto;
        substituto->cor = no->cor;
    }

    delete no;

    if (corOriginalSubstituto == BLACK) {
        corrigirExclusao(raiz, noFilho);
    }
}



void enqueue(No* node, No** queue, int* r) {
    queue[*r] = node;
    (*r)++;
}

No* dequeue(No** queue, int* front) {
    (*front)++;
    return queue[*front - 1];
}

void printRedBlackTree(No* raiz) {
    if (raiz == NULL)
        return;

    int front = 0;
    int r = 0;
    No* queue[100];  

    enqueue(raiz, queue, &r);

    printf("Red-Black Tree por nivel:\n");

    while (front < r) {
        No* atual = dequeue(queue, &front);

        printf("Data: %d, Cor: %s\n", atual->valor, atual->cor == RED ? "Red" : "Black");

        if (atual->e != NULL)
            enqueue(atual->e, queue, &r);
        if (atual->d != NULL)
            enqueue(atual->d, queue, &r);
    }
}

No* busca(No* raiz, int valor) {
    if (raiz == NULL || raiz->valor == valor) {
        return raiz;
    }

    if (valor < raiz->valor) {
        return busca(raiz->e, valor);
    } else {
        return busca(raiz->d, valor);
    }
}

int main(){
	No* raiz = NULL;
	inserir(&raiz,8);
	inserir(&raiz,4);
	inserir(&raiz,12);
	inserir(&raiz,2);
	inserir(&raiz,6);
	inserir(&raiz,10);
	inserir(&raiz,14);
	inserir(&raiz,1);
	inserir(&raiz,3);
	inserir(&raiz,5);
	inserir(&raiz,7);
	inserir(&raiz,9);
	inserir(&raiz,11);
	inserir(&raiz,13);
	inserir(&raiz,15);
	inserir(&raiz,16);
	printRedBlackTree(raiz);
	excluir(&raiz,busca(raiz,14));
	excluir(&raiz,busca(raiz,2));
	excluir(&raiz,busca(raiz,1));
	excluir(&raiz,busca(raiz,8));
	excluir(&raiz,busca(raiz,10));
	printRedBlackTree(raiz);
	return 0;
}



