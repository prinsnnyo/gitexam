import java.util.*;

// 🔹 Base Class: Product
abstract class Product {
    private String productID;
    private String productName;
    private double price;

    public Product(String productID, String productName, double price) {
        this.productID = productID;
        this.productName = productName;
        this.price = price;
    }

    public String getProductID() { return productID; }
    public String getProductName() { return productName; }
    public double getPrice() { return price; }

    public abstract double getFinalPrice();

    public void displayProductInfo() {
        System.out.printf("%s - %s - Original: %.2f | Final Price: %.2f%n",
                productID, productName, price, getFinalPrice());
    }
}

// 🔹 Electronics: 10% discount
class Electronics extends Product {
    public Electronics(String id, String name, double price) {
        super(id, name, price);
    }

    @Override
    public double getFinalPrice() {
        return getPrice() * 0.90;
    }
}

// 🔹 Clothing: 20% off if price > 1000
class Clothing extends Product {
    public Clothing(String id, String name, double price) {
        super(id, name, price);
    }

    @Override
    public double getFinalPrice() {
        return getPrice() > 1000 ? getPrice() * 0.80 : getPrice();
    }
}

// 🔹 Grocery: No discount
class Grocery extends Product {
    public Grocery(String id, String name, double price) {
        super(id, name, price);
    }

    @Override
    public double getFinalPrice() {
        return getPrice();
    }
}

// 🔹 ShoppingCart Class
class ShoppingCart {
    private final List<Product> cart = new ArrayList<>();

    public void addProduct(Product p) {
        for (Product prod : cart) {
            if (prod.getProductID().equals(p.getProductID())) {
                System.out.println("Error: Product ID already exists in cart.");
                return;
            }
        }
        cart.add(p);
        System.out.println("Product added: " + p.getProductName());
    }

    public void removeProduct(String productID) {
        Iterator<Product> iterator = cart.iterator();
        while (iterator.hasNext()) {
            if (iterator.next().getProductID().equals(productID)) {
                iterator.remove();
                System.out.println("Product removed.");
                return;
            }
        }
        System.out.println("Error: Product ID not found.");
    }

    public void displayCart() {
        if (cart.isEmpty()) {
            System.out.println("Cart is empty.");
            return;
        }
        System.out.println("Cart Contents:");
        for (Product p : cart) {
            p.displayProductInfo();
        }
    }

    public void checkout() {
        double total = 0;
        for (Product p : cart) {
            total += p.getFinalPrice();
        }
        System.out.printf("Total Amount to Pay: %.2f%n", total);
    }
}

// 🔹 Main Program
class ShoppingCartSystem {
    public static void main(String[] args) {
        try (Scanner scanner = new Scanner(System.in)) {
            ShoppingCart cart = new ShoppingCart();
            int choice;

            do {
                System.out.println("\n1. Add Product");
                System.out.println("2. Remove Product");
                System.out.println("3. Display Cart");
                System.out.println("4. Checkout");
                System.out.println("5. Exit");
                System.out.print("Enter choice: ");
                choice = scanner.nextInt();
                scanner.nextLine(); // clear newline

                switch (choice) {
                    case 1 -> {
                        System.out.print("Enter Product Type (1-Electronics, 2-Clothing, 3-Grocery): ");
                        int type = scanner.nextInt();
                        scanner.nextLine();

                        System.out.print("Enter Product ID: ");
                        String id = scanner.nextLine();

                        System.out.print("Enter Product Name: ");
                        String name = scanner.nextLine();

                        System.out.print("Enter Price: ");
                        double price = scanner.nextDouble();

                        if (price <= 0) {
                            System.out.println("Error: Price must be positive.");
                            continue;
                        }

                        Product p = switch (type) {
                            case 1 -> new Electronics(id, name, price);
                            case 2 -> new Clothing(id, name, price);
                            case 3 -> new Grocery(id, name, price);
                            default -> null;
                        };

                        if (p != null) {
                            cart.addProduct(p);
                        } else {
                            System.out.println("Invalid product type.");
                        }
                    }
                    case 2 -> {
                        System.out.print("Enter Product ID to remove: ");
                        String id = scanner.nextLine();
                        cart.removeProduct(id);
                    }
                    case 3 -> cart.displayCart();
                    case 4 -> cart.checkout();
                }
            } while (choice != 5);
        }
    }
}