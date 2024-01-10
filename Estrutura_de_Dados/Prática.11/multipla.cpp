//Estêvão Sousa
//Davi Roriz
//Larissa de Brito

#include <iostream>
#include <vector>


using namespace std;

class NoArvore {
public:

    vector<int> chaves;
    vector<NoArvore*> filhos;

    NoArvore(int SIZE) : filhos(SIZE, nullptr){}
    

    void inserirRecursivo(NoArvore*& no ,int chave,int Max) {
        
        if(no == nullptr){
            no = new NoArvore(Max);
        }
        if(no->chaves.empty()){
            no->chaves.push_back(chave);
            
            return;
        }

        for(int i = 0; i < no->chaves.size(); i++){   
            if(chave < no->chaves[i]){
                inserirRecursivo(no->filhos[i], chave, Max);
                return;
            }
        }
        if(no->chaves.size() != Max){
            no->chaves.push_back(chave);
        }else inserirRecursivo(no->filhos[Max-1], chave, Max);
    }

    int calcularAltura(NoArvore* no) {
        if (no == nullptr) {
            return -1;
        } else {

            int alturaMaxima = -1;

            for (NoArvore* filho : no->filhos) {

                int altura = calcularAltura(filho);
                if (altura > alturaMaxima) alturaMaxima = altura;

            }

            return 1 + alturaMaxima;
        }
    }
};


int main() {

    NoArvore *Tree = nullptr;
    int Interacoes, Ordem, entradas;

    while(cin >> Ordem >> Interacoes && Interacoes > 0){
        Tree = new NoArvore(Ordem);
        for(int i = 0; i < Interacoes; i++){
            cin >> entradas;
            Tree->inserirRecursivo(Tree, entradas, Ordem);
        }
        cout << Tree->calcularAltura(Tree) << endl;
    }
    

    return 0;
}