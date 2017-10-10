#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

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

proc *initList(void){
  return NULL;
}

proc *insList(header *h,proc *l, int t, int size){
  proc *p = (proc *) malloc(size);
  p->timeProg = t;
  p->timeInit = clock(); /* guarda o valor de quando o processo começou */
  p->type = 'p'; /* tipo de lista: 'p' = 'process' */
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
  }
  return l;
}

void rmvList(header *h, int id){
  int i;
  proc *p;
  p = h->ini;
  i = 0;
  do{
    if(p->procId == id){
      p->type = 'h'; /* tipo de lista: 'h' = 'hole' */
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
  int i;
  proc *p, *temp;

  i = 0;
  p = h->ini;
  do{
    temp = p->prox;
    free(p);
    p = temp;
    i++;
  }while(i < h->cont);
}

void checaTempo(header *h,int id, proc *p){
  int clk;
  clk = (clock() - p->timeInit)/CLOCKS_PER_SEC;
  if(clk >= p->timeProg){
    rmvList(h,id);
  }
  else{
    printf("Tempo de processo de id %d: %d\n", p->procId, clk);
  }
}

void printList(header *h){
  int i;
  proc *p;

  i = 0;
  p = h->ini;
  do{
    printf("Id: %d Tamanho: %d\n", p->procId, p->procSize);
    checaTempo(h, p->procId, p);
    p = p->prox;
    i++;
  }while(i < h->cont);
}


int main(void){
  header *headProc;
  proc *process;

  process = (proc *) malloc (sizeof(proc));
  headProc = (header *) malloc (sizeof(header));

  initHeader(headProc);
  process = initList();

  process = insList(headProc, process, 1, 50);
  process = insList(headProc, process, 2, 70);

  printList(headProc);

  clrList(headProc);

  return 0;
}
