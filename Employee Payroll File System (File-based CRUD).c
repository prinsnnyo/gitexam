#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_EMPLOYEES 100
#define FILE_NAME "payroll.txt"

typedef struct {
    char empID[10];
    char name[50];
    char position[30];
    float basicSalary;
    float allowances;
    float deductions;
    float tax;
    float netSalary;
} Employee;

Employee employees[MAX_EMPLOYEES];
int empCount = 0;

// 🔍 Load employees from file
void loadEmployees() {
    FILE* file = fopen(FILE_NAME, "r");
    if (!file) return;

    empCount = 0;
    while (fscanf(file, "%[^|]|%[^|]|%[^|]|%f|%f|%f|%f|%f\n",
                  employees[empCount].empID,
                  employees[empCount].name,
                  employees[empCount].position,
                  &employees[empCount].basicSalary,
                  &employees[empCount].allowances,
                  &employees[empCount].deductions,
                  &employees[empCount].tax,
                  &employees[empCount].netSalary) == 8) {
        empCount++;
    }

    fclose(file);
}

// 💾 Save employees to file
void saveEmployees() {
    FILE* file = fopen(FILE_NAME, "w");
    for (int i = 0; i < empCount; i++) {
        fprintf(file, "%s|%s|%s|%.2f|%.2f|%.2f|%.2f|%.2f\n",
                employees[i].empID,
                employees[i].name,
                employees[i].position,
                employees[i].basicSalary,
                employees[i].allowances,
                employees[i].deductions,
                employees[i].tax,
                employees[i].netSalary);
    }
    fclose(file);
}

// ✅ Check for unique ID
int isUniqueID(char* id) {
    for (int i = 0; i < empCount; i++) {
        if (strcmp(employees[i].empID, id) == 0) return 0;
    }
    return 1;
}

// ➕ Add employee
void addEmployee() {
    Employee e;
    printf("Enter Employee ID: ");
    scanf("%s", e.empID);
    if (!isUniqueID(e.empID)) {
        printf("Error: Employee ID already exists.\n");
        return;
    }

    getchar(); // clear newline
    printf("Enter Full Name: ");
    fgets(e.name, sizeof(e.name), stdin);
    e.name[strcspn(e.name, "\n")] = '\0';

    printf("Enter Position: ");
    fgets(e.position, sizeof(e.position), stdin);
    e.position[strcspn(e.position, "\n")] = '\0';

    printf("Enter Basic Salary: ");
    scanf("%f", &e.basicSalary);
    printf("Enter Allowances: ");
    scanf("%f", &e.allowances);
    printf("Enter Deductions: ");
    scanf("%f", &e.deductions);

    if (e.basicSalary < 0 || e.allowances < 0 || e.deductions < 0) {
        printf("Error: Salary values must be non-negative.\n");
        return;
    }

    float gross = e.basicSalary + e.allowances - e.deductions;
    e.tax = gross * 0.10;
    e.netSalary = gross - e.tax;

    employees[empCount++] = e;
    saveEmployees();
    printf("Record added successfully!\n");
}

// 📋 View all employees
void viewEmployees() {
    loadEmployees();
    if (empCount == 0) {
        printf("No records found.\n");
        return;
    }

    printf("\n--------------------------------------------------------\n");
    printf("ID     Name                Position           Net Salary\n");
    printf("--------------------------------------------------------\n");
    for (int i = 0; i < empCount; i++) {
        printf("%-6s %-18s %-18s %.2f\n",
               employees[i].empID,
               employees[i].name,
               employees[i].position,
               employees[i].netSalary);
    }
    printf("--------------------------------------------------------\n");
}

// ✏️ Update employee
void updateEmployee() {
    char id[10];
    loadEmployees();
    printf("Enter Employee ID to update: ");
    scanf("%s", id);

    for (int i = 0; i < empCount; i++) {
        if (strcmp(employees[i].empID, id) == 0) {
            printf("Enter new Basic Salary: ");
            scanf("%f", &employees[i].basicSalary);
            printf("Enter new Allowances: ");
            scanf("%f", &employees[i].allowances);
            printf("Enter new Deductions: ");
            scanf("%f", &employees[i].deductions);

            if (employees[i].basicSalary < 0 || employees[i].allowances < 0 || employees[i].deductions < 0) {
                printf("Error: Salary values must be non-negative.\n");
                return;
            }

            float gross = employees[i].basicSalary + employees[i].allowances - employees[i].deductions;
            employees[i].tax = gross * 0.10;
            employees[i].netSalary = gross - employees[i].tax;

            saveEmployees();
            printf("Record updated successfully!\n");
            return;
        }
    }

    printf("Employee ID not found.\n");
}

// ❌ Delete employee
void deleteEmployee() {
    char id[10];
    loadEmployees();
    printf("Enter Employee ID to delete: ");
    scanf("%s", id);

    int found = 0;
    for (int i = 0; i < empCount; i++) {
        if (strcmp(employees[i].empID, id) == 0) {
            for (int j = i; j < empCount - 1; j++) {
                employees[j] = employees[j + 1];
            }
            empCount--;
            found = 1;
            break;
        }
    }

    if (found) {
        saveEmployees();
        printf("Record deleted successfully!\n");
    } else {
        printf("Employee ID not found.\n");
    }
}

// 🧾 Generate payslip
void generatePayslip() {
    char id[10];
    loadEmployees();
    printf("Enter Employee ID: ");
    scanf("%s", id);

    for (int i = 0; i < empCount; i++) {
        if (strcmp(employees[i].empID, id) == 0) {
            float gross = employees[i].basicSalary + employees[i].allowances - employees[i].deductions;
            printf("\nPayslip for %s\n", employees[i].name);
            printf("--------------------------------\n");
            printf("Basic Salary : %.2f\n", employees[i].basicSalary);
            printf("Allowances   : %.2f\n", employees[i].allowances);
            printf("Deductions   : %.2f\n", employees[i].deductions);
            printf("Gross Salary : %.2f\n", gross);
            printf("Tax (10%%)     : %.2f\n", employees[i].tax);
            printf("Net Salary   : %.2f\n", employees[i].netSalary);
            printf("--------------------------------\n");
            return;
        }
    }

    printf("Employee ID not found.\n");
}

// 📌 Main menu
int main() {
    int choice;

    do {
        printf("\nEmployee Payroll Management System\n");
        printf("1. Add Employee Record\n");
        printf("2. View All Records\n");
        printf("3. Update Employee Record\n");
        printf("4. Delete Employee Record\n");
        printf("5. Search & Generate Payslip\n");
        printf("6. Exit\n");
        printf("Enter choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1: addEmployee(); break;
            case 2: viewEmployees(); break;
            case 3: updateEmployee(); break;
            case 4: deleteEmployee(); break;
            case 5: generatePayslip(); break;
        }

    } while (choice != 6);

    return 0;
}