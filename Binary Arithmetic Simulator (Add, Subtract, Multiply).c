#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

#define MAX_BITS 17  // 16 bits + null terminator

// 🔍 Validate binary input
int isValidBinary(char* bin) {
    if (strlen(bin) > 16) return 0;
    for (int i = 0; bin[i]; i++) {
        if (bin[i] != '0' && bin[i] != '1') return 0;
    }
    return 1;
}

// 🔧 Convert binary string to decimal
int binToDec(char* bin) {
    int dec = 0;
    for (int i = 0; bin[i]; i++) {
        dec = dec * 2 + (bin[i] - '0');
    }
    return dec;
}

// 🔁 Convert decimal to binary string
void decToBin(int num, char* bin) {
    int i = 0;
    char temp[MAX_BITS] = "";
    if (num == 0) {
        strcpy(bin, "0");
        return;
    }
    while (num > 0) {
        temp[i++] = (num % 2) + '0';
        num /= 2;
    }
    temp[i] = '\0';

    // Reverse
    for (int j = 0; j < i; j++) {
        bin[j] = temp[i - j - 1];
    }
    bin[i] = '\0';
}

// ➕ Binary addition with step-by-step
void binaryAddition(char* a, char* b) {
    int lenA = strlen(a), lenB = strlen(b);
    int maxLen = lenA > lenB ? lenA : lenB;
    char result[MAX_BITS] = "";
    int carry = 0, i, j, k = maxLen;

    result[k] = '\0';
    i = lenA - 1;
    j = lenB - 1;

    printf("Step-by-step:\n%s\n+ %s\n------\n", a, b);

    while (k > 0) {
        int bitA = i >= 0 ? a[i--] - '0' : 0;
        int bitB = j >= 0 ? b[j--] - '0' : 0;
        int sum = bitA + bitB + carry;
        result[--k] = (sum % 2) + '0';
        carry = sum / 2;
    }

    if (carry) {
        printf("1%s\n", result);
    } else {
        printf("%s\n", result);
    }

    int dec = binToDec(result);
    printf("Binary: %s\nDecimal: %d\nHexadecimal: %X\n", result, dec, dec);
}

// ➖ Binary subtraction using two’s complement
void binarySubtraction(char* a, char* b) {
    int decA = binToDec(a);
    int decB = binToDec(b);
    int result = decA - decB;

    printf("Step-by-step:\n%s\n- %s\n------\n", a, b);

    if (result < 0) {
        printf("Error: Negative result not supported in unsigned binary.\n");
        return;
    }

    char bin[MAX_BITS];
    decToBin(result, bin);
    printf("%s\n", bin);
    printf("Binary: %s\nDecimal: %d\nHexadecimal: %X\n", bin, result, result);
}

// ✖️ Binary multiplication using repeated addition
void binaryMultiplication(char* a, char* b) {
    int decA = binToDec(a);
    int decB = binToDec(b);
    int result = 0;

    printf("Step-by-step:\n%s\nx %s\n-----\n", a, b);

    for (int i = 0; i < decB; i++) {
        result += decA;
        char temp[MAX_BITS];
        decToBin(decA, temp);
        printf("+ %s\n", temp);
    }

    char bin[MAX_BITS];
    decToBin(result, bin);
    printf("-----\n%s\n", bin);
    printf("Binary: %s\nDecimal: %d\nHexadecimal: %X\n", bin, result, result);
}

// 📌 Main menu
int main() {
    int choice;
    char bin1[MAX_BITS], bin2[MAX_BITS];

    do {
        printf("\n===== Binary Arithmetic Simulator =====\n");
        printf("1. Addition\n2. Subtraction\n3. Multiplication\n4. Exit\nChoose an option: ");
        scanf("%d", &choice);
        getchar(); // clear newline

        if (choice >= 1 && choice <= 3) {
            printf("Enter first binary number: ");
            scanf("%s", bin1);
            printf("Enter second binary number: ");
            scanf("%s", bin2);

            if (!isValidBinary(bin1) || !isValidBinary(bin2)) {
                printf("Error: Invalid binary input (only 0 and 1, max 16 bits).\n");
                continue;
            }

            if (choice == 1) binaryAddition(bin1, bin2);
            else if (choice == 2) binarySubtraction(bin1, bin2);
            else if (choice == 3) binaryMultiplication(bin1, bin2);
        }

    } while (choice != 4);

    return 0;
}