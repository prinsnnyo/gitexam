#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

#define MAX_LEN 100

// 🔍 Validate input based on base
int isValid(char* num, int base) {
    for (int i = 0; num[i]; i++) {
        char c = toupper(num[i]);
        if (base == 2 && (c != '0' && c != '1')) return 0;
        if (base == 8 && (c < '0' || c > '7')) return 0;
        if (base == 10 && !isdigit(c)) return 0;
        if (base == 16 && !isdigit(c) && (c < 'A' || c > 'F')) return 0;
    }
    return 1;
}

// 🔧 Convert string to decimal
int toDecimal(char* num, int base) {
    return (int)strtol(num, NULL, base);
}

// 🔁 Convert decimal to other bases
void fromDecimal(int num) {
    printf("Decimal: %d\n", num);
    printf("Binary: ");
    for (int i = 31; i >= 0; i--) {
        printf("%d", (num >> i) & 1);
    }
    printf("\nOctal: %o\n", num);
    printf("Hexadecimal: %X\n", num);
}

// 📌 Main menu
int main() {
    int choice;

    do {
        printf("\n===== Multi-base Calculator =====\n");
        printf("1. Base Conversion\n");
        printf("2. Arithmetic Operation\n");
        printf("3. Exit\n");
        printf("Choose an option: ");
        scanf("%d", &choice);
        getchar(); // clear newline

        if (choice == 1) {
            char num[MAX_LEN], baseStr[MAX_LEN];
            int base;

            printf("Enter number: ");
            scanf("%s", num);
            printf("Enter base (Binary/Octal/Decimal/Hexadecimal): ");
            scanf("%s", baseStr);

            if (strcasecmp(baseStr, "Binary") == 0) base = 2;
            else if (strcasecmp(baseStr, "Octal") == 0) base = 8;
            else if (strcasecmp(baseStr, "Decimal") == 0) base = 10;
            else if (strcasecmp(baseStr, "Hexadecimal") == 0) base = 16;
            else {
                printf("Error: Unknown base.\n");
                continue;
            }

            if (!isValid(num, base)) {
                printf("Error: Invalid %s number.\n", baseStr);
                continue;
            }

            int decimal = toDecimal(num, base);
            fromDecimal(decimal);

        } else if (choice == 2) {
            char num1[MAX_LEN], base1Str[MAX_LEN];
            char num2[MAX_LEN], base2Str[MAX_LEN];
            char op;

            int base1, base2;

            printf("Enter first number: ");
            scanf("%s", num1);
            printf("Enter base: ");
            scanf("%s", base1Str);

            printf("Enter second number: ");
            scanf("%s", num2);
            printf("Enter base: ");
            scanf("%s", base2Str);

            printf("Operation (+/-): ");
            scanf(" %c", &op);

            if (strcasecmp(base1Str, "Binary") == 0) base1 = 2;
            else if (strcasecmp(base1Str, "Octal") == 0) base1 = 8;
            else if (strcasecmp(base1Str, "Decimal") == 0) base1 = 10;
            else if (strcasecmp(base1Str, "Hexadecimal") == 0) base1 = 16;
            else {
                printf("Error: Unknown base for first number.\n");
                continue;
            }

            if (strcasecmp(base2Str, "Binary") == 0) base2 = 2;
            else if (strcasecmp(base2Str, "Octal") == 0) base2 = 8;
            else if (strcasecmp(base2Str, "Decimal") == 0) base2 = 10;
            else if (strcasecmp(base2Str, "Hexadecimal") == 0) base2 = 16;
            else {
                printf("Error: Unknown base for second number.\n");
                continue;
            }

            if (!isValid(num1, base1)) {
                printf("Error: Invalid %s number.\n", base1Str);
                continue;
            }

            if (!isValid(num2, base2)) {
                printf("Error: Invalid %s number.\n", base2Str);
                continue;
            }

            int dec1 = toDecimal(num1, base1);
            int dec2 = toDecimal(num2, base2);
            int result = (op == '+') ? dec1 + dec2 : dec1 - dec2;

            fromDecimal(result);
        }

    } while (choice != 3);

    return 0;
}