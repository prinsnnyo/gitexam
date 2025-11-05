import java.io.*;
import java.util.*;

class Trip {
    String tripID, route, date, time;
    int totalSeats, availableSeats;
    double fare;

    public Trip(String tripID, String route, String date, String time, int totalSeats, double fare) {
        this.tripID = tripID;
        this.route = route;
        this.date = date;
        this.time = time;
        this.totalSeats = totalSeats;
        this.availableSeats = totalSeats;
        this.fare = fare;
    }

    public String toCSV() {
        return tripID + "," + route + "," + date + "," + time + "," + totalSeats + "," + availableSeats + "," + fare;
    }

    public void display() {
        System.out.printf("%s - %s - %s %s - %d Seats Available - Fare: %.2f%n",
                tripID, route, date, time, availableSeats, fare);
    }
}

class Reservation {
    String reservationID, name, contact, tripID;
    int seatNo;
    String paymentStatus;

    public Reservation(String reservationID, String name, String contact, String tripID, int seatNo, String paymentStatus) {
        this.reservationID = reservationID;
        this.name = name;
        this.contact = contact;
        this.tripID = tripID;
        this.seatNo = seatNo;
        this.paymentStatus = paymentStatus;
    }

    public String toCSV() {
        return reservationID + "," + name + "," + contact + "," + tripID + "," + seatNo + "," + paymentStatus;
    }

    public void printTicket(Trip trip) {
        System.out.println("\n--- Transport Reservation Ticket ---");
        System.out.println("ReservationID: " + reservationID);
        System.out.println("Passenger: " + name);
        System.out.println("Trip: " + trip.route);
        System.out.println("Date: " + trip.date);
        System.out.println("Time: " + trip.time);
        System.out.println("Seat: " + seatNo);
        System.out.println("Fare: " + trip.fare);
        System.out.println("Payment: " + paymentStatus);
        System.out.println("------------------------------------");
    }
}

class TransportReservationSystem {
    static List<Trip> trips = new ArrayList<>();
    static List<Reservation> reservations = new ArrayList<>();
    static Scanner scanner = new Scanner(System.in);

    public static void main(String[] args) {
        loadTrips();
        loadReservations();
        int choice;
        do {
            System.out.println("\nTransport Reservation System");
            System.out.println("1. Add Trip");
            System.out.println("2. View Trips");
            System.out.println("3. Book Reservation");
            System.out.println("4. Cancel Reservation");
            System.out.println("5. View Reservations");
            System.out.println("6. Search Reservation");
            System.out.println("7. Exit");
            System.out.print("Enter choice: ");
            choice = scanner.nextInt();
            scanner.nextLine();

            switch (choice) {
                case 1 -> addTrip();
                case 2 -> viewTrips();
                case 3 -> bookReservation();
                case 4 -> cancelReservation();
                case 5 -> viewReservations();
                case 6 -> searchReservation();
            }
        } while (choice != 7);

        saveTrips();
        saveReservations();
    }

    static void addTrip() {
        System.out.print("TripID: ");
        String id = scanner.nextLine();
        System.out.print("Route: ");
        String route = scanner.nextLine();
        System.out.print("Date (YYYY-MM-DD): ");
        String date = scanner.nextLine();
        System.out.print("Time (HH:MM): ");
        String time = scanner.nextLine();
        System.out.print("TotalSeats: ");
        int seats = scanner.nextInt();
        System.out.print("Fare: ");
        double fare = scanner.nextDouble();
        trips.add(new Trip(id, route, date, time, seats, fare));
        System.out.println("Trip added successfully.");
    }

    static void viewTrips() {
        for (Trip t : trips) t.display();
    }

