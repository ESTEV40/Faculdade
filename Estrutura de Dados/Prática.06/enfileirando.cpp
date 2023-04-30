#include <iostream>

using namespace std;
//implementação de Fila
class Queue{
    class no{ // Objeto para criar cada elemento da fila 
        public :
            int valor;
            no *prox;

            // construtores com ou sem valor;
            no(){
                prox = nullptr;
            }
            no(int V){
                valor = V;
                prox= nullptr;
            }
    };
    private : 
        // ponteiros de indicação de inicio e final da fila
        no *inicio;
        no *final;

    public :
        //construtor para iniciar a fila
        Queue(){
            inicio = nullptr;
            final = nullptr;
        }
        
    public :

        void enfileirar(int valor){
            no *novo = new no(valor);// cria objeto
            if(inicio != nullptr){ // caso fila não vazia
                final->prox = novo;// enfileira no fim da fila
                final= final->prox;// novo final
            }else{//caso fila vazia
                inicio = novo;
                final = inicio;// inicio e fim são iguais para fila com um elemento
            }
        }
        void desenfileirar(){
            no *Exlcuir = inicio;// ponteiro para apontar ao objeto a ser excluido

            if(inicio != nullptr){ // verifica se está vazio
            
                if(final == inicio){// se tiver só um elemento, e final == inicio, final não pode ser exlcuido
                    final = nullptr;// final = NULL
                    inicio = nullptr;
                }else inicio= inicio->prox; // novo inicio

                delete Exlcuir;// exclui o objeto
            }else return ;// se estiver vazio nao faz nada
        }
        void imprime(){
            if(inicio == nullptr && final == nullptr){ //verifica fila vazia
                cout << "*" << endl; //Imprime "*" caso vazia
                return;
            }else {
                for (no *nav = inicio; nav != final->prox; nav=nav->prox){ //cria ponteiro para navegar a fila
                    cout << nav->valor << " "; // imprime valores da fila
                }
                cout << "\n";
            }
        }
};

int main (){ 

    Queue *Fila = new Queue();
    int N, In;
    char Operador;

    cout << "Interações:";
    cin >> N;

    while (N>0){ // Fim das entradas Quando N=0
        for(int i=0; i<N; i++){// LOOP DE N OPERAÇÕES
        
            cout << "Enfileirar/Desenfileirar?: ";
            cin >> Operador;

            if(Operador ==  'E'){

                cin >> In;
                Fila->enfileirar(In);
                cout << "Fila:";
                Fila->imprime();
                cout << "\n\n";

            }else if(Operador == 'D'){

                Fila->desenfileirar();
                cout << "Fila:";
                Fila->imprime();
                cout << "\n\n";

            }
        }
        cout << "Interações:";
        cin >> N;
    }
}
