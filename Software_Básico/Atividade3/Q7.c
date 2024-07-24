#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int strLonger (char *s, char* t);

int strLonger(char *s, char *t){
    int ls = strlen(s);
    int lt = strlen(t);
    
    return (ls - lt) > 0;
}

int main(){

    char *S, *T;
    //INTMAX para quais quer strings caberem aqui
    S = (char*) malloc(sizeof(char)* __INT_MAX__);
    T = (char*) malloc(sizeof(char)* __INT_MAX__);
    
    printf("Insert two strings:\n\n");

    printf("String 1:");

    scanf("%[^\n]s", S);
    scanf("%*c");

    printf("String 2:");
    scanf("%[^\n]s", T);
    scanf("%*c");

    printf("\n\nOutput: %d\n\n\t%d %d", strLonger(S, T), strlen(S), strlen(T));


    free(S);
    free(T);

    return 0;   
}