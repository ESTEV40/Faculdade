#include <stdio.h>
//BOUBLE SORT
int main(){

    int N, ind_min, aux, i, j;
    while(scanf("%d", &N) && N>0){// recebe Entradas enquanto N != 0
        int Vetor[N];
        
        for(i=0; i<N;i++) // recebe valores
            scanf("%d", &Vetor[i]);
        
        for(i=0; i<N-1; i++){
            ind_min=i;//index do numero a ser comparado a todos os outros;

            for(j = ind_min+1 ; j<N ; j++)
                if(Vetor[ind_min] > Vetor[j]){//busca o menor valor
                    ind_min=j;//se encontrar um valor menor, salva o index deste, novo valor a ser comparado;
                }

            printf("%d ", ind_min+1);//imprime na tela o index do valor antes do sort;
            //sort
            aux=Vetor[i];
            Vetor[i]=Vetor[ind_min];
            Vetor[ind_min]=aux;
        }
        printf("\n");
        //impressão pós bouble sort
        for(i=0; i<N;i++)
            printf("%d ", Vetor[i]);
        printf("\n");
    }
}
