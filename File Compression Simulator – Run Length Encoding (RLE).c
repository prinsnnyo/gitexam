#include <stdio.h>
#include <string.h>

int main() {
    char s[] = "aaaabbbccdaa", out[100]="";
    int i=0, j=0;
    while(s[i]) {
        int c=1; while(s[i]==s[i+1]) c++, i++;
        out[j++]=s[i]; sprintf(out+j,"%d",c); j+=strlen(out+j); i++;
    }
    printf("Compressed: %s\n", out);
    return 0;
}