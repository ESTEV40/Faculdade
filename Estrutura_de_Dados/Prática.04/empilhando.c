
#include <stdio.h>
#include <stdlib.h>

typedef struct stack {
    int num;
    struct stack *prox;
}Pilha;

Pilha* empilhar(Pilha*,int);
Pilha* desempilhar(Pilha*);
Pilha* inicializar();
int verifica_void(Pilha *);
void imprime_pilha(Pilha*);

int main (){
    char OP;
    int N, In;
    Pilha *Topo;
  
    while(scanf("%d", &N)==1 && N>0){//Termina com o fim N <= 0
        Topo=inicializar();
      
        while(N--){
            scanf(" %c", &OP);
            switch (OP){//Verifica se Empilha ou desempilha
                case 'E': {
                    scanf("%d", &In);
                    Topo=empilhar(Topo, In);
                    imprime_pilha(Topo);
                }
                    break;
                
                case 'D': {
                    Topo= desempilhar(Topo);
                    imprime_pilha(Topo);
                }
                    break;
                }
          
        }
        free(Topo);
    }
    return 0;
}
Pilha* inicializar(){
    return NULL;
}

Pilha* empilhar(Pilha *topo, int num){
    Pilha *p;
    p=malloc(sizeof(Pilha)); //aloca memória
    p->num=num;
    p->prox=topo;
    return p;
}
Pilha* desempilhar(Pilha *topo){
    Pilha *p = topo;
    if(verifica_void(topo)){
        topo=topo->prox;
        free(p); // libera memoria
    }
    return topo;
}
int verifica_void(Pilha *p){
    if(p==NULL)
        return 0;
    return 1;
}
void imprime_pilha(Pilha *topo){
    Pilha *p=topo;
    if(verifica_void(topo)){
        while (p!=NULL){
            printf("%d ", p->num);
            p=p->prox;
        }
    }else printf("*");// Se a pilha estiver vazia imprime '*'
    printf("\n");
}
