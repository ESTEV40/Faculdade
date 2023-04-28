#include <stdio.h>
//Algoritmo de Busca em um Vetor;
int main(){
    int N=1, X, B;
    int i = 0;

    while (scanf("%d", &N) && N)
    {
        int V[N];
        for (i = 0; i < N; i++)
            scanf("%d", &V[i]);//recebe vetor
        scanf("%d", &B);// recebe buscas
        for(i=0;i<B;i++){// busca
            scanf("%d", &X);//recebe numero
            for (int j = 0; j < N; j++){
                if(V[j]==X){
                    printf("%d\n", j+1);
                    break;
                }else if (j==(N-1)){
                    printf("NAO\n");
                }
            }
        }
        printf("\n");
    }
    

}
