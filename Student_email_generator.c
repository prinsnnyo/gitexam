#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define MAX_EMAILS 100

// Store emails and IDs
char emails[MAX_EMAILS][100];
char ids[MAX_EMAILS][20];
int count = 0;

// Convert name to lowercase and replace spaces with dots
void formatName(char* name) {
    for (int i = 0; name[i]; i++) {
        if (name[i] == ' ') {
            name[i] = '.';
        } else {
            name[i] = tolower(name[i]);
        }
    }
}

// Generate email
void generateEmail(char* name, char* id, char* email) {
    char formattedName[100];
    strcpy(formattedName, name);
    formatName(formattedName);

    char lastTwo[3];
    int len = strlen(id);
    lastTwo[0] = id[len - 2];
    lastTwo[1] = id[len - 1];
    lastTwo[2] = '\0';

    sprintf(email, "%s%s@university.edu", formattedName, lastTwo);

    // Check for duplicates
    int duplicate = 0;
    for (int i = 0; i < count; i++) {
        if (strcmp(emails[i], email) == 0) {
            duplicate++;
        }
    }

    if (duplicate > 0) {
        sprintf(email, "%s%s_%d@university.edu", formattedName, lastTwo, duplicate);
    }

    // Save email and ID
    strcpy(emails[count], email);
    strcpy(ids[count], id);
    count++;
}

// Search email by ID
void searchEmail(char* id) {
    for (int i = 0; i < count; i++) {
        if (strcmp(ids[i], id) == 0) {
            printf("Email: %s\n", emails[i]);
            return;
        }
    }
    printf("ID not found.\n");
}

int main() {
    char name[100], id[20], email[100];
    int choice;

    do {
        printf("\n1. Add Student\n2. Search by ID\n3. Exit\nChoose: ");
        scanf("%d", &choice);
        getchar(); // clear newline

        if (choice == 1) {
            printf("Enter full name: ");
            fgets(name, sizeof(name), stdin);
            name[strcspn(name, "\n")] = '\0';

            printf("Enter student ID: ");
            scanf("%s", id);

            // Simple validation
            int valid = 1;
            for (int i = 0; name[i]; i++) {
                if (!isalpha(name[i]) && name[i] != ' ') {
                    valid = 0;
                    break;
                }
            }
            for (int i = 0; id[i]; i++) {
                if (!isdigit(id[i])) {
                    valid = 0;
                    break;
                }
            }

            if (!valid) {
                printf("Error: Invalid name or ID.\n");
                continue;
            }

            generateEmail(name, id, email);
            printf("Generated Email: %s\n", email);

        } else if (choice == 2) {
            printf("Enter student ID: ");
            scanf("%s", id);
            searchEmail(id);
        }

    } while (choice != 3);

    return 0;
}