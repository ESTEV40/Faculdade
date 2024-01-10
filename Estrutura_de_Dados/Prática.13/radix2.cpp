// Estevão
// Larissa
// Davi

#include <bits/stdc++.h>

using namespace std;

void exibeVector(vector<int> v){
    for(int x=0; x<v.size(); x++){
        cout << v[x] << " ";
    }
    cout << endl;
}

void CSort(vector<int> &A, int n, int exp){

    int B[n];
    int i, C[2] = { 0 };

    for (i = 0; i < n; i++)
        C[((A[i] / exp) % 2)]++;

    for (i = 1; i < 2; i++)
        C[i] += C[i - 1];

    for (i = n - 1; i >= 0; i--) {
        B[C[((A[i] / exp) % 2)]-1] = A[i];
        C[((A[i] / exp) % 2)]--;
    }

    A.clear();
    for (i = 0; i < n; i++)
        A.push_back(B[i]);
}


void radixsort(vector<int> &A, int m){
    for (int exp = 0; exp < m; exp++){
        CSort(A, A.size(), pow(2, exp));
        exibeVector(A);
    }
}

int main(){
    int d, qtd, num;
    vector<int> A;
    while(cin >> d >> qtd){
        while(qtd--){
            cin >> num;
            A.push_back(num);
        }

        radixsort(A, d);
        cout << endl << endl;
        A.clear();
    }
}