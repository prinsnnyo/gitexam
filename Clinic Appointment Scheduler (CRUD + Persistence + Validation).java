import java.io.*;
import java.util.*;

class Doctor {
    String doctorID, name, specialization;
    List<String> availableSlots;

    public Doctor(String doctorID, String name, String specialization, List<String> slots) {
        this.doctorID = doctorID;
        this.name = name;
        this.specialization = specialization;
        this.availableSlots = slots;
    }

    public String toCSV() {
        return doctorID + "," + name + "," + specialization + "," + String.join(";", availableSlots);
    }
}

class Patient {
    String patientID, name, contact;

    public Patient(String patientID, String name, String contact) {
        this.patientID = patientID;
        this.name = name;
        this.contact = contact;
    }

    public String toCSV() {
        return patientID + "," + name + "," + contact;
    }
}

class Appointment {
    String appointmentID, patientID, doctorID, date, timeSlot, status;

    public Appointment(String appointmentID, String patientID, String doctorID, String date, String timeSlot, String status) {
        this.appointmentID = appointmentID;
        this.patientID = patientID;
        this.doctorID = doctorID;
        this.date = date;
        this.timeSlot = timeSlot;
        this.status = status;
    }

    public String toCSV() {
        return appointmentID + "," + patientID + "," + doctorID + "," + date + "," + timeSlot + "," + status;
    }
}

class ClinicScheduler {
    static List<Doctor> doctors = new ArrayList<>();
    static List<Patient> patients = new ArrayList<>();
    static List<Appointment> appointments = new ArrayList<>();
    static Scanner scanner = new Scanner(System.in);

    public static void main(String[] args) {
        loadDoctors();
        loadPatients();
        loadAppointments();
        int choice;
        do {
            System.out.println("\nClinic Appointment Scheduler");
            System.out.println("1. Add Doctor");
            System.out.println("2. Register Patient");
            System.out.println("3. Book Appointment");
            System.out.println("4. Cancel Appointment");
            System.out.println("5. View Doctor Schedule");
            System.out.println("6. Mark Appointment Completed");
            System.out.println("7. Exit");
            System.out.print("Enter choice: ");
            choice = scanner.nextInt(); scanner.nextLine();

            switch (choice) {
                case 1 -> addDoctor();
                case 2 -> registerPatient();
                case 3 -> bookAppointment();
                case 4 -> cancelAppointment();
                case 5 -> viewSchedule();
                case 6 -> completeAppointment();
            }
        } while (choice != 7);

        saveDoctors();
        savePatients();
        saveAppointments();
    }

    static void addDoctor() {
        System.out.print("DoctorID: ");
        String id = scanner.nextLine();
        System.out.print("Name: ");
        String name = scanner.nextLine();
        System.out.print("Specialization: ");
        String spec = scanner.nextLine();
        System.out.print("Available Slots (comma-separated): ");
        String[] slots = scanner.nextLine().split(",");
        doctors.add(new Doctor(id, name, spec, Arrays.asList(slots)));
        System.out.println("Doctor added successfully.");
    }

    static void registerPatient() {
        System.out.print("PatientID: ");
        String id = scanner.nextLine();
        System.out.print("Name: ");
        String name = scanner.nextLine();
        System.out.print("Contact: ");
        String contact = scanner.nextLine();
        if (!contact.matches("\\d+")) {
            System.out.println("Error: Contact must be numeric.");
            return;
        }
        patients.add(new Patient(id, name, contact));
        System.out.println("Patient registered successfully.");
    }

    static void bookAppointment() {
        System.out.print("AppointmentID: ");
        String aid = scanner.nextLine();
        System.out.print("PatientID: ");
        String pid = scanner.nextLine();
        System.out.print("DoctorID: ");
        String did = scanner.nextLine();
        System.out.print("Date (YYYY-MM-DD): ");
        String date = scanner.nextLine();
        System.out.print("TimeSlot: ");
        String slot = scanner.nextLine();

        if (appointments.stream().anyMatch(a -> a.doctorID.equals(did) && a.date.equals(date) && a.timeSlot.equals(slot) && a.status.equals("Scheduled"))) {
            System.out.println("Error: Slot already booked.");
            return;
        }

        appointments.add(new Appointment(aid, pid, did, date, slot, "Scheduled"));
        System.out.println("Appointment scheduled successfully.");
    }

    static void cancelAppointment() {
        System.out.print("Enter AppointmentID to cancel: ");
        String aid = scanner.nextLine();
        for (Appointment a : appointments) {
            if (a.appointmentID.equals(aid)) {
                a.status = "Cancelled";
                System.out.println("Appointment cancelled. Slot is now available.");
                return;
            }
        }
        System.out.println("Appointment not found.");
    }

    static void viewSchedule() {
        System.out.print("Enter DoctorID: ");
        String did = scanner.nextLine();
        Doctor doc = doctors.stream().filter(d -> d.doctorID.equals(did)).findFirst().orElse(null);
        if (doc == null) {
            System.out.println("Doctor not found.");
            return;
        }
        System.out.println("Appointments for " + doc.name);
        for (String slot : doc.availableSlots) {
            Appointment a = appointments.stream().filter(ap -> ap.doctorID.equals(did) && ap.timeSlot.equals(slot) && ap.status.equals("Scheduled")).findFirst().orElse(null);
            if (a != null) {
                Patient p = patients.stream().filter(pa -> pa.patientID.equals(a.patientID)).findFirst().orElse(null);
                System.out.println(slot + " - Booked (" + (p != null ? p.name : "Unknown") + ")");
            } else {
                System.out.println(slot + " - Available");
            }
        }
    }

    static void completeAppointment() {
        System.out.print("Enter AppointmentID to mark completed: ");
        String aid = scanner.nextLine();
        for (Appointment a : appointments) {
            if (a.appointmentID.equals(aid)) {
                a.status = "Completed";
                System.out.println("Appointment marked as completed.");
                return;
            }
        }
        System.out.println("Appointment not found.");
    }

    static void loadDoctors() {
        try (Scanner file = new Scanner(new File("doctors.csv"))) {
            while (file.hasNextLine()) {
                String[] p = file.nextLine().split(",");
                doctors.add(new Doctor(p[0], p[1], p[2], Arrays.asList(p[3].split(";"))));
            }
        } catch (Exception ignored) {}
    }

    static void saveDoctors() {
        try (PrintWriter out = new PrintWriter("doctors.csv")) {
            for (Doctor d : doctors) out.println(d.toCSV());
        } catch (Exception ignored) {}
    }

    static void loadPatients() {
        try (Scanner file = new Scanner(new File("patients.csv"))) {
            while (file.hasNextLine()) {
                String[] p = file.nextLine().split(",");
                patients.add(new Patient(p[0], p[1], p[2]));
            }
        } catch (Exception ignored) {}
    }

    static void savePatients() {
        try (PrintWriter out = new PrintWriter("patients.csv")) {
            for (Patient p : patients) out.println(p.toCSV());
        } catch (Exception ignored) {}
    }

    static void loadAppointments() {
        try (Scanner file = new Scanner(new File("appointments.csv"))) {
            while (file.hasNextLine()) {
                String[] p = file.nextLine().split(",");
                appointments.add(new Appointment(p[0], p[1], p[2], p[3], p[4], p[5]));
            }
        } catch (Exception ignored) {}
    }

    static void saveAppointments() {
        try (PrintWriter out = new PrintWriter("appointments.csv")) {
            for (Appointment a : appointments) out.println(a.toCSV());
        } catch (Exception ignored) {}
    }
}