#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct proc{
  int timeProg, timeInit, procId, procSize;
  struct proc *prox, *ant;
  char type;
}proc;

typedef struct{
  proc *ini;
  int cont;
}header;

void initHeader(header *h){
  h->ini = NULL;
  h->cont = 0;
}

proc *initList(proc *l){
  return NULL;
}

void insList(header *h,proc *l, int time, int size){
  proc *p = (proc *) malloc(size);
  p->timeProg = time;
  p->timeInit = clock(); /* guarda o valor de quando o processo começou */
  p->type = 'p';
  p->procSize = size;
  h->cont++;
  p->procId = h->cont;
  if(l == NULL){
    p->prox = NULL;
    p->ant = NULL;
    l = p;
    h->ini = l;
  }
  else{
    p->ant = l;
    l->prox = p;
    p->prox = h->ini;
    l = p;
  }
}

void rmvList(header *h, int id){
  int i;
  proc *p;
  p = h->ini;
  i = 0;
  do{
    if(p->procId == id){
      p->type = 'h';
      h->cont--;
      if(p->prox != NULL && p->ant != NULL){
        p->prox->ant = p->ant;
        p->ant->prox = p->prox;
        p->prox = NULL;
        p->ant = NULL;
      }
      else if(p->prox == NULL && p->ant != NULL){
        p->ant->prox = NULL;
        p->ant = NULL;
      }
      else if(p->prox == NULL && p->ant == NULL){
        h->ini = NULL;
        p->prox = NULL;
        p->ant = NULL;
      }
      else{
        h->ini = p->prox;
        p->prox->ant = NULL;
      }
    }
    i++;
  }while(i < h->cont);
}


void clrList(header *h){
  proc *p, *temp;

  p = h->ini;
  do{
    temp = p->prox;
    free(p);
    p = temp;
  }while(p != NULL);
}

void printList(header *h){
  proc *p;

  p = h->ini;
  do{
    printf("Id: %d Tamanho: %d\n", p->procId, p->procSize);
    p = p->prox;
  }while(p != NULL);
}

int main(void){
  header *head;
  proc *process;

  process = (proc *) malloc (sizeof(proc));
  head = (header *) malloc (sizeof(header));

  initHeader(head);
  process = initList(process);
  insList(head, process, 10, 50);
  insList(head, process, 25, 70);
  printList(head);
  clrList(head);

  return 0;
}
