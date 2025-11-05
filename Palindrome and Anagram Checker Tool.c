#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

#define MAX_LEN 200

// 🔧 Normalize string: remove spaces/punctuation, convert to lowercase
void normalize(char* input, char* output) {
    int j = 0;
    for (int i = 0; input[i]; i++) {
        if (isalpha(input[i])) {
            output[j++] = tolower(input[i]);
        }
    }
    output[j] = '\0';
}

// 🔁 Reverse string
void reverse(char* str, char* reversed) {
    int len = strlen(str);
    for (int i = 0; i < len; i++) {
        reversed[i] = str[len - 1 - i];
    }
    reversed[len] = '\0';
}

// 🔍 Check if palindrome
int isPalindrome(char* input) {
    char cleaned[MAX_LEN], reversed[MAX_LEN];
    normalize(input, cleaned);
    reverse(cleaned, reversed);
    return strcmp(cleaned, reversed) == 0;
}

// 🔁 Sort characters in string
void sortString(char* str) {
    int len = strlen(str);
    for (int i = 0; i < len - 1; i++) {
        for (int j = i + 1; j < len; j++) {
            if (str[i] > str[j]) {
                char temp = str[i];
                str[i] = str[j];
                str[j] = temp;
            }
        }
    }
}

// 🔍 Check if anagram
int isAnagram(char* input1, char* input2) {
    char cleaned1[MAX_LEN], cleaned2[MAX_LEN];
    normalize(input1, cleaned1);
    normalize(input2, cleaned2);
    sortString(cleaned1);
    sortString(cleaned2);
    return strcmp(cleaned1, cleaned2) == 0;
}

// 📌 Main menu loop
int main() {
    int choice;
    char input1[MAX_LEN], input2[MAX_LEN];

    do {
        printf("\n===== Palindrome & Anagram Tool =====\n");
        printf("1. Palindrome Checker\n");
        printf("2. Anagram Checker\n");
        printf("3. Exit\n");
        printf("Choose an option: ");
        scanf("%d", &choice);
        getchar(); // clear newline

        if (choice == 1) {
            printf("Enter word/phrase: ");
            fgets(input1, sizeof(input1), stdin);
            input1[strcspn(input1, "\n")] = '\0';

            if (isPalindrome(input1)) {
                printf("Output: Palindrome\n");
            } else {
                printf("Output: Not Palindrome\n");
            }

        } else if (choice == 2) {
            printf("Enter first word/phrase: ");
            fgets(input1, sizeof(input1), stdin);
            input1[strcspn(input1, "\n")] = '\0';

            printf("Enter second word/phrase: ");
            fgets(input2, sizeof(input2), stdin);
            input2[strcspn(input2, "\n")] = '\0';

            if (isAnagram(input1, input2)) {
                printf("Output: Anagrams\n");
            } else {
                printf("Output: Not Anagrams\n");
            }
        }

    } while (choice != 3);

    return 0;
}