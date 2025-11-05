#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_LINE 500
#define LOG_FILE "system.log"
#define REPORT_FILE "report.txt"

// 🔧 Convert string to uppercase
void toUpper(char* str) {
    for (int i = 0; str[i]; i++) {
        str[i] = toupper(str[i]);
    }
}

int main() {
    FILE* log = fopen(LOG_FILE, "r");
    if (!log) {
        printf("Error: %s not found.\n", LOG_FILE);
        return 1;
    }

    int errorCount = 0, warningCount = 0, infoCount = 0;
    char line[MAX_LINE];
    char lastError[MAX_LINE] = "";

    while (fgets(line, sizeof(line), log)) {
        char temp[MAX_LINE];
        strcpy(temp, line);
        toUpper(temp);

        if (strstr(temp, "ERROR")) {
            errorCount++;
            strcpy(lastError, line);
        }
        if (strstr(temp, "WARNING")) {
            warningCount++;
        }
        if (strstr(temp, "INFO")) {
            infoCount++;
        }
    }

    fclose(log);

    // 📋 Display summary
    printf("Log Summary Report\n");
    printf("-------------------\n");
    printf("Total ERRORs   : %d\n", errorCount);
    printf("Total WARNINGs : %d\n", warningCount);
    printf("Total INFOs    : %d\n", infoCount);
    if (errorCount > 0) {
        printf("Last ERROR     : %s", lastError);
    } else {
        printf("Last ERROR     : None\n");
    }

    // 💾 Write to report.txt
    FILE* report = fopen(REPORT_FILE, "w");
    fprintf(report, "Log Summary Report\n");
    fprintf(report, "-------------------\n");
    fprintf(report, "Total ERRORs   : %d\n", errorCount);
    fprintf(report, "Total WARNINGs : %d\n", warningCount);
    fprintf(report, "Total INFOs    : %d\n", infoCount);
    if (errorCount > 0) {
        fprintf(report, "Last ERROR     : %s", lastError);
    } else {
        fprintf(report, "Last ERROR     : None\n");
    }
    fclose(report);

    return 0;
}