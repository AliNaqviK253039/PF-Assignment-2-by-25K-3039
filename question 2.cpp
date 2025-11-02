#include <stdio.h>
#include <string.h>

#define MAX_PRODUCTS 4
#define MAX_CART 10

struct Product {
    char code[10];
    int quantity;
    float price;
};

struct CartItem {
    char code[10];
    int quantity;
    float price;
};

struct Customer {
    char name[50];
    char cnic[20];
};

void getCustomerInfo(struct Customer *cust);
void displayInventory(struct Product products[], int count);
void addToCart(struct Product products[], int count, struct CartItem cart[], int *cartCount);
void updateInventory(struct Product products[], int count, struct CartItem cart[], int cartCount);
float displayTotalBill(struct CartItem cart[], int cartCount);
void showInvoice(struct Customer cust, struct CartItem cart[], int cartCount, float total);

int main() {
    struct Product products[MAX_PRODUCTS] = {
        {"001", 50, 100},
        {"002", 10, 200},
        {"003", 20, 300},
        {"004", 8, 150}
    };

    struct CartItem cart[MAX_CART];
    struct Customer customer;
    int cartCount = 0;
    int choice;
    float totalBill = 0.0;

    do {
        printf("\n================= SUPERMARKET MANAGEMENT SYSTEM =================\n");
        printf("1. Enter Customer Information\n");
        printf("2. Display Inventory\n");
        printf("3. Add Item to Cart\n");
        printf("4. Display Total Bill\n");
        printf("5. Show Invoice\n");
        printf("6. Exit\n");
        printf("=================================================================\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                getCustomerInfo(&customer);
                break;

            case 2:
                displayInventory(products, MAX_PRODUCTS);
                break;

            case 3:
                addToCart(products, MAX_PRODUCTS, cart, &cartCount);
                break;

            case 4:
                totalBill = displayTotalBill(cart, cartCount);
                updateInventory(products, MAX_PRODUCTS, cart, cartCount);
                break;

            case 5:
                showInvoice(customer, cart, cartCount, totalBill);
                break;

            case 6:
                printf("Exiting the system. Thank you for shopping!\n");
                break;

            default:
                printf("Invalid choice! Please try again.\n");
        }

    } while (choice != 6);

    return 0;
}

void getCustomerInfo(struct Customer *cust) {
    printf("\nEnter Customer Name: ");
    getchar(); // to clear newline
    fgets(cust->name, sizeof(cust->name), stdin);
    cust->name[strcspn(cust->name, "\n")] = '\0'; // remove newline

    printf("Enter CNIC Number: ");
    fgets(cust->cnic, sizeof(cust->cnic), stdin);
    cust->cnic[strcspn(cust->cnic, "\n")] = '\0';

    printf("Customer information saved successfully!\n");
}

void displayInventory(struct Product products[], int count) {
    printf("\n-------------------- INVENTORY --------------------\n");
    printf("Product Code\tQuantity\tPrice per Product\n");
    printf("--------------------------------------------------\n");
    for (int i = 0; i < count; i++) {
        printf("%s\t\t%d\t\t%.2f\n", products[i].code, products[i].quantity, products[i].price);
    }
}

void addToCart(struct Product products[], int count, struct CartItem cart[], int *cartCount) {
    char code[10];
    int quantity, found = 0;

    printf("\nEnter Product Code to Add: ");
    scanf("%s", code);

    for (int i = 0; i < count; i++) {
        if (strcmp(products[i].code, code) == 0) {
            found = 1;
            printf("Enter Quantity: ");
            scanf("%d", &quantity);

            if (quantity > products[i].quantity) {
                printf("Error: Only %d items in stock.\n", products[i].quantity);
                return;
            }

            strcpy(cart[*cartCount].code, code);
            cart[*cartCount].quantity = quantity;
            cart[*cartCount].price = products[i].price;
            (*cartCount)++;

            printf("Item added to cart successfully!\n");
            return;
        }
    }

    if (!found)
        printf("Product not found!\n");
}

void updateInventory(struct Product products[], int count, struct CartItem cart[], int cartCount) {
    for (int i = 0; i < cartCount; i++) {
        for (int j = 0; j < count; j++) {
            if (strcmp(cart[i].code, products[j].code) == 0) {
                products[j].quantity -= cart[i].quantity;
            }
        }
    }
}

float displayTotalBill(struct CartItem cart[], int cartCount) {
    float total = 0.0, discount = 0.0;
    char promo[20];

    printf("\n-------------------- BILL DETAILS --------------------\n");
    printf("Product Code\tQuantity\tPrice\tSubtotal\n");
    printf("------------------------------------------------------\n");

    for (int i = 0; i < cartCount; i++) {
        float subtotal = cart[i].quantity * cart[i].price;
        total += subtotal;
        printf("%s\t\t%d\t\t%.2f\t%.2f\n", cart[i].code, cart[i].quantity, cart[i].price, subtotal);
    }

    printf("------------------------------------------------------\n");
    printf("Total Bill: Rs. %.2f\n", total);

    printf("Do you have a promo code (Eid2025)? Enter code or 'no': ");
    scanf("%s", promo);

    if (strcmp(promo, "Eid2025") == 0) {
        discount = total * 0.25;
        total -= discount;
        printf("Promo code applied! 25%% discount: Rs. %.2f\n", discount);
    } else {
        printf("No promo code applied.\n");
    }

    printf("Final Bill: Rs. %.2f\n", total);
    return total;
}

void showInvoice(struct Customer cust, struct CartItem cart[], int cartCount, float total) {
    printf("\n===================== INVOICE =====================\n");
    printf("Customer Name: %s\n", cust.name);
    printf("Customer CNIC: %s\n", cust.cnic);
    printf("--------------------------------------------------\n");
    printf("Product Code\tQuantity\tPrice\tSubtotal\n");

    for (int i = 0; i < cartCount; i++) {
        float subtotal = cart[i].quantity * cart[i].price;
        printf("%s\t\t%d\t\t%.2f\t%.2f\n", cart[i].code, cart[i].quantity, cart[i].price, subtotal);
    }

    printf("--------------------------------------------------\n");
    printf("Total Payable Amount: Rs. %.2f\n", total);
    printf("==================================================\n");
}

