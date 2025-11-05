#include <stdio.h>
#include <string.h>

#define MAX 100

typedef struct {
    char id[10], name[50];
    double price;
    int type; // 1=Electronics, 2=Clothing, 3=Grocery
    double (*getFinalPrice)(double, int);
} Product;

Product cart[MAX];
int count = 0;

double finalPrice(double price, int type) {
    if (type == 1) return price * 0.90;             // Electronics: 10% off
    if (type == 2) return price > 1000 ? price * 0.80 : price; // Clothing: 20% off if >1000
    return price;                                   // Grocery: no discount
}

void addProduct() {
    if (count >= MAX) { printf("Cart full.\n"); return; }
    Product p;
    printf("Type (1-Elec, 2-Cloth, 3-Groc): "); scanf("%d", &p.type);
    printf("ID: "); scanf("%s", p.id);
    for (int i = 0; i < count; i++)
        if (strcmp(cart[i].id, p.id) == 0) { printf("ID exists.\n"); return; }
    printf("Name: "); getchar(); gets(p.name);
    printf("Price: "); scanf("%lf", &p.price);
    if (p.price <= 0) { printf("Invalid price.\n"); return; }
    p.getFinalPrice = finalPrice;
    cart[count++] = p;
    printf("Product added: %s\n", p.name);
}

void removeProduct() {
    char id[10]; printf("ID to remove: "); scanf("%s", id);
    for (int i = 0; i < count; i++) {
        if (strcmp(cart[i].id, id) == 0) {
            for (int j = i; j < count - 1; j++) cart[j] = cart[j + 1];
            count--; printf("Removed.\n"); return;
        }
    }
    printf("Not found.\n");
}

void displayCart() {
    if (count == 0) { printf("Cart empty.\n"); return; }
    for (int i = 0; i < count; i++) {
        double final = cart[i].getFinalPrice(cart[i].price, cart[i].type);
        printf("%s - %s - Original: %.2f | Final: %.2f\n",
               cart[i].id, cart[i].name, cart[i].price, final);
    }
}

void checkout() {
    double total = 0;
    for (int i = 0; i < count; i++)
        total += cart[i].getFinalPrice(cart[i].price, cart[i].type);
    printf("Total Amount to Pay: %.2f\n", total);
}

int main() {
    int ch;
    while (1) {
        printf("\n1.Add 2.Remove 3.Display 4.Checkout 5.Exit\nChoose: ");
        scanf("%d", &ch);
        if (ch == 1) addProduct();
        else if (ch == 2) removeProduct();
        else if (ch == 3) displayCart();
        else if (ch == 4) checkout();
        else break;
    }
    return 0;
}