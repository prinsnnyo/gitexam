#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_STUDENTS 100
#define MAX_LINE 200
#define FILE_NAME "students.txt"

typedef struct {
    char studentID[10];
    char name[50];
    char course[30];
    int yearLevel;
    float gpa;
} Student;

Student students[MAX_STUDENTS];
int studentCount = 0;

// 🔍 Load students from file
void loadStudents() {
    FILE* file = fopen(FILE_NAME, "r");
    if (!file) return;

    char line[MAX_LINE];
    studentCount = 0;

    while (fgets(line, sizeof(line), file)) {
        sscanf(line, "%[^|]|%[^|]|%[^|]|%d|%f",
               students[studentCount].studentID,
               students[studentCount].name,
               students[studentCount].course,
               &students[studentCount].yearLevel,
               &students[studentCount].gpa);
        studentCount++;
    }

    fclose(file);
}

// 💾 Save students to file
void saveStudents() {
    FILE* file = fopen(FILE_NAME, "w");
    for (int i = 0; i < studentCount; i++) {
        fprintf(file, "%s|%s|%s|%d|%.2f\n",
                students[i].studentID,
                students[i].name,
                students[i].course,
                students[i].yearLevel,
                students[i].gpa);
    }
    fclose(file);
}

// ✅ Validate GPA
int isValidGPA(float gpa) {
    return gpa >= 0.00 && gpa <= 5.00;
}

// 🔍 Check if StudentID is unique
int isUniqueID(char* id) {
    for (int i = 0; i < studentCount; i++) {
        if (strcmp(students[i].studentID, id) == 0) return 0;
    }
    return 1;
}

// ➕ Add student
void addStudent() {
    Student newStudent;
    printf("Enter StudentID: ");
    scanf("%s", newStudent.studentID);
    if (!isUniqueID(newStudent.studentID)) {
        printf("Error: StudentID already exists.\n");
        return;
    }

    getchar(); // clear newline
    printf("Enter Name: ");
    fgets(newStudent.name, sizeof(newStudent.name), stdin);
    newStudent.name[strcspn(newStudent.name, "\n")] = '\0';

    printf("Enter Course: ");
    fgets(newStudent.course, sizeof(newStudent.course), stdin);
    newStudent.course[strcspn(newStudent.course, "\n")] = '\0';

    printf("Enter YearLevel: ");
    scanf("%d", &newStudent.yearLevel);

    printf("Enter GPA: ");
    scanf("%f", &newStudent.gpa);
    if (!isValidGPA(newStudent.gpa)) {
        printf("Error: Invalid GPA.\n");
        return;
    }

    students[studentCount++] = newStudent;
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

    printf("\nStudentID Name                Course     Year GPA\n");
    printf("------------------------------------------------------\n");
    for (int i = 0; i < studentCount; i++) {
        printf("%-10s %-20s %-10s %-4d %.2f\n",
               students[i].studentID,
               students[i].name,
               students[i].course,
               students[i].yearLevel,
               students[i].gpa);
    }
}

// ✏️ Update student
void updateStudent() {
    char id[10];
    loadStudents();
    printf("Enter StudentID to update: ");
    scanf("%s", id);

    for (int i = 0; i < studentCount; i++) {
        if (strcmp(students[i].studentID, id) == 0) {
            getchar();
            printf("Enter new Name: ");
            fgets(students[i].name, sizeof(students[i].name), stdin);
            students[i].name[strcspn(students[i].name, "\n")] = '\0';

            printf("Enter new Course: ");
            fgets(students[i].course, sizeof(students[i].course), stdin);
            students[i].course[strcspn(students[i].course, "\n")] = '\0';

            printf("Enter new YearLevel: ");
            scanf("%d", &students[i].yearLevel);

            printf("Enter new GPA: ");
            scanf("%f", &students[i].gpa);
            if (!isValidGPA(students[i].gpa)) {
                printf("Error: Invalid GPA.\n");
                return;
            }

            saveStudents();
            printf("Record updated successfully!\n");
            return;
        }
    }

    printf("StudentID not found.\n");
}

// ❌ Delete student
void deleteStudent() {
    char id[10];
    loadStudents();
    printf("Enter StudentID to delete: ");
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
        printf("StudentID not found.\n");
    }
}

// 🔍 Search student
void searchStudent() {
    char keyword[50];
    int found = 0;
    loadStudents();
    getchar();
    printf("Enter Name or Course to search: ");
    fgets(keyword, sizeof(keyword), stdin);
    keyword[strcspn(keyword, "\n")] = '\0';

    for (int i = 0; i < studentCount; i++) {
        if (strstr(students[i].name, keyword) || strstr(students[i].course, keyword)) {
            printf("%s | %s | %s | %d | %.2f\n",
                   students[i].studentID,
                   students[i].name,
                   students[i].course,
                   students[i].yearLevel,
                   students[i].gpa);
            found = 1;
        }
    }

    if (!found) {
        printf("No matching records found.\n");
    }
}

// 📌 Main menu
int main() {
    int choice;

    do {
        printf("\n===== Student Records Management =====\n");
        printf("1. Add Student Record\n");
        printf("2. View All Records\n");
        printf("3. Update Record\n");
        printf("4. Delete Record\n");
        printf("5. Search Record\n");
        printf("6. Exit\n");
        printf("Choose an option: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1: addStudent(); break;
            case 2: viewStudents(); break;
            case 3: updateStudent(); break;
            case 4: deleteStudent(); break;
            case 5: searchStudent(); break;
        }

    } while (choice != 6);

    return 0;
}