//Conversor de expressão infixa para posfixa
#include <iostream>
#include <string>
#include <stack>

using namespace std;

bool ehOperador(char c){// verifica se é operador
    if ((c == '+' || c == '-' || c == '*' || c == '/'))
        return true;
    return false;
}

int precedencia(char c){// retorna o operador com maior prioridade
    if(c == '+' || c == '-'){
        return 1;
    }else if(c == '*' || c == '/'){
        return 2;
    }
    return 0;
}

string conversao(string Exp_in){
    stack<char> pilha;// expressão infixa de entrada
    string Exp_pos;// expressão pós-fixa de saída

    for(char c: Exp_in){//pega um caracterer da string de entrada, a cada iteração
        if(!ehOperador(c) && c != '(' && c != ')'){//parenteses não pode ser empilhado com os operandos
            Exp_pos.push_back(c);//função para inserir um caracter à string
        }else if(ehOperador(c)){ 
            while(!pilha.empty() && precedencia(pilha.top()) >= precedencia(c) && pilha.top() != '('){// verifica a precedencia > ou <
                Exp_pos.push_back(pilha.top());//insere
                pilha.pop();//retira
            }
            pilha.push(c);
        }else if(c == '('){//abriu parenteses
            pilha.push(c);
        }else if(c == ')'){//expressão de prioridade
            while(!pilha.empty() && pilha.top() != '('){//esvazia a pilha com todos os operadores até encontrar o parenteses inicial
                Exp_pos.push_back(pilha.top());
                pilha.pop();
            }
            pilha.pop(); // remove o '(' da pilha
        }
    }
    while(!pilha.empty()){ // insere os operadores restantes da pilha
        Exp_pos.push_back(pilha.top());
        pilha.pop();
    }
    return Exp_pos;
}

int main(){
    string Entrada, Saida;
    while(cin >> Entrada && Entrada != "Sair"){
        Saida = conversao(Entrada);
        cout << Saida << endl;
    }
    return 0;
}
