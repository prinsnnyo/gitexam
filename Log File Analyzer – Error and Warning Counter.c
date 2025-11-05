#include <stdio.h>
#include <string.h>
#include <ctype.h>

int main() {
    FILE *f = fopen("system.log", "r");
    if (!f) { printf("Error: system.log not found.\n"); return 1; }

    char line[500], lastErr[500] = "";
    int err = 0, warn = 0, info = 0;

    while (fgets(line, sizeof(line), f)) {
        char l[500]; strcpy(l, line);
        for (int i = 0; l[i]; i++) l[i] = toupper(l[i]);
        if (strstr(l, "ERROR")) { err++; strcpy(lastErr, line); }
        if (strstr(l, "WARNING")) warn++;
        if (strstr(l, "INFO")) info++;
    }
    fclose(f);

    FILE *r = fopen("report.txt", "w");
    fprintf(r, "Log Summary Report\n-------------------\n");
    fprintf(r, "Total ERRORs : %d\nTotal WARNINGs: %d\nTotal INFOs : %d\n", err, warn, info);
    fprintf(r, "Last ERROR : %s", lastErr[0] ? lastErr : "None\n");
    fclose(r);

    printf("Log Summary Report\n-------------------\n");
    printf("Total ERRORs : %d\nTotal WARNINGs: %d\nTotal INFOs : %d\n", err, warn, info);
    printf("Last ERROR : %s", lastErr[0] ? lastErr : "None\n");

    return 0;
}