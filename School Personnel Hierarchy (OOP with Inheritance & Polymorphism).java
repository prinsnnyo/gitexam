#include <stdio.h>
#include <string.h>

#define MAX 100

typedef struct {
    char id[10], name[50];
    int age, type; // 1=Teacher, 2=Student, 3=Admin
    char extra[50]; // Subject / Course / Department
    int yearLevel;  // Only for students
    void (*introduce)();
    void (*action)();
} Person;

Person people[MAX];
int count = 0;

void introTeacher() {
    printf("I am %s, a Teacher of %s.\n", people[count].name, people[count].extra);
}
void gradeStudent() {
    printf("%s has graded a student.\n", people[count].name);
}

void introStudent() {
    printf("I am %s, a %d year student of %s.\n", people[count].name, people[count].yearLevel, people[count].extra);
}
void submitAssignment() {
    printf("%s has submitted an assignment.\n", people[count].name);
}

void introAdmin() {
    printf("I am %s, working in the %s department.\n", people[count].name, people[count].extra);
}
void processDocument() {
    printf("%s has processed a document.\n", people[count].name);
}

int find(char *id) {
    for (int i = 0; i < count; i++)
        if (strcmp(people[i].id, id) == 0) return i;
    return -1;
}

void addPerson() {
    if (count >= MAX) return;
    Person p;
    printf("Type (1-Teacher, 2-Student, 3-Admin): "); scanf("%d", &p.type);
    printf("ID: "); scanf("%s", p.id);
    if (find(p.id) >= 0) { printf("ID exists.\n"); return; }
    printf("Name: "); getchar(); gets(p.name);
    printf("Age: "); scanf("%d", &p.age);
    if (p.age <= 0) { printf("Invalid age.\n"); return; }

    if (p.type == 1) {
        printf("Subject: "); getchar(); gets(p.extra);
        p.introduce = introTeacher;
        p.action = gradeStudent;
    } else if (p.type == 2) {
        printf("Course: "); getchar(); gets(p.extra);
        printf("Year Level: "); scanf("%d", &p.yearLevel);
        p.introduce = introStudent;
        p.action = submitAssignment;
    } else if (p.type == 3) {
        printf("Department: "); getchar(); gets(p.extra);
        p.introduce = introAdmin;
        p.action = processDocument;
    }
    people[count++] = p;
    printf("Personnel added successfully.\n");
}

void viewAll() {
    for (int i = 0; i < count; i++) {
        printf("ID: %s - ", people[i].id);
        people[i].introduce();
    }
}

void roleAction() {
    char id[10]; printf("Enter ID: "); scanf("%s", id);
    int i = find(id);
    if (i < 0) { printf("Not found.\n"); return; }
    people[i].action();
}

int main() {
    int ch;
    while (1) {
        printf("\n1.Add 2.View All 3.Role Action 4.Exit\nChoose: ");
        scanf("%d", &ch);
        if (ch == 1) addPerson();
        else if (ch == 2) viewAll();
        else if (ch == 3) roleAction();
        else break;
    }
    return 0;
}