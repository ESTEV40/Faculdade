#include <iostream>

using namespace std;

//Implementação de Lista duplamente encadeada ordenada

class list_ordenada{
    class no{// classe para cada elemento objeto da lista
        public :
            int valor;
            no *prox;
            no *ante;

            //construtor para entrada de valor
            no(int i) : valor(i), prox(nullptr), ante(nullptr) {}
    };
    private :
    //sinalizador de inicio
    no *head;

    public :
    //inicializar o ponteiro head
    list_ordenada(){
        head = nullptr;
    }

    void inserir_ordenado(int num){

        no *novo = new no(num);// Novo elemento para ser inserido
        no *nav = nullptr;// Ponteiro para navegar a lista
        no *auxiliar = nullptr; //Ponteiro para auxiliar a inserção do elemento
        int contagem = 0;// Conta quantos elementos ele pulou para ser inserido
        
        // verificar se lista está vazia
        //se não tiver elementos, numero novo é o inicio
        if(vazia()){ 
            head = novo;
            head->prox = nullptr;
            head->ante = nullptr;
        }else{
            nav = head; // navegação do inicio ao fim
            while(nav!=nullptr && novo->valor > nav->valor){ // enquanto não for NULL
                auxiliar = nav;// Armazena endereço do valor menor que o valor novo
                nav=nav->prox;// proximo valor
                contagem = contagem + 1; // incrementa local pulado
            }
            if(nav==head && auxiliar == nullptr){// verifica se irá inserir na frente

                novo->prox = head; //head é posterior a novo
                head->ante = novo;
                head = novo;// elemento novo é o novo head
                head->ante = nullptr; // não existe valor antes do head

            }else if(nav==nullptr){// verifica se irá inserir atrás
                
                novo->ante = auxiliar;//antes: auxiliar => ultimo elemento. agora: novo=> ultimo elemento
                auxiliar->prox= novo;
                novo->prox = nullptr;// ultimo->prox aponta pra nada

            }else{// se não insere entre elementos
               
                novo->prox = auxiliar->prox;// aponta o elemento próximo ao inserido
                novo->ante = auxiliar;// aponta o elemento a anterior ao inserido
                auxiliar->prox = novo;// elemento proximo aponta ao novo
                auxiliar->prox->ante = novo;// elemento anterior aponta ao novo

            }
        }
        cout << contagem << " "; // quantidade de pulos
    }
    bool vazia(){//  verifica vazia
        return (head==nullptr);
    }
    void imprime(){
        no *nav = head;
        cout << endl << "LISTA: ";
        while (nav != nullptr){// navega a lista e imprime cada elemento
            cout << nav->valor << " ";
            nav=nav->prox;
        }
        cout << endl;
        return ;
    }
    void limpalista(){
            no *Exlcuir;// ponteiro para apontar ao objeto a ser excluido
            while (!vazia()){
                Exlcuir = head;
                head= head->prox; // novo head
                delete Exlcuir;// exclui o objeto
            }
        }
};
int main(){

    list_ordenada *Lista = new list_ordenada(); // cria a lista
    int N;

    cout << "Tamanho da lista: ";
    cin >> N;
    while(N>0){
        cout << endl << "Entrada: ";
        int entrada[N];

        // Explicação:
        // Fiz com dois laços for;
        // para imprimir "jumps:" entre os dois
        // só pra deixar bonitinho :).
        // é possivel fazer, com um for, leitura e inserção;

        for(int i = 0; i<N ; i++) // laço para armazenar valores
            cin >> entrada[i];
        cout << "jumps: ";
        for(int i = 0; i<N ; i++)// laço para inserir valores
            Lista->inserir_ordenado(entrada[i]);

        Lista->imprime();
        Lista->limpalista();
        cout << "\n\n" << "Tamanho da lista: ";
        cin >> N;
    }
}
