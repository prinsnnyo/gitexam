#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX 100

typedef struct {
    char id[10], name[50], status[5]; // ON/OFF
    int type; // 1=Light, 2=Fan, 3=AC
    int brightness, speed, temp;
    char mode[10]; // Cool, Heat, Fan
} Device;

Device d[MAX];
int count = 0;

void turnOn(Device *x) { strcpy(x->status, "ON"); }
void turnOff(Device *x) { strcpy(x->status, "OFF"); }

void addDevice() {
    if (count >= MAX) return;
    Device x;
    printf("Type (1-Light, 2-Fan, 3-AC): "); scanf("%d", &x.type);
    printf("ID: "); scanf("%s", x.id);
    for (int i = 0; i < count; i++)
        if (strcmp(d[i].id, x.id) == 0) { printf("ID exists.\n"); return; }
    printf("Name: "); getchar(); gets(x.name);
    strcpy(x.status, "OFF");

    if (x.type == 1) {
        printf("Brightness (0–100): "); scanf("%d", &x.brightness);
        if (x.brightness < 0 || x.brightness > 100) return;
    } else if (x.type == 2) {
        printf("Speed (1–5): "); scanf("%d", &x.speed);
        if (x.speed < 1 || x.speed > 5) return;
    } else if (x.type == 3) {
        printf("Temp (16–30): "); scanf("%d", &x.temp);
        printf("Mode (Cool/Heat/Fan): "); getchar(); gets(x.mode);
        if (x.temp < 16 || x.temp > 30) return;
    }
    d[count++] = x;
    printf("Device added successfully.\n");
}

void toggleDevice() {
    char id[10]; printf("Device ID: "); scanf("%s", id);
    for (int i = 0; i < count; i++) {
        if (strcmp(d[i].id, id) == 0) {
            printf("Action (1-ON, 2-OFF): "); int a; scanf("%d", &a);
            if (a == 1) turnOn(&d[i]);
            else turnOff(&d[i]);
            printf("%s is now %s\n", d[i].name, d[i].status);
            return;
        }
    }
    printf("Device not found.\n");
}

void adjustDevice() {
    char id[10]; printf("Device ID: "); scanf("%s", id);
    for (int i = 0; i < count; i++) {
        if (strcmp(d[i].id, id) == 0) {
            if (d[i].type == 1) {
                printf("New Brightness (0–100): "); scanf("%d", &d[i].brightness);
            } else if (d[i].type == 2) {
                printf("New Speed (1–5): "); scanf("%d", &d[i].speed);
            } else if (d[i].type == 3) {
                printf("New Temp (16–30): "); scanf("%d", &d[i].temp);
                printf("New Mode: "); getchar(); gets(d[i].mode);
            }
            printf("Settings updated.\n");
            return;
        }
    }
    printf("Device not found.\n");
}

void viewDevices() {
    for (int i = 0; i < count; i++) {
        printf("[%s] %s - %s", d[i].id, d[i].name, d[i].status);
        if (d[i].type == 1) printf(", Brightness: %d\n", d[i].brightness);
        else if (d[i].type == 2) printf(", Speed: %d\n", d[i].speed);
        else printf(", Temp: %d, Mode: %s\n", d[i].temp, d[i].mode);
    }
}

void saveDevices() {
    FILE *f = fopen("devices.txt", "w");
    for (int i = 0; i < count; i++)
        fprintf(f, "%s|%s|%s|%d|%d|%d|%d|%s\n", d[i].id, d[i].name, d[i].status,
                d[i].type, d[i].brightness, d[i].speed, d[i].temp, d[i].mode);
    fclose(f);
    printf("Devices saved to devices.txt\n");
}

void loadDevices() {
    FILE *f = fopen("devices.txt", "r"); count = 0;
    if (!f) { printf("No file found.\n"); return; }
    while (fscanf(f, "%[^|]|%[^|]|%[^|]|%d|%d|%d|%d|%[^\n]\n",
           d[count].id, d[count].name, d[count].status, &d[count].type,
           &d[count].brightness, &d[count].speed, &d[count].temp, d[count].mode) == 8)
        count++;
    fclose(f);
    printf("Devices loaded from devices.txt\n");
}

void scheduleAction() {
    char id[10]; printf("Device ID: "); scanf("%s", id);
    char time[20]; printf("Schedule (e.g., Turn ON at 7:00 PM): "); getchar(); gets(time);
    for (int i = 0; i < count; i++)
        if (strcmp(d[i].id, id) == 0) {
            printf("%s will be %s\n", d[i].name, time);
            return;
        }
    printf("Device not found.\n");
}

int main() {
    int ch;
    while (1) {
        printf("\n1.Add 2.Toggle 3.Adjust 4.View 5.Save 6.Load 7.Schedule 8.Exit\nChoose: ");
        scanf("%d", &ch);
        if (ch == 1) addDevice();
        else if (ch == 2) toggleDevice();
        else if (ch == 3) adjustDevice();
        else if (ch == 4) viewDevices();
        else if (ch == 5) saveDevices();
        else if (ch == 6) loadDevices();
        else if (ch == 7) scheduleAction();
        else break;
    }
    return 0;
}