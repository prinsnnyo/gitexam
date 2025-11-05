#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_WORDS 1000
#define MAX_WORD_LEN 50
#define MAX_STOPWORDS 100

// Structure to hold word and its frequency
typedef struct {
    char word[MAX_WORD_LEN];
    int count;
} WordFreq;

WordFreq wordList[MAX_WORDS];
char stopwords[MAX_STOPWORDS][MAX_WORD_LEN];
int wordCount = 0;
int stopwordCount = 0;

// 🔧 Normalize word: lowercase and remove punctuation
void normalize(char* word) {
    int j = 0;
    for (int i = 0; word[i]; i++) {
        if (isalpha(word[i])) {
            word[j++] = tolower(word[i]);
        }
    }
    word[j] = '\0';
}

// 🔍 Check if word is a stopword
int isStopword(char* word) {
    for (int i = 0; i < stopwordCount; i++) {
        if (strcmp(word, stopwords[i]) == 0) {
            return 1;
        }
    }
    return 0;
}

// 📊 Add or update word frequency
void addWord(char* word) {
    for (int i = 0; i < wordCount; i++) {
        if (strcmp(wordList[i].word, word) == 0) {
            wordList[i].count++;
            return;
        }
    }
    strcpy(wordList[wordCount].word, word);
    wordList[wordCount].count = 1;
    wordCount++;
}

// 📁 Load stopwords from file
void loadStopwords(const char* filename) {
    FILE* file = fopen(filename, "r");
    if (!file) {
        printf("Error: Cannot open stopwords file.\n");
        exit(1);
    }

    while (fscanf(file, "%s", stopwords[stopwordCount]) != EOF) {
        normalize(stopwords[stopwordCount]);
        stopwordCount++;
    }

    fclose(file);
}

// 📁 Process input file
void processFile(const char* filename) {
    FILE* file = fopen(filename, "r");
    if (!file) {
        printf("Error: Cannot open input file.\n");
        exit(1);
    }

    fseek(file, 0, SEEK_END);
    long size = ftell(file);
    if (size == 0) {
        printf("Error: Input file is empty.\n");
        fclose(file);
        exit(1);
    }
    rewind(file);

    char word[MAX_WORD_LEN];
    while (fscanf(file, "%s", word) != EOF) {
        normalize(word);
        if (strlen(word) > 0 && !isStopword(word)) {
            addWord(word);
        }
    }

    fclose(file);
}

// 🔢 Sort words by frequency (descending)
void sortWords() {
    for (int i = 0; i < wordCount - 1; i++) {
        for (int j = i + 1; j < wordCount; j++) {
            if (wordList[j].count > wordList[i].count) {
                WordFreq temp = wordList[i];
                wordList[i] = wordList[j];
                wordList[j] = temp;
            }
        }
    }
}

// 📤 Export results to file
void exportToFile(const char* filename) {
    FILE* file = fopen(filename, "w");
    if (!file) {
        printf("Error: Cannot write to output file.\n");
        return;
    }

    for (int i = 0; i < wordCount; i++) {
        fprintf(file, "%s: %d\n", wordList[i].word, wordList[i].count);
    }

    fclose(file);
}

int main() {
    loadStopwords("stopwords.txt");
    processFile("input.txt");
    sortWords();

    printf("Word Frequency Count (excluding stopwords):\n");
    for (int i = 0; i < wordCount; i++) {
        printf("%s -> %d\n", wordList[i].word, wordList[i].count);
    }

    char choice;
    printf("\nExport results to output.txt? (y/n): ");
    scanf(" %c", &choice);
    if (choice == 'y' || choice == 'Y') {
        exportToFile("output.txt");
        printf("Results exported to output.txt\n");
    }

    return 0;
}