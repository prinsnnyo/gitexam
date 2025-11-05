import java.io.*;
import java.util.*;

// 🔹 Base Class: Device
abstract class Device {
    private String deviceID;
    private String deviceName;
    private boolean status;

    public Device(String id, String name) {
        this.deviceID = id;
        this.deviceName = name;
        this.status = false;
    }

    public String getDeviceID() { return deviceID; }
    public String getDeviceName() { return deviceName; }
    public boolean isOn() { return status; }

    public void turnOn() { status = true; }
    public void turnOff() { status = false; }

    public abstract String getStatus();
    public abstract String toCSV();
    public abstract void display();
}

// 🔹 Light Device
class Light extends Device {
    private int brightness;

    public Light(String id, String name, int brightness) {
        super(id, name);
        this.brightness = brightness;
    }

    public void setBrightness(int level) {
        if (level >= 0 && level <= 100) this.brightness = level;
    }

    @Override
    public String getStatus() {
        return (isOn() ? "ON" : "OFF") + ", Brightness: " + brightness;
    }

    @Override
    public String toCSV() {
        return "Light," + getDeviceID() + "," + getDeviceName() + "," + isOn() + "," + brightness;
    }

    @Override
    public void display() {
        System.out.printf("[%s] %s - %s%n", getDeviceID(), getDeviceName(), getStatus());
    }
}

// 🔹 Fan Device
class Fan extends Device {
    private int speed;

    public Fan(String id, String name, int speed) {
        super(id, name);
        this.speed = speed;
    }

    public void setSpeed(int level) {
        if (level >= 1 && level <= 5) this.speed = level;
    }

    @Override
    public String getStatus() {
        return (isOn() ? "ON" : "OFF") + ", Speed: " + speed;
    }

    @Override
    public String toCSV() {
        return "Fan," + getDeviceID() + "," + getDeviceName() + "," + isOn() + "," + speed;
    }

    @Override
    public void display() {
        System.out.printf("[%s] %s - %s%n", getDeviceID(), getDeviceName(), getStatus());
    }
}

// 🔹 AC Device
class AC extends Device {
    private int temperature;
    private String mode;

    public AC(String id, String name, int temp, String mode) {
        super(id, name);
        this.temperature = temp;
        this.mode = mode;
    }

    public void setTemperature(int temp) {
        if (temp >= 16 && temp <= 30) this.temperature = temp;
    }

    public void setMode(String mode) {
        if (mode.equalsIgnoreCase("Cool") || mode.equalsIgnoreCase("Heat") || mode.equalsIgnoreCase("Fan"))
            this.mode = mode;
    }

    @Override
    public String getStatus() {
        return (isOn() ? "ON" : "OFF") + ", Temp: " + temperature + ", Mode: " + mode;
    }

    @Override
    public String toCSV() {
        return "AC," + getDeviceID() + "," + getDeviceName() + "," + isOn() + "," + temperature + "," + mode;
    }

    @Override
    public void display() {
        System.out.printf("[%s] %s - %s%n", getDeviceID(), getDeviceName(), getStatus());
    }
}

// 🔹 Controller Class
class SmartHomeController {
    private static final List<Device> devices = new ArrayList<>();
    private static final Scanner scanner = new Scanner(System.in);

    public static void main(String[] args) {
        int choice;
        do {
            System.out.println("\nSmart Home Controller");
            System.out.println("1. Add Device");
            System.out.println("2. Toggle Device ON/OFF");
            System.out.println("3. Adjust Device Settings");
            System.out.println("4. View All Devices");
            System.out.println("5. Save Devices");
            System.out.println("6. Load Devices");
            System.out.println("7. Exit");
            System.out.print("Enter choice: ");
            choice = scanner.nextInt();
            scanner.nextLine();

            switch (choice) {
                case 1 -> addDevice();
                case 2 -> toggleDevice();
                case 3 -> adjustSettings();
                case 4 -> viewDevices();
                case 5 -> saveDevices();
                case 6 -> loadDevices();
            }
        } while (choice != 7);
    }

