#include <stdio.h>
#include <string.h>

typedef struct {
    char accNumber[10], holderName[50];
    double balance;
    void (*deposit)(double);
    void (*withdraw)(double);
    void (*display)();
} Account;

Account acc;

void deposit(double amt) {
    if (amt > 0) {
        acc.balance += amt;
        printf("Deposit successful! New Balance: %.2f\n", acc.balance);
    } else printf("Invalid deposit.\n");
}

void display() {
    printf("Account: %s | Name: %s | Balance: %.2f\n", acc.accNumber, acc.holderName, acc.balance);
}

void withdrawSavings(double amt) {
    if (acc.balance - amt >= 500) {
        acc.balance -= amt;
        printf("Withdraw successful! New Balance: %.2f\n", acc.balance);
    } else printf("Error: Minimum balance of 500 required.\n");
}

void withdrawChecking(double amt) {
    if (acc.balance - amt >= -1000) {
        acc.balance -= amt;
        printf("Withdraw successful! New Balance: %.2f\n", acc.balance);
    } else printf("Error: Overdraft limit exceeded.\n");
}

int main() {
    int type, choice;
    printf("Account Type (1-Savings, 2-Checking): "); scanf("%d", &type);
    printf("Account Number: "); scanf("%s", acc.accNumber);
    printf("Holder Name: "); getchar(); gets(acc.holderName);
    printf("Initial Balance: "); scanf("%lf", &acc.balance);

    acc.deposit = deposit;
    acc.display = display;
    acc.withdraw = (type == 1) ? withdrawSavings : withdrawChecking;

    while (1) {
        printf("\n1.Deposit 2.Withdraw 3.Display 4.Exit\nChoose: ");
        scanf("%d", &choice);
        if (choice == 1) {
            double amt; printf("Amount: "); scanf("%lf", &amt);
            acc.deposit(amt);
        } else if (choice == 2) {
            double amt; printf("Amount: "); scanf("%lf", &amt);
            acc.withdraw(amt);
        } else if (choice == 3) acc.display();
        else break;
    }
    return 0;
}