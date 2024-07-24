#include <stdio.h>

int comp (long a, long b){
    return (a < b);
}

long function(long input){
    long result = input;

    while (result > 0) {
        result -= 1;
    }

    return result;
}

long absdiff(long x, long y){
    long result;
    if (x < y)
        result = y - x;
    else
        result = x - y;
    return result;
}

int main(){

    return 0;
}
