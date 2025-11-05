#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX 1000

typedef struct {
    char id[10], title[100], author[100], year[6], status[10];
} Book;

Book books[MAX];
int count = 0;

void load() {
    FILE *f = fopen("books.txt", "r");
    count = 0;
    if (!f) return;
    while (fscanf(f, "%[^|]|%[^|]|%[^|]|%[^|]|%[^\n]\n", books[count].id, books[count].title,
           books[count].author, books[count].year, books[count].status) == 5) count++;
    fclose(f);
}

void save() {
    FILE *f = fopen("books.txt", "w");
    for (int i = 0; i < count; i++)
        fprintf(f, "%s|%s|%s|%s|%s\n", books[i].id, books[i].title, books[i].author,
                books[i].year, books[i].status);
    fclose(f);
}

void add() {
    load();
    Book b;
    printf("BookID: "); gets(b.id);
    for (int i = 0; i < count; i++)
        if (!strcmp(books[i].id, b.id)) { printf("ID exists.\n"); return; }
    printf("Title: "); gets(b.title);
    printf("Author: "); gets(b.author);
    printf("Year: "); gets(b.year);
    int y = atoi(b.year);
    if (y < 1500 || y > 2025) { printf("Invalid year.\n"); return; }
    printf("Status (Available/Borrowed): "); gets(b.status);
    if (strcmp(b.status, "Available") && strcmp(b.status, "Borrowed")) {
        printf("Invalid status.\n"); return;
    }
    FILE *f = fopen("books.txt", "a");
    fprintf(f, "%s|%s|%s|%s|%s\n", b.id, b.title, b.author, b.year, b.status);
    fclose(f);
    printf("Book added!\n");
}

void view() {
    load();
    if (count == 0) { printf("No records.\n"); return; }
    printf("ID Title Author Year Status\n-------------------------------\n");
    for (int i = 0; i < count; i++)
        printf("%s %s %s %s %s\n", books[i].id, books[i].title, books[i].author,
               books[i].year, books[i].status);
}

void update() {
    load();
    char id[10]; printf("BookID to update: "); gets(id);
    for (int i = 0; i < count; i++) {
        if (!strcmp(books[i].id, id)) {
            printf("New Title: "); gets(books[i].title);
            printf("New Author: "); gets(books[i].author);
            printf("New Year: "); gets(books[i].year);
            int y = atoi(books[i].year);
            if (y < 1500 || y > 2025) { printf("Invalid year.\n"); return; }
            printf("New Status: "); gets(books[i].status);
            if (strcmp(books[i].status, "Available") && strcmp(books[i].status, "Borrowed")) {
                printf("Invalid status.\n"); return;
            }
            save(); printf("Book updated!\n"); return;
        }
    }
    printf("BookID not found.\n");
}

void del() {
    load();
    char id[10]; printf("BookID to delete: "); gets(id);
    for (int i = 0; i < count; i++) {
        if (!strcmp(books[i].id, id)) {
            for (int j = i; j < count - 1; j++) books[j] = books[j + 1];
            count--; save(); printf("Book deleted!\n"); return;
        }
    }
    printf("BookID not found.\n");
}

void search() {
    load();
    char q[100]; printf("Search Title/Author: "); gets(q);
    int found = 0;
    for (int i = 0; i < count; i++) {
        if (strstr(books[i].title, q) || strstr(books[i].author, q)) {
            printf("%s | %s | %s | %s | %s\n", books[i].id, books[i].title,
                   books[i].author, books[i].year, books[i].status);
            found = 1;
        }
    }
    if (!found) printf("No match.\n");
}

int main() {
    int c;
    while (1) {
        printf("\n1.Add 2.View 3.Update 4.Delete 5.Search 6.Exit\nChoose: ");
        scanf("%d", &c); getchar();
        if (c == 1) add();
        else if (c == 2) view();
        else if (c == 3) update();
        else if (c == 4) del();
        else if (c == 5) search();
        else if (c == 6) break;
    }
    return 0;
}