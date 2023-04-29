#include <iostream>
#include <stack>

using namespace std;
//implementação de classe fila
class Queue{
    //nó para a fila, se não tiver nó, será fila de filas
    class No{
        public : 
            int Num;
            No *next;
        No(){//inicializar o nó
            next = nullptr;
        }
        No(int i){//adiciona valor
            Num = i;
            next = nullptr;
        }
    };
    //ponteiros para o inicio e fim da fila
    private:
        //ponteiros para fila com valores >= 5000
        No *head_MA5000;
        No *tail_MA5000;
        //ponteiros para fila com valores <5000
        No *head_ME5000;
        No *tail_ME5000;
        
    public :
        Queue(){//construtor para inicializar os ponteiros 

            head_MA5000 = nullptr;
            tail_MA5000 = nullptr;

            head_ME5000 = nullptr;
            tail_ME5000 = nullptr;
        }
        void enfileirar(int num){
            No *novo = new No(num);//novo objeto
            if(num>=5000){
                if(tail_MA5000 != nullptr){//se a fila não tiver vazia
                    tail_MA5000->next = novo;// adiciona novo objeto a fila
                    tail_MA5000 = tail_MA5000->next;// fim da fila atualizado
                }else{
                    //se tiver vazia, head e tail apontam pro mesmo lugar
                    head_MA5000 = novo;
                    tail_MA5000 = head_MA5000;
                }
            }else {
                if(tail_ME5000 != nullptr){
                    tail_ME5000->next = novo;
                    tail_ME5000 = tail_ME5000->next;
                }else{
                    head_ME5000 = novo;
                    tail_ME5000 = head_ME5000;
                }
            }
        }
        void desenfileirar(stack<int> *fila_Excloi){
            No *Excloi;// ponteiro para exluir objeto

            if (head_ME5000 != nullptr){ //verifica se pilha vazia, para a primeira fila
                Excloi = head_ME5000;
                if(tail_ME5000==head_ME5000)//se só tiver um valor => tail = NULL
                    tail_ME5000=nullptr;//evita que tail seja excluído
                head_ME5000 = head_ME5000->next; //novo inicio
                fila_Excloi->push(Excloi->Num); // armazena valores que saíram da fila
                delete Excloi;

            }else if(head_MA5000 != nullptr){// para a segunda fila
                
                Excloi = head_MA5000;
                if(tail_MA5000==head_MA5000)
                    tail_MA5000=tail_MA5000->next;
                head_MA5000 = head_MA5000->next;
                fila_Excloi->push(Excloi->Num);
                delete Excloi;
                
            }
            
        }
        void imprime_desenfileirados(stack<int> *Pilha_print){
            while(!Pilha_print->empty()){//desenfilera enquanto pilha não estiver vazia
                cout << Pilha_print->top() << " ";
                Pilha_print->pop();
            }
        }
};
int main(){
    Queue *Fila = new Queue();
    stack<int> SAIDA;
    int N, ENTRADA;
    char op;
    while(cin >> N && N>0){
        for(int i=0; i<N; i++){
            cin >> op;
            switch (op)
            {
            case 'E': 
                    cin >> ENTRADA;
                    Fila->enfileirar(ENTRADA);
                break;
            case 'D' :
                    Fila->desenfileirar(&SAIDA);
                break;
            }
        }
        Fila->imprime_desenfileirados(&SAIDA);
        cout << "\n";
    }
    return 0;
}
