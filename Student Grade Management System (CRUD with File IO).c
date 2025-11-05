#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define MAX 1000

typedef struct { char id[10], name[50], course[30]; int grade; } Student;
Student s[MAX]; int n;

void load() {
    FILE *f = fopen("grades.txt", "r"); n = 0;
    if (!f) return;
    while (fscanf(f, "%[^,],%[^,],%[^,],%d\n", s[n].id, s[n].name, s[n].course, &s[n].grade) == 4) n++;
    fclose(f);
}

void save() {
    FILE *f = fopen("grades.txt", "w");
    for (int i = 0; i < n; i++)
        fprintf(f, "%s,%s,%s,%d\n", s[i].id, s[i].name, s[i].course, s[i].grade);
    fclose(f);
}

int find(char *id) {
    for (int i = 0; i < n; i++)
        if (!strcmp(s[i].id, id)) return i;
    return -1;
}

void add() {
    load(); Student t;
    printf("ID: "); gets(t.id);
    if (find(t.id) >= 0) { printf("ID exists.\n"); return; }
    printf("Name: "); gets(t.name);
    printf("Course: "); gets(t.course);
    printf("Grade (0–100): "); scanf("%d"); getchar();
    if (t.grade < 0 || t.grade > 100) { printf("Invalid grade.\n"); return; }
    FILE *f = fopen("grades.txt", "a");
    fprintf(f, "%s,%s,%s,%d\n", t.id, t.name, t.course, t.grade);
    fclose(f); printf("Record added!\n");
}

void view() {
    load(); if (!n) { printf("No records.\n"); return; }
    printf("ID Name Course Grade\n-----------------------------\n");
    for (int i = 0; i < n; i++)
        printf("%s %s %s %d\n", s[i].id, s[i].name, s[i].course, s[i].grade);
}

void update() {
    load(); char id[10]; printf("ID to update: "); gets(id);
    int i = find(id);
    if (i < 0) { printf("Not found.\n"); return; }
    printf("New Grade (0–100): "); scanf("%d"); getchar();
    if (s[i].grade < 0 || s[i].grade > 100) { printf("Invalid.\n"); return; }
    scanf("%d", &s[i].grade); getchar();
    save(); printf("Updated!\n");
}

void del() {
    load(); char id[10]; printf("ID to delete: "); gets(id);
    int i = find(id);
    if (i < 0) { printf("Not found.\n"); return; }
    for (int j = i; j < n - 1; j++) s[j] = s[j + 1];
    n--; save(); printf("Deleted!\n");
}

int main() {
    int c;
    while (1) {
        printf("\nGrade Manager\n1.Add 2.View 3.Update 4.Delete 5.Exit\nChoose: ");
        scanf("%d"); getchar();
        if (c == 1) add(); else if (c == 2) view();
        else if (c == 3) update(); else if (c == 4) del();
        else break;
    }
    return 0;
}