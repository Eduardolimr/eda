#include <stdio.h>
#include <stdlib.h>

#define MINSIZE 18

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
  h->cont = 0; /* Número de elementos */
  h->id = 0; /* Id dos elementos */
}

/* Procedimento de inicialização da lista */
void *initList(header *h, int size){
    process *inicio;
    inicio = (process *) malloc (size);
    /* Inicialização dos dos atributos do buraco */
    inicio->type = 'h'; /* tipo "buraco": 'h' */
    inicio->timeProg = 0;
    inicio->timeInit = 0;
    h->cont++;
    h->id++;
    inicio->id = h->id;
    inicio->size = size;
    /* Inserção no cabeçalho */
    h->ini = inicio;
    h->top = inicio;
    inicio->prox = inicio;
    inicio->ant = inicio;
}

/* Procura do primeiro buraco disponível */
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

/* Função para reorganizar buracos para alocar novo processo */
int reOrganize(header *h){
  process *p, *temp;
  int aux, size, success, i;

  p = h->ini;
  i = aux = size = success = 0;

  do{
    if(p->type == 'h' && aux != 0){
      /* Removendo buraco 'p' da lsita */
      p->ant->prox = p->prox;
      p->prox->ant = p->ant;
      /* Guardando seu tamanho antes de liberar */
      size+=p->size;
      free(p);
      /* Realocando buraco inicial */
      printf("Tamanho p: %d\n", size);
      printf("Tamanho temp: %d\n", temp->size);
      size = temp->size + size;
      printf("Tamanho a ser adicionado: %d\n", size);
      temp = realloc(temp, size);
      temp->size = size;
      printf("Tamanho temp: %d\n", temp->size);
      success++;
      h->cont--;
    }
    else if(p->type == 'h' && aux == 0){
      /* Procura do primeiro buraco na lista */
      temp = p;
      aux++;
    }
    p = p->prox;
    i++;
  }while(i < h->cont);
  /* Retornando flag 'sucess'; caso success == 1, foi feita realocação
                               caso success == 0, não foi feita realocação
  */
  return success;
}

