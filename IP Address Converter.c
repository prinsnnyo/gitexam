#include <stdio.h>
#include <string.h>
#include <stdlib.h>
int main() {
    char ip[40]; printf("IP: "); gets(ip);
    if (strchr(ip,'.')) {
        int a,b,c,d; sscanf(ip,"%d.%d.%d.%d",&a,&b,&c,&d);
        printf("Bin: %08b.%08b.%08b.%08b\nHex: %02X%02X%02X%02X\n",a,b,c,d,a,b,c,d);
    } else if (strlen(ip)==32) {
        for(int i=0;i<4;i++) {
            char s[9]; strncpy(s, ip+i*8, 8); s[8]='\0';
            printf("%d%s", strtol(s,NULL,2), i<3?".":"\n");
        }
    } else {
        for(int i=0;i<4;i++) {
            char s[3]; strncpy(s, ip+i*2, 2); s[2]='\0';
            printf("%d%s", strtol(s,NULL,16), i<3?".":"\n");
        }
    }
    return 0;
}