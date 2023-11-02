//Estêvão Sousa
//Davi Roriz
//Larissa de Brito

#include <iostream>

using namespace std;

void Max_Heapfy(int* A, int i, int N) {
    int esquerda = 2 * i;
    int direita = (2 * i) + 1;
    int MAX = i;
    int aux;

    if (esquerda <= N && A[esquerda - 1] > A[MAX - 1])
        MAX = esquerda;

    if (direita <= N && A[direita - 1] > A[MAX - 1])
        MAX = direita;

    if (MAX != i) {
        aux = A[i - 1];
        A[i - 1] = A[MAX - 1];
        A[MAX - 1] = aux;

        Max_Heapfy(A, MAX, N);
    }
}

void Build_MAX_Heap(int** A, int N) {
    for (int i = (N/2); i >= 1; i--)
        Max_Heapfy(*A, i, N);
}

int main() {
    int* entrada;
    int N;

    while (cin >> N && N > 0) {
        entrada = new int[N];

        for (int cont = 0; cont < N; cont++)
            cin >> entrada[cont];

        Build_MAX_Heap(&entrada, N);

        for (int cont = 0; cont < N; cont++)
            cout << entrada[cont] << " ";
        cout << endl;
        delete[] entrada;
    }

    return 0;
}
