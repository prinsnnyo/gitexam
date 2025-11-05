#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define MAX 1000

typedef struct {
    char id[10], name[50], pos[30];
    float basic, allow, deduct, tax, net;
} Emp;

Emp e[MAX]; int n;

void load() {
    FILE *f = fopen("payroll.txt", "r"); n = 0;
    if (!f) return;
    while (fscanf(f, "%[^|]|%[^|]|%[^|]|%f|%f|%f|%f|%f\n", e[n].id, e[n].name, e[n].pos,
           &e[n].basic, &e[n].allow, &e[n].deduct, &e[n].tax, &e[n].net) == 8) n++;
    fclose(f);
}

void save() {
    FILE *f = fopen("payroll.txt", "w");
    for (int i = 0; i < n; i++)
        fprintf(f, "%s|%s|%s|%.2f|%.2f|%.2f|%.2f|%.2f\n", e[i].id, e[i].name, e[i].pos,
                e[i].basic, e[i].allow, e[i].deduct, e[i].tax, e[i].net);
    fclose(f);
}

void calc(Emp *x) {
    float gross = x->basic + x->allow - x->deduct;
    x->tax = gross * 0.10;
    x->net = gross - x->tax;
}

void add() {
    load(); Emp t;
    printf("ID: "); gets(t.id);
    for (int i = 0; i < n; i++) if (!strcmp(e[i].id, t.id)) { printf("ID exists.\n"); return; }
    printf("Name: "); gets(t.name);
    printf("Position: "); gets(t.pos);
    printf("Basic: "); scanf("%f", &t.basic);
    printf("Allowances: "); scanf("%f", &t.allow);
    printf("Deductions: "); scanf("%f", &t.deduct); getchar();
    if (t.basic < 0 || t.allow < 0 || t.deduct < 0) { printf("Invalid salary.\n"); return; }
    calc(&t);
    FILE *f = fopen("payroll.txt", "a");
    fprintf(f, "%s|%s|%s|%.2f|%.2f|%.2f|%.2f|%.2f\n", t.id, t.name, t.pos,
            t.basic, t.allow, t.deduct, t.tax, t.net);
    fclose(f); printf("Added!\n");
}

void view() {
    load(); if (!n) { printf("No records.\n"); return; }
    printf("ID Name Position Net\n-----------------------------\n");
    for (int i = 0; i < n; i++)
        printf("%s %s %s %.2f\n", e[i].id, e[i].name, e[i].pos, e[i].net);
}

void update() {
    load(); char id[10]; printf("ID to update: "); gets(id);
    for (int i = 0; i < n; i++) {
        if (!strcmp(e[i].id, id)) {
            printf("New Basic: "); scanf("%f", &e[i].basic);
            printf("New Allow: "); scanf("%f", &e[i].allow);
            printf("New Deduct: "); scanf("%f", &e[i].deduct); getchar();
            if (e[i].basic < 0 || e[i].allow < 0 || e[i].deduct < 0) { printf("Invalid.\n"); return; }
            calc(&e[i]); save(); printf("Updated!\n"); return;
        }
    }
    printf("ID not found.\n");
}

void del() {
    load(); char id[10]; printf("ID to delete: "); gets(id);
    for (int i = 0; i < n; i++) {
        if (!strcmp(e[i].id, id)) {
            for (int j = i; j < n - 1; j++) e[j] = e[j + 1];
            n--; save(); printf("Deleted!\n"); return;
        }
    }
    printf("ID not found.\n");
}

void payslip() {
    load(); char id[10]; printf("ID to search: "); gets(id);
    for (int i = 0; i < n; i++) {
        if (!strcmp(e[i].id, id)) {
            float gross = e[i].basic + e[i].allow - e[i].deduct;
            printf("\nPayslip for %s\n----------------------\n", e[i].name);
            printf("Basic: %.2f\nAllow: %.2f\nDeduct: %.2f\n", e[i].basic, e[i].allow, e[i].deduct);
            printf("Gross: %.2f\nTax: %.2f\nNet: %.2f\n----------------------\n",
                   gross, e[i].tax, e[i].net);
            return;
        }
    }
    printf("ID not found.\n");
}

int main() {
    int c;
    while (1) {
        printf("\n1.Add 2.View 3.Update 4.Delete 5.Payslip 6.Exit\nChoose: ");
        scanf("%d", &c); getchar();
        if (c == 1) add(); else if (c == 2) view();
        else if (c == 3) update(); else if (c == 4) del();
        else if (c == 5) payslip(); else break;
    }
    return 0;
}