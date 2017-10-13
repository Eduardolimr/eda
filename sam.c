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

void Iteracao(){
	int sum;
	processo *aux;
	processo *temp;
	processo *prev;
	aux=head;
	do{
		sum=0;
		if(aux->tempo>0){
			aux->tempo--;
		}
		if(aux->tempo==0){	
			aux->id=0;
		}
		aux=aux->prox;
	}while(aux!=head);
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
	int i=0;
	processo *aux;
	aux=head;
	do{
		if(aux->id==0 && aux->tam>=tamanho){
			i++;
		}
		aux=aux->prox;
	}while(aux!=head);
	if(i==0){
		return 0;
	}
	else{
		return 1;
	}
}

void insertLista(int tamanho){
	int newSize;
	processo *aux;
	processo *temp;
	processo *novo;
	if(head==tail){
		aux=head;
		newSize= (aux->tam)-tamanho;
		aux = (processo*)realloc(aux,newSize);
		aux->tam=newSize;
		novo = (processo*)malloc(tamanho);
		novo->id=idUtil;
		idUtil++;
		novo->tam=tamanho;
		novo->tempo=randomNumber();
		head->ant=novo;
		tail->prox=novo;
		novo->prox=head;
		novo->ant=tail;
		head=novo;
	}
	else if(checarValid(tamanho)==1){
		temp=tail;
		aux=head;
		while((aux->id)!=0 || (aux->tam)<tamanho){
			aux=aux->prox;
			temp=temp->prox;
		}
		newSize=(aux->tam)-tamanho;
		if(newSize!=0){
			aux = (processo*)realloc(aux, newSize);
			aux->tam=newSize;
			novo = (processo*)malloc(tamanho);
			novo->tam=tamanho;
			novo->id=idUtil;
			idUtil++;
			novo->tempo=randomNumber();
			temp->prox=novo;
			novo->ant=temp;
			novo->prox=aux;
			aux->ant=novo;
		}
		if(newSize==0){
			processo *aj;
			aj=aux->prox;
			free(aux);
			novo = (processo*)malloc(tamanho);
			novo->tam=tamanho;
			novo->id=idUtil;
			idUtil++;
			novo->tempo=randomNumber();
			temp->prox=novo;
			novo->ant=temp;
			novo->prox=aj;
			aj->ant=novo;
			if(novo->prox==head){
				tail=novo;
			}
		}
	}
}

int findHoleNo(){
	int No=0;
	processo *aux;
	aux=head;
	do{
		if(aux->id==0){
			No++;
		}
		aux=aux->prox;
	}while(aux!=head);
	return No;
}

void reArrange(){
	int tot,sum=0;
	tot = findHoleNo();	
	processo *aux;
	processo *temp;
	processo *next;
	aux=head;
	temp=tail;
	while(tot!=0){
		if(aux->id==0){
			next=aux->prox;
			temp->prox=next;
			next->ant=temp;
			sum+=aux->tam;
			if(head==aux){
				head=next;
			}
			else if(tail==aux){
				tail=temp;
			}
			free(aux);
			aux=next;
			tot--;
		}
		aux=aux->prox;
		temp=temp->prox;
	}
	processo *novo = (processo*)malloc(sum);
	novo->id=0;
	novo->tempo=0;
	novo->tam=sum;
	novo->ant=tail;
	tail->prox=novo;
	novo->prox=head;
	head->ant=novo;
	tail=novo;
}

void printLista(){
	processo *aux;
	aux=head;
	do{
		printf("|ID:%d|Time:%d|Size:%d|->", aux->id,aux->tempo, aux->tam);
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
		printf("1 - Inserir\n2 - Iteracao\n3 - Rearrange\n0 - Sair\n");
		scanf("%d",&op);
		switch(op){
			case 1:
				printf("\n");
				scanf("%d",&tamanho);
				insertLista(tamanho);
				break;
			case 2:
				Iteracao();
				break;
			case 3:
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
