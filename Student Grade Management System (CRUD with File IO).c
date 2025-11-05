#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_STUDENTS 100
#define FILE_NAME "grades.txt"

typedef struct {
    char studentID[10];
    char name[50];
    char course[30];
    int finalGrade;
} Student;

Student students[MAX_STUDENTS];
int studentCount = 0;

// 🔍 Load students from file
void loadStudents() {
    FILE* file = fopen(FILE_NAME, "r");
    if (!file) return;

    studentCount = 0;
    while (fscanf(file, "%[^,],%[^,],%[^,],%d\n",
                  students[studentCount].studentID,
                  students[studentCount].name,
                  students[studentCount].course,
                  &students[studentCount].finalGrade) == 4) {
        studentCount++;
    }

    fclose(file);
}

// 💾 Save students to file
void saveStudents() {
    FILE* file = fopen(FILE_NAME, "w");
    for (int i = 0; i < studentCount; i++) {
        fprintf(file, "%s,%s,%s,%d\n",
                students[i].studentID,
                students[i].name,
                students[i].course,
                students[i].finalGrade);
    }
    fclose(file);
}

// ✅ Check for unique Student ID
int isUniqueID(char* id) {
    for (int i = 0; i < studentCount; i++) {
        if (strcmp(students[i].studentID, id) == 0) return 0;
    }
    return 1;
}

// ➕ Add student
void addStudent() {
    Student s;
    printf("Enter Student ID: ");
    scanf("%s", s.studentID);
    if (!isUniqueID(s.studentID)) {
        printf("Error: Student ID already exists.\n");
        return;
    }

    getchar(); // clear newline
    printf("Enter Name: ");
    fgets(s.name, sizeof(s.name), stdin);
    s.name[strcspn(s.name, "\n")] = '\0';

    printf("Enter Course: ");
    fgets(s.course, sizeof(s.course), stdin);
    s.course[strcspn(s.course, "\n")] = '\0';

    printf("Enter Final Grade (0–100): ");
    scanf("%d", &s.finalGrade);
    if (s.finalGrade < 0 || s.finalGrade > 100) {
        printf("Error: Final grade must be between 0 and 100.\n");
        return;
    }

    students[studentCount++] = s;
    saveStudents();
    printf("Record added successfully!\n");
}

// 📋 View all students
void viewStudents() {
    loadStudents();
    if (studentCount == 0) {
        printf("No records found.\n");
        return;
    }

    printf("\nStudentID Name                Course     FinalGrade\n");
    printf("------------------------------------------------------\n");
    for (int i = 0; i < studentCount; i++) {
        printf("%-10s %-20s %-10s %d\n",
               students[i].studentID,
               students[i].name,
               students[i].course,
               students[i].finalGrade);
    }
}

// ✏️ Update student
void updateStudent() {
    char id[10];
    loadStudents();
    printf("Enter Student ID to update: ");
    scanf("%s", id);

    for (int i = 0; i < studentCount; i++) {
        if (strcmp(students[i].studentID, id) == 0) {
            printf("Enter new Final Grade (0–100): ");
            scanf("%d", &students[i].finalGrade);
            if (students[i].finalGrade < 0 || students[i].finalGrade > 100) {
                printf("Error: Final grade must be between 0 and 100.\n");
                return;
            }
            saveStudents();
            printf("Record updated successfully!\n");
            return;
        }
    }

    printf("Student ID not found.\n");
}

// ❌ Delete student
void deleteStudent() {
    char id[10];
    loadStudents();
    printf("Enter Student ID to delete: ");
    scanf("%s", id);

    int found = 0;
    for (int i = 0; i < studentCount; i++) {
        if (strcmp(students[i].studentID, id) == 0) {
            for (int j = i; j < studentCount - 1; j++) {
                students[j] = students[j + 1];
            }
            studentCount--;
            found = 1;
            break;
        }
    }

    if (found) {
        saveStudents();
        printf("Record deleted successfully!\n");
    } else {
        printf("Student ID not found.\n");
    }
}

// 📌 Main menu
int main() {
    int choice;

    do {
        printf("\n===== Student Grade Management System =====\n");
        printf("1. Add Record\n");
        printf("2. View Records\n");
        printf("3. Update Record\n");
        printf("4. Delete Record\n");
        printf("5. Exit\n");
        printf("Choose an option: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1: addStudent(); break;
            case 2: viewStudents(); break;
            case 3: updateStudent(); break;
            case 4: deleteStudent(); break;
        }

    } while (choice != 5);

    return 0;
}