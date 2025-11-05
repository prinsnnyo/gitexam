#include <stdio.h>
#include <string.h>

int binToDec(char *b) { int d=0; for(int i=0;b[i];i++) d=d*2+(b[i]-'0'); return d; }
void decToBin(int n) { for(int i=15;i>=0;i--) printf("%d",(n>>i)&1); }

int main() {
    char a[17], b[17]; int op;
    printf("1=+ 2=- 3=* : "); scanf("%d\n", &op); gets(a); gets(b);
    int x=binToDec(a), y=binToDec(b), r=(op==1)?x+y:(op==2)?x-y:x*y;
    printf("Bin: "); decToBin(r); printf("\nDec: %d\nHex: %X\n", r, r);
    return 0;
}