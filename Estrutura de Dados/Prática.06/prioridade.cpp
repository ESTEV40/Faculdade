#include <iostream>

using namespace std;
//implementação de Fila de prioridade
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

            no *Excluir = inicio;// ponteiro para apontar ao objeto a ser excluido
            no *nav = inicio->prox; // ponteiro para navegar a fila
			no *nav_sombra = inicio; // auxiliar para salvar anterior
            no *salva_anterior = nullptr;// ponteiro para apontar o anterior do excluído

            if(inicio != nullptr){ // verifica se está vazio
                if(final == inicio){// se tiver só um elemento, final e inicio não pode serem exlcuídos
                    inicio = nullptr;
                    final = nullptr;
                }else {
					while(nav!=nullptr){
                        if(Excluir->valor < nav->valor){// prioridade de saída => o numero maior
                            salva_anterior = nav_sombra; // salva o endereço do numero anterior ao maior
                            Excluir = nav; // salva o endereço do numero maior
                        }
						nav_sombra=nav; // acompanha o anterior da navegação
						nav=nav->prox; //navega a fila 
                    }
				}
				//Verifica se o excluir está no inicio/meio/fim
				//evita falha de segmentação
                if(Excluir==inicio)
					inicio=inicio->prox;
				else if(Excluir==final)
                    	final = salva_anterior;
				else salva_anterior->prox=salva_anterior->prox->prox;// para nao perder parte da fila => fila reorganizada
				
				delete Excluir;// exclui o objeto com o maior valor
            }else return ;// se estiver vazio nao faz nada
        }
        bool vazia(){
            if(inicio == nullptr && final == nullptr)
                return true;
            return false;
        }
        void imprime(){
            if(vazia()){
                cout << "*" << endl; //Imprime "*" caso vazia
                return;
            }else{
                for (no *nav = inicio; nav != final->prox; nav=nav->prox){ //cria ponteiro para navegar a fila
                    cout << nav->valor << " "; // imprime valores da fila
                }
                cout << "\n";
            }
        }
        void limpafila(){
            while (!vazia()){
                no *Exlcuir = inicio;// ponteiro para apontar ao objeto a ser excluido
                
                if(inicio != nullptr){ // verifica se está vazio
                    if(final == inicio){// se tiver só um elemento, e final == inicio, final não pode ser exlcuido
                        final = nullptr;// final = NULL
                        inicio = nullptr;
                    }else inicio= inicio->prox; // novo inicio

                    delete Exlcuir;// exclui o objeto
                }else return ;// se estiver vazio nao faz nada
            }
        }
};

int main(){

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
        Fila->limpafila();
        cout << "Interações:";
        cin >> N;
    }
}
