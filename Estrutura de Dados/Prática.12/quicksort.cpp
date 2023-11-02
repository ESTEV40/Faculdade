//Estêvão Sousa
//Davi Roriz
//Larissa de Brito

#include <iostream>

using namespace std;

int Particione(int *&Vetor, int P, int Max){
    int PIVONES = Vetor[Max];
    int i = P-1;
    int aux;
    for(int cont = P; cont <= Max-1; cont++){
        if(Vetor[cont] <= PIVONES){
            i++;

            aux = Vetor[i];
            Vetor[i] = Vetor[cont];
            Vetor[cont] = aux;

        }
    }

    aux = Vetor[Max];
    Vetor[Max] = Vetor[i+1];
    Vetor[i+1] = aux;

    cout << PIVONES << " ";

    return i+1;
}

void QuickSort(int *&Vetor,int P, int TAM){
    if(P < TAM){
        int Q = Particione(Vetor, P, TAM); 
        QuickSort(Vetor, P, Q-1);
        QuickSort(Vetor, Q + 1, TAM);
    }
}

int main(void){
    
    int N, *Array;

    while(cin >> N && N > 0){
        Array = new int[N];

        for(int i =0; i<N; i++){
            cin >> Array[i];
        }

        QuickSort(Array, 0, N-1);
        cout << endl;

        delete[] Array;
    }

    return 0;
}