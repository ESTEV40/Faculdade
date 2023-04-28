#include <stdio.h>
//Soma Cruzada
int main(){
    int N, i, j;
    while (scanf("%d", &N)==1){//Acaba com o fim das entradas

        int Vetor_1[N], Vetor_2[N];

        for(i=0; i < N; i++) //RECEBA 1
            scanf("%d", &Vetor_1[i]);

        for(i=0; i < N; i++) //RECEBA 2
            scanf("%d", &Vetor_2[i]);

        for( i=0 , j=(N-1) ; i<N ; i++ , j--)// Soma o ultimo com o primeiro, o segundo com penultimo...
            printf("%d ", Vetor_1[i]+Vetor_2[j]);
            
        printf("\n");
    }
}
