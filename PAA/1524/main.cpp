#include <bits/stdc++.h>

using namespace std;

int main (){

    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int N, K;
    while(cin >> N && cin >> K){
        
        vector<int> fila_Dist; 
        vector<int> fila_ru;

        int x;

        fila_ru.push_back(0);
        fila_Dist.push_back(0);

        for(int i = 1; i < N; i++){
            cin >> x;
            fila_ru.push_back(x);

            fila_Dist.push_back(fila_ru[i] - fila_ru[i-1]);
        }

        sort(begin(fila_Dist), end(fila_Dist));

        int soma = 0;

        for(int i = 0; i <= N-K; i++)
            soma += fila_Dist[i];

        cout << soma << endl;
    }
    return 0;
}