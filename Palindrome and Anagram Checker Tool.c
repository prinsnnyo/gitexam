#include <stdio.h>
#include <string.h>
#include <ctype.h>
void clean(char *s) { int j=0; for(int i=0;s[i];i++) if(isalpha(s[i])) s[j++]=tolower(s[i]); s[j]='\0'; }
int main() {
    char a[100], b[100]; printf("1=Pal, 2=Ana: "); int c; scanf("%d\n", &c);
    gets(a); if (c==1) { clean(a); int l=strlen(a), f=1; for(int i=0;i<l/2;i++) if(a[i]!=a[l-1-i]) f=0;
        printf(f?"Palindrome\n":"Not Palindrome\n");
    } else { gets(b); clean(a); clean(b); int ca[26]={0}, cb[26]={0};
        for(int i=0;a[i];i++) ca[a[i]-'a']++; for(int i=0;b[i];i++) cb[b[i]-'a']++;
        int f=1; for(int i=0;i<26;i++) if(ca[i]!=cb[i]) f=0;
        printf(f?"Anagrams\n":"Not Anagrams\n");
    }
    return 0;
}