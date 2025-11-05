#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_SIZE 1000000  // 1 MB

// 🔧 Compress using RLE
void compressFile() {
    FILE *in = fopen("input.txt", "r");
    FILE *out = fopen("compressed.txt", "w");

    if (!in || !out) {
        printf("Error opening files.\n");
        return;
    }

    char ch, prev = '\0';
    int count = 0;

    while ((ch = fgetc(in)) != EOF) {
        if (!isprint(ch)) continue;  // Skip non-printable

        if (ch == prev) {
            count++;
        } else {
            if (count > 0) {
                fprintf(out, "%c%d", prev, count);
            }
            prev = ch;
            count = 1;
        }
    }

    if (count > 0) {
        fprintf(out, "%c%d", prev, count);
    }

    fclose(in);
    fclose(out);
    printf("Compression complete. Output saved to compressed.txt\n");
}

// 🔧 Decompress RLE format
void decompressFile() {
    FILE *in = fopen("compressed.txt", "r");
    FILE *out = fopen("decompressed.txt", "w");

    if (!in || !out) {
        printf("Error opening files.\n");
        return;
    }

    char ch;
    while ((ch = fgetc(in)) != EOF) {
        if (!isprint(ch)) continue;

        if (isalpha(ch) || ispunct(ch) || isdigit(ch)) {
            char countStr[10] = "";
            int i = 0;
            char next;

            while ((next = fgetc(in)) != EOF && isdigit(next)) {
                countStr[i++] = next;
            }
            countStr[i] = '\0';

            int count = atoi(countStr);
            if (count <= 0) {
                printf("Error: Invalid RLE format.\n");
                fclose(in);
                fclose(out);
                return;
            }

            for (int j = 0; j < count; j++) {
                fputc(ch, out);
            }

            if (next != EOF) ungetc(next, in);  // Put back non-digit
        }
    }

    fclose(in);
    fclose(out);
    printf("Decompression complete. Output saved to decompressed.txt\n");
}

// 📌 Main menu
int main() {
    int choice;

    do {
        printf("\n===== File Compression Simulator (RLE) =====\n");
        printf("1. Compress File\n");
        printf("2. Decompress File\n");
        printf("3. Exit\n");
        printf("Choose an option: ");
        scanf("%d", &choice);

        if (choice == 1) {
            compressFile();
        } else if (choice == 2) {
            decompressFile();
        }

    } while (choice != 3);

    return 0;
}