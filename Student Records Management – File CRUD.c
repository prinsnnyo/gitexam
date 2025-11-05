#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX 1000

typedef struct {
    char id[10], name[100], course[50], year[5], gpa[6];
} Student;

Student s[MAX];
int count = 0;

void load() {
    FILE *f = fopen("students.txt", "r");
    count = 0;
    if (!f) return;
    while (fscanf(f, "%[^|]|%[^|]|%[^|]|%[^|]|%[^\n]\n", s[count].id, s[count].name,
           s[count].course, s[count].year, s[count].gpa) == 5) count++;
    fclose(f);
}

void save() {
    FILE *f = fopen("students.txt", "w");
    for (int i = 0; i < count; i++)
        fprintf(f, "%s|%s|%s|%s|%s\n", s[i].id, s[i].name, s[i].course, s[i].year, s[i].gpa);
    fclose(f);
}

void add() {
    load();
    Student t;
    printf("StudentID: "); gets(t.id);
    for (int i = 0; i < count; i++)
        if (!strcmp(s[i].id, t.id)) { printf("ID exists.\n"); return; }
    printf("Name: "); gets(t.name);
    printf("Course: "); gets(t.course);
    printf("YearLevel: "); gets(t.year);
    printf("GPA: "); gets(t.gpa);
    float g = atof(t.gpa);
    if (g < 0 || g > 5) { printf("Invalid GPA.\n"); return; }
    FILE *f = fopen("students.txt", "a");
    fprintf(f, "%s|%s|%s|%s|%s\n", t.id, t.name, t.course, t.year, t.gpa);
    fclose(f);
    printf("Record added!\n");
}

void view() {
    load();
    if (count == 0) { printf("No records.\n"); return; }
    printf("ID Name Course Year GPA\n-------------------------------\n");
    for (int i = 0; i < count; i++)
        printf("%s %s %s %s %s\n", s[i].id, s[i].name, s[i].course, s[i].year, s[i].gpa);
}

void update() {
    load();
    char id[10]; printf("StudentID to update: "); gets(id);
    for (int i = 0; i < count; i++) {
        if (!strcmp(s[i].id, id)) {
            printf("New Name: "); gets(s[i].name);
            printf("New Course: "); gets(s[i].course);
            printf("New YearLevel: "); gets(s[i].year);
            printf("New GPA: "); gets(s[i].gpa);
            float g = atof(s[i].gpa);
            if (g < 0 || g > 5) { printf("Invalid GPA.\n"); return; }
            save(); printf("Record updated!\n"); return;
        }
    }
    printf("StudentID not found.\n");
}

void del() {
    load();
    char id[10]; printf("StudentID to delete: "); gets(id);
    for (int i = 0; i < count; i++) {
        if (!strcmp(s[i].id, id)) {
            for (int j = i; j < count - 1; j++) s[j] = s[j + 1];
            count--; save(); printf("Record deleted!\n"); return;
        }
    }
    printf("StudentID not found.\n");
}

void search() {
    load();
    char q[100]; printf("Search Name/Course: "); gets(q);
    int f = 0;
    for (int i = 0; i < count; i++) {
        if (strstr(s[i].name, q) || strstr(s[i].course, q)) {
            printf("%s | %s | %s | %s | %s\n", s[i].id, s[i].name, s[i].course, s[i].year, s[i].gpa);
            f = 1;
        }
    }
    if (!f) printf("No match.\n");
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