//CALCULADORA POS-FIXA

#include <iostream>
#include <string>
#include <stack>
#include <math.h>

using namespace std;
double calcula_posfix(double first, double second, string op); // desempilha dois valores e faz a próxima operação
double desempilha(stack<double> *pil);// desempilha e retorna valor desempilhado

int main (){
    int N;
    stack<double> pilha;
    double num, primeiro, segundo;
    string entrada;//Expressão inteira
    while ( cin >> N && N>0){
        for(int i=0; i<N; i++){
            cin >> entrada;
            if(entrada !="^" && entrada!="/" && entrada != "*" && entrada != "+" && entrada != "-"){//verifica o operador
                num = stod(entrada); //converte String para Double
                pilha.push(num);
            }
            else {
                segundo= desempilha(&pilha);
                primeiro= desempilha(&pilha);
                num = calcula_posfix(primeiro, segundo, entrada);
                pilha.push(num);
            }
        }
        printf("%.3lf\n", pilha.top());//ultimo valor a ser adicionado 
        cin >> N;
    }
    return 0;
}
double desempilha(stack<double> *pil){
    double num = pil->top();
    pil->pop();
    return num;
}
double calcula_posfix(double first, double second, string op){
    if (op == "^") 
        return pow( first, second);// função para potência
    else if ( op =="*") 
            return (first * second);
        else if(op == "/")
                return (first/second);
            else if(op == "+")
                    return (first+second);
                else
                    return (first-second);
}
