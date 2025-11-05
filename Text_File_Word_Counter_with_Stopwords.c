#include <stdio.h>
#include <string.h>
#include <ctype.h>

int main() {
    char text[] = "The quick brown fox jumps over the lazy dog. The dog was not amused.";
    char *stop[] = {"the","was","over","not"};
    char *word = strtok(text, " .");
    while (word) {
        for (int i = 0; word[i]; i++) word[i] = tolower(word[i]);
        int skip = 0;
        for (int i = 0; i < 4; i++) if (!strcmp(word, stop[i])) skip = 1;
        if (!skip) printf("%s\n", word);
        word = strtok(NULL, " .");
    }
    return 0;
}