    private static Device findDevice(String id) {
        return devices.stream().filter(d -> d.getDeviceID().equals(id)).findFirst().orElse(null);
    }

    private static void addDevice() {
        System.out.print("Enter Device Type (1-Light, 2-Fan, 3-AC): ");
        int type = scanner.nextInt();
        scanner.nextLine();

        System.out.print("Enter Device ID: ");
        String id = scanner.nextLine();
        System.out.print("Enter Device Name: ");
        String name = scanner.nextLine();

        switch (type) {
            case 1 -> {
                System.out.print("Enter Brightness (0–100): ");
                int brightness = scanner.nextInt();
                devices.add(new Light(id, name, brightness));
            }
            case 2 -> {
                System.out.print("Enter Speed (1–5): ");
                int speed = scanner.nextInt();
                devices.add(new Fan(id, name, speed));
            }
            case 3 -> {
                System.out.print("Enter Temperature (16–30): ");
                int temp = scanner.nextInt();
                scanner.nextLine();
                System.out.print("Enter Mode (Cool/Heat/Fan): ");
                String mode = scanner.nextLine();
                devices.add(new AC(id, name, temp, mode));
            }
        }
        System.out.println("Device added successfully.");
    }

    private static void toggleDevice() {
        System.out.print("Enter Device ID: ");
        String id = scanner.nextLine();
        Device d = findDevice(id);
        if (d != null) {
            System.out.print("Action (1-ON, 2-OFF): ");
            int action = scanner.nextInt();
            if (action == 1) d.turnOn();
            else d.turnOff();
            System.out.println(d.getDeviceName() + " is now " + (d.isOn() ? "ON" : "OFF"));
        } else {
            System.out.println("Device not found.");
        }
    }

    private static void adjustSettings() {
        System.out.print("Enter Device ID: ");
        String id = scanner.nextLine();
        Device d = findDevice(id);
        if (d instanceof Light l) {
            System.out.print("Enter new Brightness (0–100): ");
            l.setBrightness(scanner.nextInt());
        } else if (d instanceof Fan f) {
            System.out.print("Enter new Speed (1–5): ");
            f.setSpeed(scanner.nextInt());
        } else if (d instanceof AC ac) {
            System.out.print("Enter new Temperature (16–30): ");
            int temp = scanner.nextInt();
            scanner.nextLine();
            System.out.print("Enter new Mode (Cool/Heat/Fan): ");
            String mode = scanner.nextLine();
            ac.setTemperature(temp);
            ac.setMode(mode);
        } else {
            System.out.println("Device not found or unsupported.");
        }
    }

    private static void viewDevices() {
        if (devices.isEmpty()) {
            System.out.println("No devices found.");
            return;
        }
        for (Device d : devices) d.display();
    }

    private static void saveDevices() {
        try (PrintWriter writer = new PrintWriter("devices.txt")) {
            for (Device d : devices) {
                writer.println(d.toCSV());
            }
            System.out.println("Devices saved successfully to devices.txt");
        } catch (IOException e) {
            System.out.println("Error saving devices.");
        }
    }

    private static void loadDevices() {
        devices.clear();
        try (Scanner fileScanner = new Scanner(new File("devices.txt"))) {
            while (fileScanner.hasNextLine()) {
                String[] parts = fileScanner.nextLine().split(",");
                String type = parts[0], id = parts[1], name = parts[2];
                boolean status = Boolean.parseBoolean(parts[3]);

                switch (type) {
                    case "Light" -> {
                        Light l = new Light(id, name, Integer.parseInt(parts[4]));
                        if (status) l.turnOn();
                        devices.add(l);
                    }
                    case "Fan" -> {
                        Fan f = new Fan(id, name, Integer.parseInt(parts[4]));
                        if (status) f.turnOn();
                        devices.add(f);
                    }
                    case "AC" -> {
                        AC ac = new AC(id, name, Integer.parseInt(parts[4]), parts[5]);
                        if (status) ac.turnOn();
                        devices.add(ac);
                    }
                }
            }
            System.out.println("Devices loaded successfully from devices.txt");
        } catch (IOException e) {
            System.out.println("Error loading devices.");
        }
    }
}