#include <stdio.h>
#include <stdlib.h>

typedef struct process{
  int timeProg, timeInit, id, size;
  struct process *prox, *ant;
  char type;
}process;

typedef struct{
  process *ini, *top;
  int cont;
}header;

 /* Procedimento de inicialização de cabeçalho */
void initHeader(header *h){
  h->ini = NULL;
  h->top = NULL;
  h->cont = 0;
}

/* Procedimento de inicialização da lista */
void *initList(header *h, int size){
    process *inicio;
    inicio = (process *) malloc (size);
    /* Inicialização dos dos atributos do buraco */
    inicio->type = 'h'; /* tipo buraco: 'h' */
    inicio->timeProg = 0;
    inicio->timeInit = 0;
    h->cont++; /* Incrementação do número de
    elementos */
    inicio->id = h->cont;
    inicio->size = size;
    inicio->prox = inicio;
    inicio->ant = inicio;
    /* Inserção no cabeçalho */
    h->ini = inicio;
    h->top = inicio;
}

process *memoryFirstSearch(header *h){
  process *p;
  int i;

  p = h->ini;
  i = 0;

  do{
    if(p->type == 'h'){
      return p; /* Buraco encontrado */
    }
    p = p->prox;
    i++;
  }while(i < h->cont);

  return NULL; /* Falha ao achar buraco na
  memória */
}

/* Procedimento de inserção de elementos à lista*/
void insertList(header *h, int tim, int size){
  process *p, *novo;
  p = memoryFirstSearch(h);
  if(p != NULL){
    if((p->size - size) > 0){
      /* Realocação do tamanho do buraco encontrado */
      p = (process *) realloc(p, p->size - size);
      p->size = p->size - size;
      /* Alocação do novo elemento */
      novo = (process *) malloc(size);
      novo->timeProg = tim;
      novo->timeInit = 0;
      novo->size = size;
      novo->type = 'p'; /* Tipo 'p': process */

      h->cont++;
      novo->id = h->cont;

      h->top->prox = novo;
      novo->ant = h->top;
      novo->prox = h->ini;
      h->top = novo;
    }
    else{
      printf("Não há espaço na memória para o processo.\n");
    }
  }
  else{
    printf("Não há espaço na memória para o processo.");
  }
}

/* Procedimento para liberar ponteiros ao final do programa */
void clearList(header *h){
  int i;
  process *p, *temp;

  i = 0;
  p = h->ini;
  do{
    temp = p->prox;
    free(p);
    p = temp;
    i++;
  }while(i < h->cont);
}

/* Procedimento para imprimir os elementos da lista */
void printList(header *h){
  int i;
  process *p;

  i = 0;
  p = h->ini;
  do{
    printf("Id: %d Tamanho: %d Tipo: %c\n", p->id, p->size, p->type);
    p = p->prox;
    i++;
  }while(i < h->cont);
}

int main(void){
  header *head;
  int size;

  head = (header *) malloc (sizeof(header));

  printf("Digite o espaço na memória destinado para os processos: \n");
  do{
    scanf("%d", &size);
    if(size < 0){
      printf("Por favor, digite um valor positivo. \n");
    }
  }while(size < 0);

  initHeader(head);
  initList(head, size);

  /* Testes de funcionamento provisórios */
  insertList(head, 10, 30);
  insertList(head, 10, 20);

  printList(head);
  clearList(head);
  return 0;
}
