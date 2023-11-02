#include <bits/stdc++.h>

using namespace std;

int main (){
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int Nsol;
    vector<int> Noglo;
    vector<int> Quadro;
    int a;

    while(cin >> Nsol){
        for(int i = 0; i < Nsol; i++){
            cin >> a;
            Quadro.push_back(a);
        }
        for(int i = 0; i < Nsol; i++){
            cin >> a;
            Noglo.push_back(a);
        }

        sort(begin(Quadro), end(Quadro));
        sort(begin(Noglo), end(Noglo));

        int contBattles = 0;

        for(int i = Quadro.size()-1, j = Noglo.size()-1; i >= 0; i--){
            if(Noglo[j] > Quadro[i]){
                contBattles++;
                j--;
            }
        }

        cout << contBattles << endl;
    }

    return 0;
}