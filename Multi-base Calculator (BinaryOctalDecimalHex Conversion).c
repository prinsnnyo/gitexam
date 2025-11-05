#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main() {
    char num[33], base[10]; printf("Number: "); gets(num); printf("Base: "); gets(base);
    int b = (!strcmp(base,"Binary")) ? 2 : (!strcmp(base,"Octal")) ? 8 : (!strcmp(base,"Hex")) ? 16 : 10;
    int d = strtol(num, NULL, b);
    printf("Dec: %d\nOct: %o\nBin: ", d, d);
    for(int i=31;i>=0;i--) printf("%d",(d>>i)&1); printf("\nHex: %X\n", d);
    return 0;
}