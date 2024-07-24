#include <stdlib.h>
#include <stdio.h>

char Complemento_2(char n){
    return ~n + 1;
}

int main(){

    char n = 10;

    printf("%d\n", Complemento_2(n));

    return 0;
}