#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

int uadd_OK(unsigned int x, unsigned int y) {
    return (UINT_MAX - y > x);
}

int main() {

    unsigned int x = 500;
    unsigned int y = 500;

    if(uadd_OK(x,y)) printf("Soma sem estouro");
    else printf("Causará estouro");

    return 0;
}
