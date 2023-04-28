#include <stdio.h>
#include <stdlib.h>
//Lista Ligada/encadeada
typedef struct no{
    int Num;
    struct no *next;
}Lista;

//Insere elemento da frente da Lista
Lista* Insere_frente(Lista *P, int Num){ //LAELE
  
    //A cada chamada é necessário alocar memória para adicionar um novo elemento
    Lista *novo = malloc(sizeof(Lista));
    novo->Num= Num;
    novo->next = P;
    return novo;
}
//Insere elemento no final da Lista
Lista* Insere_atras(Lista *P,int Num){ //LAELE
  
    Lista *novo;
    novo = malloc(sizeof(Lista));
    novo->Num= Num;
    novo->next = NULL;
    return novo;
}
void limpa_buffer(){
    scanf("%*[^\n]");
    scanf("%*c");
}

int main(){
    Lista *p, *head;
    int N=1, Num;
    char OP;
  
    while(scanf("%d", &N)==1 && N>0){
        head=NULL;
        limpa_buffer();
   
        for(int i=0; i<N; i++){      
            scanf("%c %d", &OP, &Num);
            limpa_buffer();
          
            if(OP=='P'){// verifica se insere na frente ou atrás (laele!)
                head=Insere_frente(head, Num);
            }else {
                p=head;
                while (p->next!=NULL) // percorre a lista até o final
                  p=p->next;
                p->next=Insere_atras(head,Num);
            }
        }
        //imprime na tela os valores enfileirados
        for(p=head; p!=NULL; p=p->next){
            printf("%d ", p->Num);
        }
    }
    return 0;
}
