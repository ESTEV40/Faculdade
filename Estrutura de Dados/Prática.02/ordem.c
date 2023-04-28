//Estêvão Sousa - 202210345
//Larissa de Brito - 202210349
//Davi Roriz - 202210342
#include <stdio.h>

int main(){

    int N, ind_min, aux, i, j;
    while(scanf("%d", &N) && N){
        int Vetor[N];
        
        for(i=0; i<N;i++)
            scanf("%d", &Vetor[i]);
        
        for(i=0; i<N-1; i++){
            ind_min=i;

            for(j = ind_min+1 ; j<N ; j++)
                if(Vetor[ind_min] > Vetor[j]){
                    ind_min=j;
                }

            printf("%d ", ind_min+1);
            aux=Vetor[i];
            Vetor[i]=Vetor[ind_min];
            Vetor[ind_min]=aux;
        }
        printf("\n");
        for(i=0; i<N;i++)
            printf("%d ", Vetor[i]);
        printf("\n");
    }
}