/* Procedimento de inserção de elementos à lista*/
void insertList(header *h, int tim, int size, int passedTime){
  process *p, *novo;
  p = memoryFirstSearch(h);
  if(p != NULL){
    if((p->size - size) > 0){
      /* Realocação do tamanho do buraco encontrado */
      p = realloc(p, p->size - size);
      p->size = p->size - size;
      /* Alocação do novo elemento */
      novo = (process *) malloc(size);
      novo->timeProg = tim;
      novo->timeInit = passedTime;
      novo->size = size;
      novo->type = 'p'; /* Tipo "process": 'p' */

      h->cont++;
      h->id++;
      novo->id = h->id;

      /* A inserção nesse programa é sempre feita no primeiro
      espaço de memória disponível, não sendo no início nem no fim
      na maioria dos casos */
      if(h->ini != h->top){
        p->ant->prox = novo;
        p->ant = novo;
        novo->prox = p;
      }
      else{  /* Caso especial de primeira inserção */
        p->prox = novo;
        p->ant = novo;
        novo->prox = p;
        novo->ant = p;
        h->ini = novo;
        h->top = p;
      }
    }
    else{
      printf("Verificando se é possível reorganizar memória...\n");
      if(reOrganize(h)){ /* Alocação pôde ser feita */
        p = memoryFirstSearch(h);
        printf("Tamanho vsf: %d\n", p->size - size);
        if((p->size - size) > 0){
          /* Realocação do tamanho do buraco encontrado */
          p = realloc(p, p->size - size);
          p->size = p->size - size;
          /* Alocação do novo elemento */
          novo = (process *) malloc(size);
          novo->timeProg = tim;
          novo->size = size;
          novo->type = 'p';  /* Tipo "process": 'p' */

          h->cont++;
          h->id++;
          novo->id = h->id;

          p->ant->prox = novo;
          p->ant = novo;
          novo->prox = p;
        }
        else{
          printf("Foi feita realocação, mas o processo desejado ainda é grande demais para armazenar.\n");
        }
      }
      else{ /* Não pôde ser feita realocação */
        printf("Não há espaço para realocação de memória.\n");
      }
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
    printf("Não há processo com esse id. \n");
  }
}

/* Procedimento para checar a lista por processos que já expiraram */
void checkTime(header *h, int passedTime){
    process *p;
    int i, totalTime;

    p = h->ini;
    totalTime = passedTime - p->timeInit;
    do{
      /* Apenas remover caso seja do tipo processo('p') e tempo expirado */
      if((totalTime - p->timeProg) >= 0 && p->type == 'p'){
        p->type = 'h';
      }
      p = p->prox;
      i++;
    }while(i < h->cont);
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
void printList(header *h, int passedTime){
  int i, tim;
  process *p;

  i = 0;
  p = h->ini;
  do{
    tim = passedTime - p->timeInit;
    if(p->type == 'p'){
      printf("Tempo de execução: %d ", tim);
    }
    else{
      printf("Tempo de execução: N/A ");
    }
    printf("Id: %d Tamanho: %d Tipo: %c\n", p->id, p->size, p->type);
    p = p->prox;
    i++;
  }while(i < h->cont);
}

/*procedimento que grava em arquivo*/
void printFile(header *h, int passedTime){
  int i, tim;
  process *p;
  FILE *fp;
  FILE *head;
  fp = fopen("file.txt", "w");

  i = 0;
  p = h->ini;
  do{
    fprintf(fp, "%d %d %d ", p->timeInit, p->id, p->size);
    if(p->type=='p'){
	fprintf(fp,"%d ",1);
    }
    else if(p->type=='h'){
	fprintf(fp,"%d ",0);
    }
    p = p->prox;
    i++;
  }while(i < h->cont);
  fclose(fp);
  head = fopen("header.txt", "w");
  fprintf(head,"%d %d %d", h->id, h->cont, passedTime);
  fclose(head);
}

void readFile(header *h, int *passedTime){
	FILE *fp;
	FILE *head;
	int id,time,size, number, typeb;
	int i=1;
	/*head = fopen("head.txt", "r");
	fscanf(head,"%d", &number);
	*h->id=number;
	fscanf(head,"%d", &number);
	*h->cont=number;
	fscanf(head,"%d", &number);
	*passedTime=number;
	fclose(head);*/
	fp = fopen("file.txt", "r");
	while(fscanf(fp,"%d",&number)==1){
		switch(i){
			case 1:
				time=number;
				i++;
				break;
			case 2:
				id=number;
				i++;
				break;
			case 3:
				size=number;
				i++;
				break;
			case 4:
				typeb=number;
				i=1;
				printf("Time: %d ID: %d Size: %d Type: %d\n",time, id, size, typeb);
        insertList(h, time, size, *passedTime);
		}
	}
	fclose(fp);
}

/*Procedimento que printa o menu de opções para o usuário */
void printMenu(void){
  printf(">>>>>> Menu <<<<<<\n");
  printf("1 - Inserir elemento\n");
  printf("2 - Imprimir lista\n");
  printf("3 - Remove elemento\n");
  printf("4 - Escreve arquivo\n");
  printf("5 - Ler arquivo\n");
  printf("0 - Sair\n");
}

int main(void){
  header *head;
  int size, tim, id, opt;
  int passedTime;

  passedTime = 0;
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
    printMenu();
    scanf("%d", &opt);
    getchar();
    switch(opt){
      case 1:
        printf("Digite o espaço e tempo para o processo: \n");
        do{
          scanf("%d", &size);
          if(size < MINSIZE){
            printf("Tamanho muito pequeno! Digite um valor maior que 17 bytes.\n");
          }
        }while(size < MINSIZE);
        do{
          scanf("%d", &tim);
          if(tim < 0){
            printf("Tempo muito pequeno! Digite um valor maior que 0.\n");
          }
        }while(tim < 0);
        insertList(head, tim, size, passedTime);
        break;
      case 2:
        printList(head, passedTime);
        break;
      case 3:
        printf("Digite a id do elemento a remover: \n");
        scanf("%d", &id);
        removeList(head, id);
        break;
      case 4:
	      printFile(head,passedTime);
	      break;
      case 5:
	      readFile(head, &passedTime);
	      break;
      case 0:
        printf("Encerrando...\n");
    }
    printf("\n\nTempo passado desde o início do programa: %d\n\n", ++passedTime);
    if(opt){
      checkTime(head, passedTime);
    }
  }while(opt);

  clearList(head);
  return 0;
}
