#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TAM 7
//Instruction set Architecture
typedef struct stack{
    int num;
    struct stack *prox;
}pilha;

pilha* IADD(pilha*); // retira dois elementos da pilha, soma e empilha o resultado
pilha* ISUB(pilha*); // retira dois elementos da pilha, subtrai e empilha o resulltado
pilha* IMUL(pilha*); // retira dois elementos da pilha, mutiplica e empilha o resultado
pilha* BIPUSH(pilha*, int); // Insere elemento na pilha
void libera(pilha*); // libera memoria da pilha
int POP(pilha**); // retira um elemento da pilha e o retorna

int main (){
    pilha *Topo;
    int N, num, i;
    char Control[TAM];
  
    while(scanf("%d", &N)==1  && N>0){ // Termina com o fim das entradas
      
        for(i=0;i<N;i++){
          
            scanf("%s", Control); // comando de controle, qual operação ele irá executar
            if(strcmp(Control, "BIPUSH")==0){
                printf("In:");
                scanf("%d", &num);
                Topo=BIPUSH(Topo, num);
                
            }else
            if(strcmp(Control, "IADD")==0)
                Topo=IADD(Topo);
            else
            if(strcmp(Control, "ISUB")==0)
                Topo=ISUB(Topo);
            else 
            if(strcmp(Control, "IMUL")==0)
                Topo= IMUL(Topo);
        }
        printf("Topo:%d\n", Topo->num);
        libera(Topo);
        Topo=NULL;
    }
    

    return 0;
}

pilha* IADD(pilha *A){
    int num1, num2;
    num1 = POP(&A);
    num2 = POP(&A);
    num1 = num1 + num2;
    return BIPUSH(A, num1);
}
pilha* ISUB(pilha *A){
    int num1, num2;
    num1 = POP(&A);
    num2 = POP(&A);
    num1= num1 - num2;
    return BIPUSH(A, num1);
}
pilha* IMUL(pilha *A){
    int NUM, num1, num2;
    num1 = POP(&A);
    num2 = POP(&A);
    NUM = num2 * num1;
    return BIPUSH(A, NUM);
}
int POP(pilha **A){
    //Verifica se pilha vazia
    if(A==NULL){
        printf("Pilha Vazia");
        exit(EXIT_FAILURE);
    }
    pilha *p=*A;
    int num=p->num;
    *A=p->prox;
    free(p);
    return num;
}
pilha* BIPUSH(pilha *A, int num){
    //aloca  memoria e insere novo valor
    pilha *novo;
    novo=malloc(sizeof(pilha));
    novo->num=num;
    novo->prox=A;
    return novo;
}
void libera(pilha* A){
    pilha *p=A;
    while(p!=NULL){
        A=A->prox;
        free(p);
        p=A;
    }
}
