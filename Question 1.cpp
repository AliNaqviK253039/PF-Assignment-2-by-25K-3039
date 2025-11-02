#include <stdio.h>
#include <string.h>

void addNewBook(int isbns[], char titles[][50], float prices[], int quantities[], int *bookCount);
void processSale(int isbns[], int quantities[], int bookCount);
void generateLowStockReport(int isbns[], char titles[][50], float prices[], int quantities[], int bookCount);

int main() {
    int isbns[100];
    char titles[100][50];
    float prices[100];
    int quantities[100];
    int bookCount = 0;
    int choice;

    do {
        printf("\n========== Liberty Books Inventory System ==========\n");
        printf("1. Add New Book\n");
        printf("2. Process a Sale\n");
        printf("3. Generate Low-Stock Report\n");
        printf("4. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                addNewBook(isbns, titles, prices, quantities, &bookCount);
                break;

            case 2:
                processSale(isbns, quantities, bookCount);
                break;

            case 3:
                generateLowStockReport(isbns, titles, prices, quantities, bookCount);
                break;


            case 4:
                printf("Exiting the program. Goodbye!\n");
                break;

            default:
                printf("Invalid choice. Please try again.\n");
        }
    } while (choice != 4);

    return 0;
}

void addNewBook(int isbns[], char titles[][50], float prices[], int quantities[], int *bookCount) {
    if (*bookCount >= 100) {
        printf("Inventory full! Cannot add more books.\n");
        return;
    }

    int isbn, i;
    char title[50];
    float price;
    int quantity;

    printf("\nEnter ISBN: ");
    scanf("%d", &isbn);

    for (i = 0; i < *bookCount; i++) {
        if (isbns[i] == isbn) {
            printf("Error: A book with this ISBN already exists!\n");
            return;
        }
    }

    printf("Enter Title: ");
    getchar(); 
    fgets(title, sizeof(title), stdin);
    title[strcspn(title, "\n")] = '\0'; 

    printf("Enter Price: ");
    scanf("%f", &price);

    printf("Enter Quantity: ");
    scanf("%d", &quantity);

    isbns[*bookCount] = isbn;
    strcpy(titles[*bookCount], title);
    prices[*bookCount] = price;
    quantities[*bookCount] = quantity;

    (*bookCount)++;

    printf("Book added successfully!\n");
}

void processSale(int isbns[], int quantities[], int bookCount) {
    if (bookCount == 0) {
        printf("No books available in inventory.\n");
        return;
    }

    int isbn, copiesSold, i, found = 0;

    printf("\nEnter ISBN of the book sold: ");
    scanf("%d", &isbn);

    for (i = 0; i < bookCount; i++) {
        if (isbns[i] == isbn) {
            found = 1;
            printf("Enter number of copies sold: ");
            scanf("%d", &copiesSold);

            if (copiesSold > quantities[i]) {
                printf("Error: Not enough stock! Available copies: %d\n", quantities[i]);
            } else {
                quantities[i] -= copiesSold;
                printf("Sale processed successfully! Remaining stock: %d\n", quantities[i]);
            }
            break;
        }
    }

    if (!found) {
        printf("Book with ISBN %d not found.\n", isbn);
    }
}

void generateLowStockReport(int isbns[], char titles[][50], float prices[], int quantities[], int bookCount) {
    int i, lowStockFound = 0;

    printf("\n========== Low Stock Report (Qty < 5) ==========\n");

    for (i = 0; i < bookCount; i++) {
        if (quantities[i] < 5) {
            printf("ISBN: %d | Title: %s | Price: Rs. %.2f | Quantity: %d\n",
                   isbns[i], titles[i], prices[i], quantities[i]);
            lowStockFound = 1;
        }
    }

    if (!lowStockFound) {
        printf("All books are sufficiently stocked.\n");
    }
}