    static void bookReservation() {
        viewTrips();
        System.out.print("ReservationID: ");
        String rid = scanner.nextLine();
        System.out.print("Name: ");
        String name = scanner.nextLine();
        System.out.print("Contact: ");
        String contact = scanner.nextLine();
        if (!contact.matches("\\d+")) {
            System.out.println("Error: Contact must be numeric.");
            return;
        }
        System.out.print("TripID: ");
        String tid = scanner.nextLine();
        Trip trip = trips.stream().filter(t -> t.tripID.equals(tid)).findFirst().orElse(null);
        if (trip == null || trip.availableSeats <= 0) {
            System.out.println("Error: Trip not found or no seats available.");
            return;
        }
        System.out.print("SeatNo: ");
        int seat = scanner.nextInt();
        scanner.nextLine();
        if (reservations.stream().anyMatch(r -> r.tripID.equals(tid) && r.seatNo == seat)) {
            System.out.println("Error: Seat already booked.");
            return;
        }
        System.out.print("PaymentStatus (Paid/Unpaid): ");
        String status = scanner.nextLine();
        reservations.add(new Reservation(rid, name, contact, tid, seat, status));
        trip.availableSeats--;
        System.out.println("Reservation successful. Ticket generated.");
        reservations.get(reservations.size() - 1).printTicket(trip);
    }

    static void cancelReservation() {
        System.out.print("Enter ReservationID to cancel: ");
        String rid = scanner.nextLine();
        Reservation r = reservations.stream().filter(res -> res.reservationID.equals(rid)).findFirst().orElse(null);
        if (r != null) {
            Trip trip = trips.stream().filter(t -> t.tripID.equals(r.tripID)).findFirst().orElse(null);
            if (trip != null) trip.availableSeats++;
            reservations.remove(r);
            System.out.println("Reservation cancelled. Seat " + r.seatNo + " is now available.");
        } else {
            System.out.println("Reservation not found.");
        }
    }

    static void viewReservations() {
        for (Reservation r : reservations) {
            System.out.printf("%s - %s - Trip: %s - Seat: %d - Payment: %s%n",
                    r.reservationID, r.name, r.tripID, r.seatNo, r.paymentStatus);
        }
    }

    static void searchReservation() {
        System.out.print("Search by (1-ID, 2-Name): ");
        int opt = scanner.nextInt();
        scanner.nextLine();
        if (opt == 1) {
            System.out.print("Enter ReservationID: ");
            String rid = scanner.nextLine();
            reservations.stream()
                    .filter(r -> r.reservationID.equals(rid))
                    .forEach(r -> System.out.println("Found: " + r.name + " - Trip: " + r.tripID));
        } else {
            System.out.print("Enter Name: ");
            String name = scanner.nextLine();
            reservations.stream()
                    .filter(r -> r.name.equalsIgnoreCase(name))
                    .forEach(r -> System.out.println("Found: " + r.reservationID + " - Trip: " + r.tripID));
        }
    }

    static void loadTrips() {
        try (Scanner file = new Scanner(new File("trips.csv"))) {
            while (file.hasNextLine()) {
                String[] p = file.nextLine().split(",");
                trips.add(new Trip(p[0], p[1], p[2], p[3], Integer.parseInt(p[4]), Double.parseDouble(p[6])));
                trips.get(trips.size() - 1).availableSeats = Integer.parseInt(p[5]);
            }
        } catch (Exception ignored) {}
    }

    static void saveTrips() {
        try (PrintWriter out = new PrintWriter("trips.csv")) {
            for (Trip t : trips) out.println(t.toCSV());
        } catch (Exception ignored) {}
    }

    static void loadReservations() {
        try (Scanner file = new Scanner(new File("reservations.csv"))) {
            while (file.hasNextLine()) {
                String[] p = file.nextLine().split(",");
                reservations.add(new Reservation(p[0], p[1], p[2], p[3], Integer.parseInt(p[4]), p[5]));
            }
        } catch (Exception ignored) {}
    }

    static void saveReservations() {
        try (PrintWriter out = new PrintWriter("reservations.csv")) {
            for (Reservation r : reservations) out.println(r.toCSV());
        } catch (Exception ignored) {}
    }
}