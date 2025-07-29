#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_ITEMS 100
#define FILENAME_LENGTH 50

typedef struct {
    char name[50];
    int quantity;
    float price;
} StoreItem;

void displayMenu();
void addStock();
void sellItem();
void viewStock();
void searchItem();
void exitProgram();

int main() {
    system("cls");
    printf("--------------------------------------------------------------------------\n");
    printf("\t\tWelcome to Stationary Shop Management System\n");
    printf("--------------------------------------------------------------------------\n");

    int choice;

    do {
        displayMenu();

        printf("\nEnter your choice: ");
        scanf("%d", &choice);

        switch(choice) {
            case 1:
                addStock();
                break;
            case 2:
                sellItem();
                break;
            case 3:
                viewStock();
                break;
            case 4:
                searchItem();
                break;
            case 5:
                exitProgram();
                break;
            default:
                printf("Invalid choice. Please try again.\n");
        }
    } while (choice != 5);

    return 0;
}

void displayMenu() {
    printf("\nStationary Shop Management System\n");
    printf("1. Add Stock\n");
    printf("2. Sell Item\n");
    printf("3. View Stock\n");
    printf("4. Search Item\n");
    printf("5. Exit\n");
}

void addStock() {
    system("cls");

    FILE *file;
    char filename[FILENAME_LENGTH];

    printf("\nEnter the department name: ");
    scanf("%s", filename);

    strcat(filename, ".txt");

    file = fopen(filename, "a");
    if (file == NULL) {
        printf("Error opening file.\n");
        return;
    }

    StoreItem item;

    printf("Enter details of the item to add to stock:\n");
    printf("Name: ");
    scanf("%s", item.name);
    printf("Quantity: ");
    scanf("%d", &item.quantity);
    printf("Price: ");
    scanf("%f", &item.price);

    fprintf(file, "%s %d %.2f\n", item.name, item.quantity, item.price);

    fclose(file);

    printf("Item added to stock successfully.\n");
}

void sellItem() {
    system("cls");

    FILE *file;
    char filename[FILENAME_LENGTH];
    char tempFilename[FILENAME_LENGTH];
    char itemName[50];
    char itemName1[50];
    int quantity;
    float price;
    int soldQuantity;

    printf("\nEnter the department name to sell from: ");
    scanf("%s", filename);

    strcat(filename, ".txt");
    strcpy(tempFilename, "temp.txt");

    file = fopen(filename, "r");
    if (file == NULL) {
        printf("Error opening file.\n");
        return;
    }

    FILE *tempFile = fopen(tempFilename, "w");
    if (tempFile == NULL) {
        printf("Error opening temporary file.\n");
        fclose(file);
        return;
    }

    printf("Enter the item name to sell: ");
    scanf("%s", itemName1);
    printf("Enter the quantity to sell: ");
    scanf("%d", &soldQuantity);

    int found = 0;
    while (fscanf(file, "%s %d %f", itemName, &quantity, &price) != EOF) {

        if (strcmp(itemName, itemName1) == 0) {
            if (quantity >= soldQuantity) {
                quantity -= soldQuantity;
                found = 1;
                printf("Total Price: %.2f\n",soldQuantity*price);
            } else {
                printf("Insufficient quantity in stock.\n");
            }
        }
        if (quantity > 0) {
            fprintf(tempFile, "%s %d %.2f\n", itemName, quantity, price);
        }
    }

    fclose(file);
    fclose(tempFile);

    remove(filename);
    rename(tempFilename, filename);

    if (!found) {
        printf("Item not found in stock.\n");
    } else {
        printf("Item sold successfully.\n");
    }
}

void viewStock() {
    system("cls");

    FILE *file;
    char filename[FILENAME_LENGTH];
    char name[50];
    int quantity;
    float price;

    printf("\nEnter the department name to view stock: ");
    scanf("%s", filename);

    strcat(filename, ".txt");

    file = fopen(filename, "r");
    if (file == NULL) {
        printf("Error opening file.\n");
        return;
    }

    printf("\nStock Details of %s:\n", filename);
    printf("-------------------------------------------------------------\n");
    printf("Name\t\tQuantity\tPrice\t\tTotal Price\n");
    printf("-------------------------------------------------------------\n");

    while (fscanf(file, "%s %d %f", name, &quantity, &price) != EOF) {
        printf("%s\t\t%d\t\t%.2f\t\t%.2f\n", name, quantity, price, quantity*price);
    }

    fclose(file);
}

void searchItem() {
    system("cls");

    FILE *file;
    char filename[FILENAME_LENGTH];
    char searchChar;
    char name[50];
    int quantity;
    float price;

    printf("\nEnter the department name to search in stock: ");
    scanf("%s", filename);

    strcat(filename, ".txt");

    file = fopen(filename, "r");
    if (file == NULL) {
        printf("Error opening file.\n");
        return;
    }

    printf("Enter the starting character of the item name to search: ");
    scanf(" %c", &searchChar);

    printf("\nItems in stock starting with '%c':\n", searchChar);
    printf("----------------------------------------------------------\n");
    printf("Name\t\tQuantity\tPrice\t\tTotal Price\n");
    printf("----------------------------------------------------------\n");

    while (fscanf(file, "%s %d %f", name, &quantity, &price) != EOF) {
        if (name[0] == searchChar) {
           printf("%s\t\t%d\t\t%.2f\t\t%.2f\n", name, quantity, price, quantity*price);
        }
    }

    fclose(file);
}

void exitProgram() {
    system("cls");

    printf("--------------------------------------------------------------------------\n");
    printf("\t\t\tExiting the program.\n");
    printf("--------------------------------------------------------------------------\n");
    printf("\tThank you for using our Stationary Shop Management System!\n");
    printf("--------------------------------------------------------------------------\n");
}
