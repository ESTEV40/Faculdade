#include <stdio.h>

int main(){

    int Input, IsEven;//Entradas e Flag de condição

    scanf("%d", &Input);

    IsEven = parity(Input);

    if (IsEven) printf("It's Odd");
    else printf("It's Even");

    return 0;   
}

