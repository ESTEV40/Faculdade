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

    // Output array
    int B[n];
    int i, C[10] = { 0 };

    // Store C of occurrences
    // in C[]
    for (i = 0; i < n; i++)
        C[(A[i] / exp) % 10]++;

    // Change C[i] so that C[i]
    // now contains actual position
    // of this digit in B[]
    for (i = 1; i < 10; i++)
        C[i] += C[i - 1];

    // Build the B array
    for (i = n - 1; i >= 0; i--) {
        B[C[(A[i] / exp) % 10] - 1] = A[i];
        C[(A[i] / exp) % 10]--;
    }

    // Copy the B array to A[],
    // so that A[] now contains sorted
    // numbers according to current digit
    A.clear();
    for (i = 0; i < n; i++)
        A.push_back(B[i]);
}


void radixsort(vector<int> &A, int m){
    for (int exp = 0; exp < m; exp++){
        CSort(A, A.size(), pow(10, exp));
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