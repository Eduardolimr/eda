#include<stdio.h>
#include<stdlib.h>
#include<time.h>


typedef struct processo{
	int tempo;
	int id;
	int tam;
	struct processo *prox;
	struct processo *ant;

}processo;

processo *head;
processo *tail;

int size;
int idUtil;

int randomNumber(){
	srand(time(NULL));
	int randomnumber;
	randomnumber = rand() % 10 + 1;
	printf("rn %d\n", randomnumber);
	return randomnumber;
}

void listaInit(){
	processo *novo = (processo*) malloc (size);
	novo->tempo=0;
	novo->id=0;
	novo->tam=size;
	novo->prox=novo;
	novo->ant=novo;
	head=novo;
	tail=novo;
}

int checarValid(int tamanho){
	processo *aux;
	aux=head;
	int i=0;
	do{
		if(aux->id==0 && aux->tam>tamanho){
			i++;
		}	
	}while(aux!=tail);
	if(i>0){
		return 1;
	}
	else{
		return 0;
	}
}

void insertLista(int tamanho){
	int newSize;
	if(checarValid(tamanho)==1){
		processo *aux;
		processo *temp;
		aux=head;
		while(aux->id!=0 && aux->tam<tamanho){
			temp=aux;
			aux=aux->prox;
		}
		newSize=(aux->tam)-tamanho;
		aux = (processo*)realloc(aux,newSize);
		processo *novo = (processo*)malloc(tamanho);
		novo->id=idUtil;
		idUtil++;
		novo->tam=newSize;
		novo->tempo=randomNumber();
		novo->prox=temp->prox;
		novo->ant=aux->ant;
		temp->prox=novo;
		aux->ant=novo;
	}

}

void reArrange(){
	int total=0;
	processo *aux;
	processo *temp;
	aux=head;
	while(aux!=tail){
		if(aux->id==0){
			total+=aux->tam;
			temp=aux->ant;
			temp->prox=aux->prox;
			temp=aux->prox;
			temp->ant=aux->ant;
			free(aux);
			aux=temp;
		}
		aux=aux->prox;
	}
	processo *novo = (processo*)malloc(total);
	novo->tempo=0;
	novo->id=0;
	novo->prox=head;
	tail->prox=novo;
	tail=novo;
}

void printLista(){
	processo *aux;
	aux=head;
	do{
		printf("%d|%d->", aux->id, aux->tam);
		aux=aux->prox;
	}while(aux!=head);
	printf("\n");	
}

void clearLista(){
	processo *aux;
	processo *temp;
	aux=head;
	do{
		temp=aux->prox;
		free(aux);
		aux=temp;
	}while(aux!=head);	
}

int main(){
	head=NULL;
	tail=NULL;
	size=300;
	idUtil=1;
	int op;
	int tamanho;
	listaInit();
	printLista();
	do{
		printf("1 - Inserir\n2 - Iteracao(rearrange)\n0 - sair\n");
		scanf("%d",&op);
		switch(op){
			case 1:
				printf("\n");
				scanf("%d",&tamanho);
				insertLista(tamanho);
				break;
			case 2:
				reArrange();
				break;
			case 0:
				break;

		}
		printLista();
	}while(op!=0);
	clearLista();



	return 0;
}
