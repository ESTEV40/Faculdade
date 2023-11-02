#include <bits/stdc++.h>

using namespace std;

int main(void){ 
    int m, n, qtd, maiorDaLinha, maiorDaColuna, aux, pdVertical[2], pdLinha[2];

    while(cin >> m >> n && n!=0 && m!=0){
        for(int i=0; i<m; i++){
            for(int j=0; j<n; j++){
                cin >> qtd;
                if(j==0)  pdLinha[0]  = qtd;
                else if(j==1){
                    if(qtd>pdLinha[0]) pdLinha[1] = qtd;
                    else pdLinha[1] = pdLinha[0];
                } else {
                    aux = pdLinha[1];
                    if(aux>pdLinha[0]+qtd) pdLinha[1] = aux;
                    else pdLinha[1] = pdLinha[0]+qtd;
                    pdLinha[0] = aux;
                }
            }
                
            if(i==0)  pdVertical[0]  = pdLinha[1];
            else if(i==1){
                if(pdLinha[1]>pdVertical[0]) pdVertical[1] = pdLinha[1];
                else pdVertical[1] = pdVertical[0];
            } else {
                aux = pdVertical[1];
                if(aux>pdVertical[0]+pdLinha[1]) pdVertical[1] = aux;
                else pdVertical[1] = pdVertical[0]+pdLinha[1];
                pdVertical[0] = aux;
            }
        }
        cout << pdVertical[1] << endl;
    }
    return 0;
}