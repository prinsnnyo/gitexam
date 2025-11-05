#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX 100

typedef struct {
    char tripID[10], route[50], date[15], time[10];
    int totalSeats, availableSeats, fare;
} Trip;

typedef struct {
    char resID[10], name[50], contact[15], tripID[10];
    int seatNo;
    char status[10]; // Paid/Unpaid
} Reservation;

Trip trips[MAX]; int tripCount = 0;
Reservation res[MAX]; int resCount = 0;

void loadTrips() {
    FILE *f = fopen("trips.txt", "r"); tripCount = 0;
    if (!f) return;
    while (fscanf(f, "%[^|]|%[^|]|%[^|]|%[^|]|%d|%d|%d\n",
           trips[tripCount].tripID, trips[tripCount].route, trips[tripCount].date,
           trips[tripCount].time, &trips[tripCount].totalSeats,
           &trips[tripCount].availableSeats, &trips[tripCount].fare) == 7)
        tripCount++;
    fclose(f);
}

void saveTrips() {
    FILE *f = fopen("trips.txt", "w");
    for (int i = 0; i < tripCount; i++)
        fprintf(f, "%s|%s|%s|%s|%d|%d|%d\n", trips[i].tripID, trips[i].route,
                trips[i].date, trips[i].time, trips[i].totalSeats,
                trips[i].availableSeats, trips[i].fare);
    fclose(f);
}

void loadRes() {
    FILE *f = fopen("res.txt", "r"); resCount = 0;
    if (!f) return;
    while (fscanf(f, "%[^|]|%[^|]|%[^|]|%[^|]|%d|%[^\n]\n",
           res[resCount].resID, res[resCount].name, res[resCount].contact,
           res[resCount].tripID, &res[resCount].seatNo, res[resCount].status) == 6)
        resCount++;
    fclose(f);
}

void saveRes() {
    FILE *f = fopen("res.txt", "w");
    for (int i = 0; i < resCount; i++)
        fprintf(f, "%s|%s|%s|%s|%d|%s\n", res[i].resID, res[i].name, res[i].contact,
                res[i].tripID, res[i].seatNo, res[i].status);
    fclose(f);
}

int findTrip(char *id) {
    for (int i = 0; i < tripCount; i++)
        if (strcmp(trips[i].tripID, id) == 0) return i;
    return -1;
}

int seatTaken(char *tripID, int seat) {
    for (int i = 0; i < resCount; i++)
        if (strcmp(res[i].tripID, tripID) == 0 && res[i].seatNo == seat)
            return 1;
    return 0;
}

void addTrip() {
    Trip t;
    printf("TripID: "); scanf("%s", t.tripID);
    if (findTrip(t.tripID) >= 0) { printf("Trip exists.\n"); return; }
    printf("Route: "); getchar(); gets(t.route);
    printf("Date: "); gets(t.date);
    printf("Time: "); gets(t.time);
    printf("TotalSeats: "); scanf("%d", &t.totalSeats);
    printf("Fare: "); scanf("%d", &t.fare);
    t.availableSeats = t.totalSeats;
    trips[tripCount++] = t;
    saveTrips();
    printf("Trip added successfully.\n");
}

void viewTrips() {
    for (int i = 0; i < tripCount; i++)
        printf("%s - %s - %d Seats Available - Fare: %d\n",
               trips[i].tripID, trips[i].route, trips[i].availableSeats, trips[i].fare);
}

void bookSeat() {
    Reservation r;
    printf("ReservationID: "); scanf("%s", r.resID);
    printf("Name: "); getchar(); gets(r.name);
    printf("Contact: "); gets(r.contact);
    for (int i = 0; r.contact[i]; i++)
        if (r.contact[i] < '0' || r.contact[i] > '9') { printf("Invalid contact.\n"); return; }
    printf("TripID: "); gets(r.tripID);
    int i = findTrip(r.tripID);
    if (i < 0) { printf("Trip not found.\n"); return; }
    if (trips[i].availableSeats <= 0) { printf("No seats available.\n"); return; }
    printf("SeatNo: "); scanf("%d", &r.seatNo); getchar();
    if (seatTaken(r.tripID, r.seatNo)) { printf("Seat taken.\n"); return; }
    printf("PaymentStatus: "); gets(r.status);
    res[resCount++] = r;
    trips[i].availableSeats--;
    saveRes(); saveTrips();
    printf("Reservation successful. Ticket generated.\n");
    printf("--- Transport Reservation Ticket ---\n");
    printf("ReservationID: %s\nPassenger: %s\nTrip: %s\nDate: %s\nTime: %s\nSeat: %d\nFare: %d\nPayment: %s\n",
           r.resID, r.name, trips[i].route, trips[i].date, trips[i].time, r.seatNo, trips[i].fare, r.status);
    printf("------------------------------------\n");
}

void cancelRes() {
    char id[10]; printf("Cancel Reservation: "); scanf("%s", id);
    for (int i = 0; i < resCount; i++) {
        if (strcmp(res[i].resID, id) == 0) {
            int t = findTrip(res[i].tripID);
            if (t >= 0) trips[t].availableSeats++;
            for (int j = i; j < resCount - 1; j++) res[j] = res[j + 1];
            resCount--; saveRes(); saveTrips();
            printf("Reservation cancelled. Seat %d is now available.\n", res[i].seatNo);
            return;
        }
    }
    printf("Reservation not found.\n");
}

void viewResByTrip() {
    char id[10]; printf("TripID: "); scanf("%s", id);
    for (int i = 0; i < resCount; i++)
        if (strcmp(res[i].tripID, id) == 0)
            printf("%s - %s - Seat: %d - %s\n", res[i].resID, res[i].name, res[i].seatNo, res[i].status);
}

void searchRes() {
    char q[50]; printf("Search Name or ResID: "); getchar(); gets(q);
    for (int i = 0; i < resCount; i++)
        if (strstr(res[i].name, q) || strstr(res[i].resID, q))
            printf("%s - %s - Trip: %s - Seat: %d\n", res[i].resID, res[i].name, res[i].tripID, res[i].seatNo);
}

int main() {
    loadTrips(); loadRes();
    int ch;
    while (1) {
        printf("\n1.Add Trip 2.View Trips 3.Book 4.Cancel 5.View Res by Trip 6.Search Res 7.Exit\nChoose: ");
        scanf("%d", &ch);
        if (ch == 1) addTrip();
        else if (ch == 2) viewTrips();
        else if (ch == 3) bookSeat();
        else if (ch == 4) cancelRes();
        else if (ch == 5) viewResByTrip();
        else if (ch == 6) searchRes();
        else break;
    }
    return 0;
}