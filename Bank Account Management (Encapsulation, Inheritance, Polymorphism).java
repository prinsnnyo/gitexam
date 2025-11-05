import java.util.*;

abstract class Account {
    private String accountNumber;
    private String holderName;
    protected double balance;

    public Account(String accountNumber, String holderName, double balance) {
        this.accountNumber = accountNumber;
        this.holderName = holderName;
        this.balance = balance;
    }

    public String getAccountNumber() {
        return accountNumber;
    }

    public void deposit(double amount) {
        if (amount > 0) {
            balance += amount;
            System.out.printf("Deposit successful! New Balance: %.2f%n", balance);
        } else {
            System.out.println("Error: Deposit must be positive.");
        }
    }

    public abstract void withdraw(double amount);

    public void displayAccountInfo() {
        System.out.println("\nAccount Info:");
        System.out.println("Account Number : " + accountNumber);
        System.out.println("Holder Name    : " + holderName);
        System.out.printf("Balance        : %.2f%n", balance);
    }
}

class SavingsAccount extends Account {
    public SavingsAccount(String accountNumber, String holderName, double balance) {
        super(accountNumber, holderName, balance);
    }

    @Override
    public void withdraw(double amount) {
        if (amount <= 0) {
            System.out.println("Error: Withdrawal must be positive.");
        } else if (balance - amount >= 500) {
            balance -= amount;
            System.out.printf("Withdrawal successful! New Balance: %.2f%n", balance);
        } else {
            System.out.println("Error: Minimum balance of 500 must be maintained.");
        }
    }
}

class CheckingAccount extends Account {
    public CheckingAccount(String accountNumber, String holderName, double balance) {
        super(accountNumber, holderName, balance);
    }

    @Override
    public void withdraw(double amount) {
        if (amount <= 0) {
            System.out.println("Error: Withdrawal must be positive.");
        } else if (balance - amount >= -1000) {
            balance -= amount;
            System.out.printf("Withdrawal successful! New Balance: %.2f%n", balance);
        } else {
            System.out.println("Error: Overdraft limit of -1000 exceeded.");
        }
    }
}

class BankSystem {
    private static final Scanner scanner = new Scanner(System.in);
    private static final List<Account> accounts = new ArrayList<>();

    public static void main(String[] args) {
        int choice;
        do {
            System.out.println("\nBank Account Management System");
            System.out.println("1. Create New Account");
            System.out.println("2. Deposit");
            System.out.println("3. Withdraw");
            System.out.println("4. Display Account Info");
            System.out.println("5. Exit");
            System.out.print("Enter choice: ");
            choice = scanner.nextInt();
            scanner.nextLine(); // clear newline

            switch (choice) {
                case 1 -> createAccount();
                case 2 -> deposit();
                case 3 -> withdraw();
                case 4 -> displayInfo();
            }
        } while (choice != 5);
    }

    private static void createAccount() {
        System.out.print("Enter Account Type (1-Savings, 2-Checking): ");
        int type = scanner.nextInt();
        scanner.nextLine();

        System.out.print("Enter Account Number: ");
        String accNum = scanner.nextLine();

        System.out.print("Enter Holder Name: ");
        String name = scanner.nextLine();

        System.out.print("Enter Initial Balance: ");
        double balance = scanner.nextDouble();

        Account account = switch (type) {
            case 1 -> new SavingsAccount(accNum, name, balance);
            case 2 -> new CheckingAccount(accNum, name, balance);
            default -> null;
        };

        if (account != null) {
            accounts.add(account);
            System.out.println((type == 1 ? "Savings" : "Checking") + " Account created successfully!");
        } else {
            System.out.println("Invalid account type.");
        }
    }

    private static Account findAccount(String accNum) {
        for (Account acc : accounts) {
            if (acc.getAccountNumber().equals(accNum)) {
                return acc;
            }
        }
        return null;
    }

    private static void deposit() {
        System.out.print("Enter Account Number: ");
        String accNum = scanner.nextLine();
        Account acc = findAccount(accNum);
        if (acc != null) {
            System.out.print("Enter Deposit Amount: ");
            double amount = scanner.nextDouble();
            acc.deposit(amount);
        } else {
            System.out.println("Error: Account not found.");
        }
    }

    private static void withdraw() {
        System.out.print("Enter Account Number: ");
        String accNum = scanner.nextLine();
        Account acc = findAccount(accNum);
        if (acc != null) {
            System.out.print("Enter Withdraw Amount: ");
            double amount = scanner.nextDouble();
            acc.withdraw(amount);
        } else {
            System.out.println("Error: Account not found.");
        }
    }

    private static void displayInfo() {
        System.out.print("Enter Account Number: ");
        String accNum = scanner.nextLine();
        Account acc = findAccount(accNum);
        if (acc != null) {
            acc.displayAccountInfo();
        } else {
            System.out.println("Error: Account not found.");
        }
    }
}