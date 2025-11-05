#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX 100

typedef struct {
    char id[10], name[50], spec[30], slots[5][10]; // up to 5 slots
    int slotCount;
} Doctor;

typedef struct {
    char id[10], name[50], contact[15];
} Patient;

typedef struct {
    char id[10], patID[10], docID[10], date[15], slot[10], status[15];
} Appointment;

Doctor docs[MAX]; int docCount = 0;
Patient pats[MAX]; int patCount = 0;
Appointment apps[MAX]; int appCount = 0;

void loadDoctors() {
    FILE *f = fopen("doctors.txt", "r"); docCount = 0;
    if (!f) return;
    while (fscanf(f, "%[^|]|%[^|]|%[^|]|%d|%[^|]|%[^|]|%[^|]|%[^|]|%[^\n]\n",
           docs[docCount].id, docs[docCount].name, docs[docCount].spec, &docs[docCount].slotCount,
           docs[docCount].slots[0], docs[docCount].slots[1], docs[docCount].slots[2],
           docs[docCount].slots[3], docs[docCount].slots[4]) >= 4)
        docCount++;
    fclose(f);
}

void saveDoctors() {
    FILE *f = fopen("doctors.txt", "w");
    for (int i = 0; i < docCount; i++) {
        fprintf(f, "%s|%s|%s|%d", docs[i].id, docs[i].name, docs[i].spec, docs[i].slotCount);
        for (int j = 0; j < docs[i].slotCount; j++)
            fprintf(f, "|%s", docs[i].slots[j]);
        fprintf(f, "\n");
    }
    fclose(f);
}

void loadPatients() {
    FILE *f = fopen("patients.txt", "r"); patCount = 0;
    if (!f) return;
    while (fscanf(f, "%[^|]|%[^|]|%[^\n]\n", pats[patCount].id, pats[patCount].name, pats[patCount].contact) == 3)
        patCount++;
    fclose(f);
}

void savePatients() {
    FILE *f = fopen("patients.txt", "w");
    for (int i = 0; i < patCount; i++)
        fprintf(f, "%s|%s|%s\n", pats[i].id, pats[i].name, pats[i].contact);
    fclose(f);
}

void loadAppointments() {
    FILE *f = fopen("appointments.txt", "r"); appCount = 0;
    if (!f) return;
    while (fscanf(f, "%[^|]|%[^|]|%[^|]|%[^|]|%[^|]|%[^\n]\n",
           apps[appCount].id, apps[appCount].patID, apps[appCount].docID,
           apps[appCount].date, apps[appCount].slot, apps[appCount].status) == 6)
        appCount++;
    fclose(f);
}

void saveAppointments() {
    FILE *f = fopen("appointments.txt", "w");
    for (int i = 0; i < appCount; i++)
        fprintf(f, "%s|%s|%s|%s|%s|%s\n", apps[i].id, apps[i].patID, apps[i].docID,
                apps[i].date, apps[i].slot, apps[i].status);
    fclose(f);
}

int findDoctor(char *id) {
    for (int i = 0; i < docCount; i++)
        if (strcmp(docs[i].id, id) == 0) return i;
    return -1;
}

int findPatient(char *id) {
    for (int i = 0; i < patCount; i++)
        if (strcmp(pats[i].id, id) == 0) return i;
    return -1;
}

int slotBooked(char *docID, char *date, char *slot) {
    for (int i = 0; i < appCount; i++)
        if (strcmp(apps[i].docID, docID) == 0 &&
            strcmp(apps[i].date, date) == 0 &&
            strcmp(apps[i].slot, slot) == 0 &&
            strcmp(apps[i].status, "Scheduled") == 0)
            return 1;
    return 0;
}

void addDoctor() {
    Doctor d;
    printf("DoctorID: "); scanf("%s", d.id);
    if (findDoctor(d.id) >= 0) { printf("ID exists.\n"); return; }
    printf("Name: "); getchar(); gets(d.name);
    printf("Specialization: "); gets(d.spec);
    printf("Number of Slots (max 5): "); scanf("%d", &d.slotCount);
    for (int i = 0; i < d.slotCount; i++) {
        printf("Slot %d: ", i + 1); scanf("%s", d.slots[i]);
    }
    docs[docCount++] = d;
    saveDoctors();
    printf("Doctor added successfully.\n");
}

void registerPatient() {
    Patient p;
    printf("PatientID: "); scanf("%s", p.id);
    if (findPatient(p.id) >= 0) { printf("ID exists.\n"); return; }
    printf("Name: "); getchar(); gets(p.name);
    printf("Contact: "); gets(p.contact);
    for (int i = 0; p.contact[i]; i++)
        if (p.contact[i] < '0' || p.contact[i] > '9') { printf("Invalid contact.\n"); return; }
    pats[patCount++] = p;
    savePatients();
    printf("Patient registered successfully.\n");
}

void bookAppointment() {
    Appointment a;
    printf("AppointmentID: "); scanf("%s", a.id);
    for (int i = 0; i < appCount; i++)
        if (strcmp(apps[i].id, a.id) == 0) { printf("ID exists.\n"); return; }
    printf("PatientID: "); scanf("%s", a.patID);
    if (findPatient(a.patID) < 0) { printf("Patient not found.\n"); return; }
    printf("DoctorID: "); scanf("%s", a.docID);
    int d = findDoctor(a.docID);
    if (d < 0) { printf("Doctor not found.\n"); return; }
    printf("Date (YYYY-MM-DD): "); scanf("%s", a.date);
    printf("TimeSlot: "); scanf("%s", a.slot);
    if (slotBooked(a.docID, a.date, a.slot)) { printf("Slot already booked.\n"); return; }
    strcpy(a.status, "Scheduled");
    apps[appCount++] = a;
    saveAppointments();
    printf("Appointment scheduled successfully.\n");
}

void cancelAppointment() {
    char id[10]; printf("Cancel Appointment: "); scanf("%s", id);
    for (int i = 0; i < appCount; i++) {
        if (strcmp(apps[i].id, id) == 0) {
            strcpy(apps[i].status, "Cancelled");
            saveAppointments();
            printf("Appointment cancelled. Slot is now available.\n");
            return;
        }
    }
    printf("Appointment not found.\n");
}

void viewSchedule() {
    char docID[10]; printf("DoctorID: "); scanf("%s", docID);
    int d = findDoctor(docID);
    if (d < 0) { printf("Doctor not found.\n"); return; }
    printf("Appointments for %s\n", docs[d].name);
    for (int i = 0; i < docs[d].slotCount; i++) {
        int booked = 0;
        for (int j = 0; j < appCount; j++) {
            if (strcmp(apps[j].docID, docID) == 0 &&
                strcmp(apps[j].slot, docs[d].slots[i]) == 0 &&
                strcmp(apps[j].status, "Scheduled") == 0) {
                int p = findPatient(apps[j].patID);
                printf("%s - Booked (%s)\n", docs[d].slots[i], pats[p].name);
                booked = 1;
                break;
            }
        }
        if (!booked) printf("%s - Available\n", docs[d].slots[i]);
    }
}

int main() {
    loadDoctors(); loadPatients(); loadAppointments();
    int ch;
    while (1) {
        printf("\n1.Add Doctor 2.Register Patient 3.Book 4.Cancel 5.View Schedule 6.Exit\nChoose: ");
        scanf("%d", &ch);
        if (ch == 1)
            addDoctor();
        else if (ch == 2)
            registerPatient();
        else if (ch == 3)
            bookAppointment();
        else if (ch == 4)
            cancelAppointment();
        else if (ch == 5)
            viewSchedule();
        else
            break;
    }
    return 0;
}