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

// Função auxiliar para enfileirar um nó
void enqueue(No* node, No** queue, int* rear) {
    queue[*rear] = node;
    (*rear)++;
}

// Função auxiliar para desenfileirar um nó
No* dequeue(No** queue, int* front) {
    (*front)++;
    return queue[*front - 1];
}

// Função para exibir a Red-Black Tree por níveis
void printRedBlackTree(No* root) {
    if (root == NULL)
        return;

    // Inicialização da fila
    int front = 0;
    int rear = 0;
    No* queue[100];  // Tamanho máximo da fila (pode ser ajustado conforme necessário)

    // Enfileirar o nó raiz
    enqueue(root, queue, &rear);

    printf("Red-Black Tree por níveis:\n");

    // Percorrer a árvore por níveis
    while (front < rear) {
        No* current = dequeue(queue, &front);

        // Imprimir o nó atual
        printf("Data: %d, Color: %s\n", current->valor, current->cor == RED ? "Red" : "Black");

        // Enfileirar os filhos do nó atual, se existirem
        if (current->e != NULL)
            enqueue(current->e, queue, &rear);
        if (current->d != NULL)
            enqueue(current->d, queue, &rear);
    }
}

int main(){
	No* raiz = NULL;
	/*inserir(&raiz,8);
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
	inserir(&raiz,16);*/
	printRedBlackTree(raiz);
	return 0;
}



