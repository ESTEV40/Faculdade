#include <stdio.h>
#include <stdlib.h>

typedef struct{
    int numdr;
    int denomdr;
}racional;

void criar(racional *q, int a, int b){
    q->numdr = a;
    q->denomdr = b;
    reduzir(q);
    printf("\n%d/%d\n", numerador(*q), denominador(*q));
}
void reduzir(racional *q){
    int aux, a, b;
    a = q->numdr;
    b = q->denomdr;
    while(b > 0){
        aux = a%b;
        a=b;
        b=aux;
    }
    q->numdr/=a;
    q->denomdr/=a;
}
int numerador(racional q){
    return (q.numdr);
}
int denominador(racional q){
    return (q.denomdr);
}
