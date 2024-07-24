#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

int tadd_ok(int x, int y) {
    return (INT_MAX - x < y) || (INT_MIN - x > y);//Aproveitei e fiz para caso de undeflow :)
}

int main(){

    int x, y;
    //quaisquer valores;
    x = 500;
    y = 500;

    if(tadd_ok(x, y)) printf("Estouro\n");
    else printf("sem estouro\n");

    return 0;
}