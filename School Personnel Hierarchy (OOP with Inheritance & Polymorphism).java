import java.util.*;

// 🔹 Abstract Base Class: Person
abstract class Person {
    private String id;
    private String name;
    private int age;

    public Person(String id, String name, int age) {
        this.id = id;
        this.name = name;
        this.age = age;
    }

    public String getId() { return id; }
    public String getName() { return name; }
    public int getAge() { return age; }

    public abstract void introduce();
}

// 🔹 Teacher Class
class Teacher extends Person {
    private String subject;

    public Teacher(String id, String name, int age, String subject) {
        super(id, name, age);
        this.subject = subject;
    }

    @Override
    public void introduce() {
        System.out.println("ID: " + getId() + " - I am " + getName() + ", a Teacher of " + subject + ".");
    }

    public void gradeStudent() {
        System.out.println(getName() + " has graded a student.");
    }
}

// 🔹 Student Class
class Student extends Person {
    private String course;
    private int yearLevel;

    public Student(String id, String name, int age, String course, int yearLevel) {
        super(id, name, age);
        this.course = course;
        this.yearLevel = yearLevel;
    }

    @Override
    public void introduce() {
        System.out.println("ID: " + getId() + " - I am " + getName() + ", a " + yearLevel + "nd year student of " + course + ".");
    }

    public void submitAssignment() {
        System.out.println(getName() + " has submitted an assignment.");
    }
}

// 🔹 AdminStaff Class
class AdminStaff extends Person {
    private String department;

    public AdminStaff(String id, String name, int age, String department) {
        super(id, name, age);
        this.department = department;
    }

    @Override
    public void introduce() {
        System.out.println("ID: " + getId() + " - I am " + getName() + ", working in the " + department + " department.");
    }

    public void processDocument() {
        System.out.println(getName() + " has processed a document.");
    }
}

// 🔹 PersonnelManager Class
class PersonnelManager {
    private static final Scanner scanner = new Scanner(System.in);
    private static final List<Person> personnelList = new ArrayList<>();

    public static void main(String[] args) {
        int choice;
        do {
            System.out.println("\n===== School Personnel Management System =====");
            System.out.println("1. Add Teacher");
            System.out.println("2. Add Student");
            System.out.println("3. Add Admin Staff");
            System.out.println("4. View All Personnel");
            System.out.println("5. Role-Specific Action");
            System.out.println("6. Exit");
            System.out.print("Enter choice: ");
            choice = scanner.nextInt();
            scanner.nextLine(); // clear newline

            switch (choice) {
                case 1 -> addTeacher();
                case 2 -> addStudent();
                case 3 -> addAdmin();
                case 4 -> viewAll();
                case 5 -> roleAction();
            }
        } while (choice != 6);
    }

    private static boolean isUniqueID(String id) {
        return personnelList.stream().noneMatch(p -> p.getId().equals(id));
    }

    private static void addTeacher() {
        System.out.print("ID: ");
        String id = scanner.nextLine();
        if (!isUniqueID(id)) {
            System.out.println("Error: ID already exists.");
            return;
        }

        System.out.print("Name: ");
        String name = scanner.nextLine();
        System.out.print("Age: ");
        int age = scanner.nextInt();
        scanner.nextLine();
        if (age <= 0) {
            System.out.println("Error: Age must be positive.");
            return;
        }

        System.out.print("Subject: ");
        String subject = scanner.nextLine();

        personnelList.add(new Teacher(id, name, age, subject));
        System.out.println("Teacher added successfully.");
    }

    private static void addStudent() {
        System.out.print("ID: ");
        String id = scanner.nextLine();
        if (!isUniqueID(id)) {
            System.out.println("Error: ID already exists.");
            return;
        }

        System.out.print("Name: ");
        String name = scanner.nextLine();
        System.out.print("Age: ");
        int age = scanner.nextInt();
        scanner.nextLine();
        if (age <= 0) {
            System.out.println("Error: Age must be positive.");
            return;
        }

        System.out.print("Course: ");
        String course = scanner.nextLine();
        System.out.print("Year Level: ");
        int year = scanner.nextInt();
        scanner.nextLine();

        personnelList.add(new Student(id, name, age, course, year));
        System.out.println("Student added successfully.");
    }

    private static void addAdmin() {
        System.out.print("ID: ");
        String id = scanner.nextLine();
        if (!isUniqueID(id)) {
            System.out.println("Error: ID already exists.");
            return;
        }

        System.out.print("Name: ");
        String name = scanner.nextLine();
        System.out.print("Age: ");
        int age = scanner.nextInt();
        scanner.nextLine();
        if (age <= 0) {
            System.out.println("Error: Age must be positive.");
            return;
        }

        System.out.print("Department: ");
        String dept = scanner.nextLine();

        personnelList.add(new AdminStaff(id, name, age, dept));
        System.out.println("Admin Staff added successfully.");
    }

    private static void viewAll() {
        if (personnelList.isEmpty()) {
            System.out.println("No personnel records found.");
            return;
        }
        System.out.println("\nPersonnel List:");
        for (Person p : personnelList) {
            p.introduce();
        }
    }

    private static void roleAction() {
        System.out.print("Enter Personnel ID: ");
        String id = scanner.nextLine();
        for (Person p : personnelList) {
            if (p.getId().equals(id)) {
                if (p instanceof Teacher t) {
                    t.gradeStudent();
                } else if (p instanceof Student s) {
                    s.submitAssignment();
                } else if (p instanceof AdminStaff a) {
                    a.processDocument();
                }
                return;
            }
        }
        System.out.println("Error: ID not found.");
    }
}