#include<stdio.h>
#include<stdlib.h>

struct queue{
	int valor;
	struct queue *prox;
};
typedef struct queue queue;

struct descritor{
	queue *ini;
	queue *fim;
};
typedef struct descritor desc;

char isEmpty(desc *d){
	return d->ini == NULL;
}

void enqueue(desc *d,int valor){
	queue *novo,*aux;
	novo = (queue*) malloc(sizeof(queue));
	novo->prox = NULL;
	novo->valor = valor;
	if(d->ini == NULL){	
		d->ini = novo;
		d->fim = novo;
	}
	else{
		aux = d->fim;
		aux->prox = novo;
		d->fim = novo;	
	}
}

int front(desc *d){
	return d->ini->valor;
}

void dequeue(desc *d){
	queue *aux;
	aux = d->ini;
	d->ini = aux->prox;
	if(d->ini == NULL){
		d->fim = NULL;
	}
	free(aux);
}

int main(){
	desc* d = (desc*)malloc(sizeof(desc));
    d->ini = NULL;
    d->fim = NULL;
    
	enqueue(d,1);
	enqueue(d,2);
	enqueue(d,3);
	
	printf("%d\n", front(d));
	dequeue(d);
	printf("%d\n", front(d));
	enqueue(d,1);
	dequeue(d);
	dequeue(d);
	printf("%d\n", front(d));
	dequeue(d);
	
	if(isEmpty(d)){
		printf("Fila vazia!\n");
	}
	else{
		printf("Fila com elementos!\n");
	}	
	return 0;
}
