#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TAM 30

typedef struct elem{
  float valor;
  struct elem *prox;
}elem;

typedef struct{
  elem *top;
}stack;

elem *init(void){
  return NULL;
}

int tam(stack *s){
  elem *e;
  int i;

  i = 0;
  e = s->top;
  printf("---- Pilha no momento ----\n");
  while(e != NULL){
    i++;
    e = e->prox;
  }
  return i;
}

void push(stack *s, int v){
  elem *novo;

  novo = (elem *) malloc (sizeof(elem));
  novo->valor = v;
  if(s != NULL){
    novo->prox = s->top;
  }
  else{
    novo->prox = NULL;
  }
  s->top = novo;
}

int pop(stack *s){
  int v;
  elem *temp;

  temp = s->top;
  v = temp->valor;
  s->top = (s->top)->prox;
  free(temp);

  return v;
}

void print(stack *s){
  elem *e;

  e = s->top;
  printf("---- Pilha no momento ----\n");
  while(e != NULL){
    printf("%f\n", e->valor);
    e = e->prox;
  }
  printf("---- --------------- ----\n\n\n");
}

void clear(stack *s){
  elem *e, *temp;

  e = s->top;
  while(e != NULL){
    temp = e;
    e = e->prox;
    free(temp);
  }
}

void op(stack *s, char c){
  float res;
  if(tam(s) >= 2){
    switch(c){
      case '*':
        res = pop(s) * pop(s);
        break;
      case '/':
        res = pop(s) / pop(s);
        break;
      case '+':
        res = pop(s) + pop(s);
        break;
      case '-':
        res = pop(s) - pop(s);
      }
    push(s, res);
    print(s);
  }
  else{
    printf("Operação inválida!\n");
  }
}

int main(void){
  stack *s;
  char c;
  int flag;

  s = (stack *) malloc(sizeof(stack));

  s->top = init();

  printf("Pressione 'q' para sair. \n");
  do{
    c = getchar();
    if( c != '\n'){
        switch(c){
          case '0':
          case '1':
          case '2':
          case '3':
          case '4':
          case '5':
          case '6':
          case '7':
          case '8':
          case '9':
            push(s, c-'0');
            print(s);
            break;
          case '*':
          case '/':
          case '+':
          case '-':
            op(s, c);
      }
    }
  }while(c<'q');
  clear(s);
  return 0;
}
