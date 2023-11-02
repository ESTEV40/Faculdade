#include <bits/stdc++.h>
#define TAMMAP 5
#define Verificado -1

using namespace std;

bool veref_limits(int i, int j){
    return (i >=0 && j>=0 && i <= 4 && j <=4);
}

bool backtrack_game(int map[TAMMAP][TAMMAP], int i, int j){
    if(i == 4 && j == 4){
        return true;
    }

    if(veref_limits(i, j) && map[i][j] == 0) {
        map[i][j] = Verificado;

        if(backtrack_game(map, i, j+1)){
            return true;
        }
        if(backtrack_game(map,i+1, j)){
            return true;
        }
        if(backtrack_game(map, i, j-1)){
            return true;
        }
        if(backtrack_game(map, i-1, j)){
            return true;
        }else return false;
    }else return false;

}

int main(){

    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int Map[TAMMAP][TAMMAP];
    int N;

    while(cin >> N){
        while(N--){

            for(int i = 0; i < TAMMAP; i++){
                for(int j = 0; j < TAMMAP; j++)
                    cin >> Map[i][j];
            }
            if(backtrack_game(Map, 0, 0)){
                cout << "COPS" << endl;
            }else cout << "ROBBERS" << endl;
            
        }

    }

    return 0;
}