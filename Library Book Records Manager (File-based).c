#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <time.h>

#define MAX_BOOKS 1000
#define MAX_LINE 200
#define FILE_NAME "books.txt"

typedef struct {
    char bookID[10];
    char title[50];
    char author[50];
    int year;
    char status[10];
} Book;

Book books[MAX_BOOKS];
int bookCount = 0;

// 🔍 Load books from file
void loadBooks() {
    FILE* file = fopen(FILE_NAME, "r");
    if (!file) return;

    char line[MAX_LINE];
    bookCount = 0;

    while (fgets(line, sizeof(line), file)) {
        sscanf(line, "%[^|]|%[^|]|%[^|]|%d|%[^|\n]", 
               books[bookCount].bookID, 
               books[bookCount].title, 
               books[bookCount].author, 
               &books[bookCount].year, 
               books[bookCount].status);
        bookCount++;
    }

    fclose(file);
}

// 💾 Save books to file
void saveBooks() {
    FILE* file = fopen(FILE_NAME, "w");
    for (int i = 0; i < bookCount; i++) {
        fprintf(file, "%s|%s|%s|%d|%s\n", 
                books[i].bookID, 
                books[i].title, 
                books[i].author, 
                books[i].year, 
                books[i].status);
    }
    fclose(file);
}

// ✅ Validate year
int isValidYear(int year) {
    int currentYear = 2025;
    return year >= 1500 && year <= currentYear;
}

// ✅ Validate status
int isValidStatus(char* status) {
    return strcmp(status, "Available") == 0 || strcmp(status, "Borrowed") == 0;
}

// 🔍 Check if BookID is unique
int isUniqueID(char* id) {
    for (int i = 0; i < bookCount; i++) {
        if (strcmp(books[i].bookID, id) == 0) return 0;
    }
    return 1;
}

// ➕ Add book
void addBook() {
    Book newBook;
    printf("Enter BookID: ");
    scanf("%s", newBook.bookID);
    if (!isUniqueID(newBook.bookID)) {
        printf("Error: BookID already exists.\n");
        return;
    }

    getchar(); // clear newline
    printf("Enter Title: ");
    fgets(newBook.title, sizeof(newBook.title), stdin);
    newBook.title[strcspn(newBook.title, "\n")] = '\0';

    printf("Enter Author: ");
    fgets(newBook.author, sizeof(newBook.author), stdin);
    newBook.author[strcspn(newBook.author, "\n")] = '\0';

    printf("Enter Year: ");
    scanf("%d", &newBook.year);
    if (!isValidYear(newBook.year)) {
        printf("Error: Invalid year.\n");
        return;
    }

    printf("Enter Status (Available/Borrowed): ");
    scanf("%s", newBook.status);
    if (!isValidStatus(newBook.status)) {
        printf("Error: Invalid status.\n");
        return;
    }

    books[bookCount++] = newBook;
    saveBooks();
    printf("Book added successfully!\n");
}

// 📋 View all books
void viewBooks() {
    loadBooks();
    if (bookCount == 0) {
        printf("No books found.\n");
        return;
    }

    printf("\nBookID  Title                     Author              Year  Status\n");
    printf("---------------------------------------------------------------------\n");
    for (int i = 0; i < bookCount; i++) {
        printf("%-7s %-25s %-18s %-5d %-10s\n", 
               books[i].bookID, 
               books[i].title, 
               books[i].author, 
               books[i].year, 
               books[i].status);
    }
}

// ✏️ Update book
void updateBook() {
    char id[10];
    loadBooks();
    printf("Enter BookID to update: ");
    scanf("%s", id);

    for (int i = 0; i < bookCount; i++) {
        if (strcmp(books[i].bookID, id) == 0) {
            getchar();
            printf("Enter new Title: ");
            fgets(books[i].title, sizeof(books[i].title), stdin);
            books[i].title[strcspn(books[i].title, "\n")] = '\0';

            printf("Enter new Author: ");
            fgets(books[i].author, sizeof(books[i].author), stdin);
            books[i].author[strcspn(books[i].author, "\n")] = '\0';

            printf("Enter new Year: ");
            scanf("%d", &books[i].year);
            if (!isValidYear(books[i].year)) {
                printf("Error: Invalid year.\n");
                return;
            }

            printf("Enter new Status: ");
            scanf("%s", books[i].status);
            if (!isValidStatus(books[i].status)) {
                printf("Error: Invalid status.\n");
                return;
            }

            saveBooks();
            printf("Book updated successfully!\n");
            return;
        }
    }

    printf("BookID not found.\n");
}

// ❌ Delete book
void deleteBook() {
    char id[10];
    loadBooks();
    printf("Enter BookID to delete: ");
    scanf("%s", id);

    int found = 0;
    for (int i = 0; i < bookCount; i++) {
        if (strcmp(books[i].bookID, id) == 0) {
            for (int j = i; j < bookCount - 1; j++) {
                books[j] = books[j + 1];
            }
            bookCount--;
            found = 1;
            break;
        }
    }

    if (found) {
        saveBooks();
        printf("Book deleted successfully!\n");
    } else {
        printf("BookID not found.\n");
    }
}

// 🔍 Search book
void searchBook() {
    char keyword[50];
    int found = 0;
    loadBooks();
    getchar();
    printf("Enter Title or Author to search: ");
    fgets(keyword, sizeof(keyword), stdin);
    keyword[strcspn(keyword, "\n")] = '\0';

    for (int i = 0; i < bookCount; i++) {
        if (strstr(books[i].title, keyword) || strstr(books[i].author, keyword)) {
            printf("%s | %s | %s | %d | %s\n", 
                   books[i].bookID, 
                   books[i].title, 
                   books[i].author, 
                   books[i].year, 
                   books[i].status);
            found = 1;
        }
    }

    if (!found) {
        printf("No matching books found.\n");
    }
}

// 📌 Main menu
int main() {
    int choice;

    do {
        printf("\n===== Library Book Records Manager =====\n");
        printf("1. Add Book Record\n");
        printf("2. View All Books\n");
        printf("3. Update Book Record\n");
        printf("4. Delete Book Record\n");
        printf("5. Search Book\n");
        printf("6. Exit\n");
        printf("Choose an option: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1: addBook(); break;
            case 2: viewBooks(); break;
            case 3: updateBook(); break;
            case 4: deleteBook(); break;
            case 5: searchBook(); break;
        }

    } while (choice != 6);

    return 0;
}