#include<stdio.h>
#include<stdlib.h>

struct PriorityQueue{
	int valor;
	struct PriorityQueue *prox;
};
typedef struct PriorityQueue priorityQueue;

char isEmpty(priorityQueue *PQ){
	return PQ==NULL;
}

void enqueue(priorityQueue **PQ,int valor){
	priorityQueue *novo,*aux,*ant;
	novo = (priorityQueue*) malloc(sizeof(priorityQueue));
	novo->prox = NULL;
	novo->valor = valor;
	if(*PQ==NULL){
		*PQ = novo;
	}	
	else{
		if(valor < (*PQ)->valor){
			novo->prox = *PQ;
			*PQ = novo;
		}
		else{
			ant = *PQ;
			aux= ant->prox;
			while(aux!=NULL && valor>=aux->valor){
				ant = aux;
				aux = aux->prox;
			}
			ant->prox = novo;
			novo->prox = aux;
		}
	}
}

int front(priorityQueue *PQ){
	return PQ->valor;
}

void dequeue(priorityQueue **PQ){
	priorityQueue *aux;
	aux = *PQ;
	*PQ = (*PQ)->prox;
	free(aux);
}

int main(){
    priorityQueue *PQ = NULL;

    enqueue(&PQ, 5);
    enqueue(&PQ, 2);
    enqueue(&PQ, 8);
	enqueue(&PQ, 3);
	
    printf("Front: %d\n", front(PQ));

    dequeue(&PQ);

    printf("Front after dequeue: %d\n", front(PQ));

    return 0;
}
