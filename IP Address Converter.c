#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

#define MAX_INPUT 50

// 🔍 Validate decimal IP
int isValidDecimal(char* ip) {
    int octet;
    char* token = strtok(ip, ".");
    int count = 0;

    while (token != NULL) {
        if (sscanf(token, "%d", &octet) != 1 || octet < 0 || octet > 255) return 0;
        count++;
        token = strtok(NULL, ".");
    }
    return count == 4;
}

// 🔍 Validate binary IP
int isValidBinary(char* bin) {
    if (strlen(bin) != 32) return 0;
    for (int i = 0; bin[i]; i++) {
        if (bin[i] != '0' && bin[i] != '1') return 0;
    }
    return 1;
}

// 🔍 Validate hex IP
int isValidHex(char* hex) {
    if (strlen(hex) != 8) return 0;
    for (int i = 0; hex[i]; i++) {
        if (!isxdigit(hex[i])) return 0;
    }
    return 1;
}

// 🔧 Convert decimal to binary and hex
void decimalToOthers(char* ip) {
    int octets[4];
    sscanf(ip, "%d.%d.%d.%d", &octets[0], &octets[1], &octets[2], &octets[3]);

    printf("Decimal: %d.%d.%d.%d\n", octets[0], octets[1], octets[2], octets[3]);

    printf("Binary : ");
    for (int i = 0; i < 4; i++) {
        for (int j = 7; j >= 0; j--) {
            printf("%d", (octets[i] >> j) & 1);
        }
        if (i < 3) printf(".");
    }
    printf("\n");

    printf("Hex     : %02X%02X%02X%02X\n", octets[0], octets[1], octets[2], octets[3]);
}

// 🔧 Convert binary to decimal and hex
void binaryToOthers(char* bin) {
    int octets[4];
    for (int i = 0; i < 4; i++) {
        octets[i] = 0;
        for (int j = 0; j < 8; j++) {
            octets[i] = (octets[i] << 1) + (bin[i * 8 + j] - '0');
        }
    }

    printf("Decimal: %d.%d.%d.%d\n", octets[0], octets[1], octets[2], octets[3]);

    printf("Binary : ");
    for (int i = 0; i < 4; i++) {
        for (int j = 7; j >= 0; j--) {
            printf("%d", (octets[i] >> j) & 1);
        }
        if (i < 3) printf(".");
    }
    printf("\n");

    printf("Hex     : %02X%02X%02X%02X\n", octets[0], octets[1], octets[2], octets[3]);
}

// 🔧 Convert hex to decimal and binary
void hexToOthers(char* hex) {
    int octets[4];
    for (int i = 0; i < 4; i++) {
        sscanf(hex + i * 2, "%2x", &octets[i]);
    }

    printf("Decimal: %d.%d.%d.%d\n", octets[0], octets[1], octets[2], octets[3]);

    printf("Binary : ");
    for (int i = 0; i < 4; i++) {
        for (int j = 7; j >= 0; j--) {
            printf("%d", (octets[i] >> j) & 1);
        }
        if (i < 3) printf(".");
    }
    printf("\n");

    printf("Hex     : %02X%02X%02X%02X\n", octets[0], octets[1], octets[2], octets[3]);
}

// 📌 Main program
int main() {
    char input[MAX_INPUT];

    printf("Enter IP Address (Decimal/Binary/Hex): ");
    scanf("%s", input);

    char inputCopy[MAX_INPUT];
    strcpy(inputCopy, input);

    if (strchr(input, '.')) {
        if (isValidDecimal(inputCopy)) {
            decimalToOthers(input);
        } else {
            printf("Error: Invalid decimal IP address.\n");
        }
    } else if (isValidBinary(input)) {
        binaryToOthers(input);
    } else if (isValidHex(input)) {
        for (int i = 0; input[i]; i++) input[i] = toupper(input[i]);
        hexToOthers(input);
    } else {
        printf("Error: Invalid IP format.\n");
    }

    return 0;
}