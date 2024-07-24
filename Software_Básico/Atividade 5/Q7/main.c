#include <stdio.h>

void decodei(long *xp,long *yp,long *zp){
    long x = *xp;
    long y = *yp;
    long z = *zp;
    *yp = x;
    *zp = y;
    *xp = z;
}

int main(){
    return 0;
}