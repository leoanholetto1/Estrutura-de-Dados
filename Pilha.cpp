#include<stdio.h>
#include<stdlib.h>

struct Pilha{
	int valor;
	struct Pilha *prox;
};
typedef struct Pilha Pilha;

//Pior tempo:O(1)  
//Melhor Tempo: O(1)
void pop(Pilha **P){ 
	Pilha *aux = *P;
	*P=(*P)->prox;
	free(aux);
}

//Pior tempo:O(1)  
//Melhor Tempo: O(1)
void push(Pilha **P,int valor){
	Pilha *novo = (Pilha*) malloc(sizeof(Pilha));
	novo->valor = valor;
	novo->prox = *P;
	*P = novo;
}

//Pior tempo:O(1)  
//Melhor Tempo: O(1)
int top(Pilha *P){
	return P->valor;
}

//Pior tempo:O(1)  
//Melhor Tempo: O(1)
char empty(Pilha *P){
	return P==NULL;	
}

int main(){
	Pilha *P=NULL;
	push(&P,10);
	push(&P,20);
	push(&P,30);
	printf("%d\n",top(P));
	pop(&P);
	printf("%d\n",top(P));
	pop(&P);
	printf("%d\n",top(P));
	pop(&P);
	if(empty(P)){
		printf("Pilha vazia\n");
	}
	else{
		printf("Pilha com elementos!\n");
	}
	return 0;
}
