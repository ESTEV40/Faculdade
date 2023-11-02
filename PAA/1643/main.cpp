#include <bits/stdc++.h>

using namespace std;

int main (){
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    vector<int> Fib = {1, 2};
    while(Fib.size() < 23){
        int a = Fib[Fib.size()-1] + Fib[Fib.size()-2];
        Fib.push_back(a);
    }

    int N;
    while(cin >> N){

        while (N--){
            
            int a, i, save;
            vector<int> vec;

            cin >> a;
            for(i = 0; i < Fib.size(); i++){
                if(Fib[i] <= a){
                    save = i;
                }
            }
                    
            vec.push_back(1);
            a = a - Fib[save];
           
            for(i = save-1; i >=0 ; i--){
                if(Fib[i] <= a){
                    vec.push_back(1);
                    a = a - Fib[i];
                }else vec.push_back(0);
            }

            vec.pop_back();
            int Bx = 0;
            for(int i = 0, j = save-1 ; i < vec.size(); i++, j--){
                Bx += vec[i] * Fib[j];
            }

            cout << Bx << endl;
        }
    }

    return 0;
}