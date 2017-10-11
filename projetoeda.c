#include <stdio.h>
#include <stdlib.h>

typedef struct process{
  int timeProg, timeInit, id, size;
  struct process *prox, *ant;
  char type;
}process;

typedef struct{
  process *ini, *top;
  int cont, id;
}header;


 /* Procedimento de inicialização de cabeçalho */
void initHeader(header *h){
  h->ini = NULL;
  h->top = NULL;
  h->cont = 0;
  h->id = 0;
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
    h->id++; /* Incrementação da id */
    inicio->id = h->id;
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

/*procedimento de reordenacao dos buracos*/
void reOrganize(header *h){
  int sum=0;
  int i;
  process *p;
  process *temp;
  process *aux;
  i = 0;
  temp = h->ini;
  p=temp->prox;
  aux=p->prox;
  do{
    if(p->id=='h'){
        sum += p->size;
	temp->prox=aux;
	aux->ant=temp;
	free(p);
	p=aux;
	aux=p->prox;
    }
    else{
      p = p->prox;
      i++;
    }
  }while(i < h->cont);
  process *novo = (process*)malloc(sum);
  novo->type='h';
  novo->timeProg=0;
  novo->timeInit=0;
  novo->size=sum;
  novo->ant=h->top;
  (h->top)->prox=novo;
  novo->prox=h->ini;
  (h->ini)->ant=novo;
  h->top=novo;
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
      h->id++;
      novo->id = h->id;

      h->top->prox = novo;
      novo->ant = h->top;
      novo->prox = h->ini;
      h->top = novo;
    }
    else{
      printf("Verificando se é possível reorganizar memória...\n");
      /* Caso possível, a reordenação dos buracos ocorerrá aqui */
      printf("Não há espaço na memória para o processo.\n");
    }
  }
  else{
    printf("Não há espaço na memória para o processo.\n");
  }
}

/* Função de busca de elemento por id */
process *idSearch(header *h, int id){
  process *p;
  int i;

  p = h->ini;
  do{
    if(p->id == id){
      return p;
    }
    i++;
    p = p->prox;
  }while(i < h->cont);
  return NULL;
}

/* Procedimento de remoção de elementos */
void removeList(header *h, int id){
  process *p;
  p = idSearch(h, id);
  if(p != NULL){
    if(p->type == 'h'){
      printf("Elemento já foi removido.\n");
    }
    else{
      p->type = 'h';
    }
  }
  else{
    printf("Não há elemento com esse id.\n");
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
  }while(i < h->cont-1);
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

void printaMenu(void){
  printf(">>>>>> Menu <<<<<<\n");
  printf("1 - Inserir elemento\n");
  printf("2 - Imprimir lista\n");
  printf("3 - Remove elemento\n");
  printf("0 - Sair\n");
}

int main(void){
  header *head;
  int size, tim, id, opt;

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

  do{
    printaMenu();
    scanf("%d", &opt);
    getchar();
    switch(opt){
      case 1:
        printf("Digite o espaço e tempo para o processo: \n");
        scanf("%d", &size);
        scanf("%d", &tim);
        insertList(head, tim, size);
        break;
      case 2:
        printList(head);
        break;
      case 3:
        printf("Digite a id do elemento a remover: \n");
        scanf("%d", &id);
        removeList(head, id);
        break;
      case 0:
        printf("Encerrando...\n");
    }
  }while(opt);

  clearList(head);
  return 0;
}
