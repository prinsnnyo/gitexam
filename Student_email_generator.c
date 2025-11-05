#include <stdio.h>
#include <string.h>
#include <ctype.h>

int main() {
    char name[100], id[20], email[150];
    printf("Name: "); gets(name);
    printf("ID: "); gets(id);
    for (int i = 0; name[i]; i++) name[i] = (name[i]==' ') ? '.' : tolower(name[i]);
    sprintf(email, "%s%.2s@university.edu", name, id+strlen(id)-2);
    printf("Email: %s\n", email);
    return 0;
}