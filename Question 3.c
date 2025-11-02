#include <stdio.h>

// Bit flag masks
#define POWER_ON        1   
#define OVERLOAD        2   
#define MAINTENANCE     4  

void updateSectorStatus(int grid[5][5], int rows, int cols);
void querySectorStatus(int grid[5][5], int rows, int cols);
void runSystemDiagnostic(int grid[5][5], int rows, int cols);
void displayMenu();

int main() {
    int grid[5][5] = {0};  // 5x5 grid initialized with all bits = 0 (all OFF/Normal)
    int choice;
    int rows = 5, cols = 5;

    do {
        displayMenu();
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                updateSectorStatus(grid, rows, cols);
                break;
            case 2:
                querySectorStatus(grid, rows, cols);
                break;
            case 3:
                runSystemDiagnostic(grid, rows, cols);
                break;
            case 4:
                printf("Exiting system... Goodbye!\n");
                break;
            default:
                printf("Invalid choice. Please try again.\n");
        }

    } while (choice != 4);

    return 0;
}

void displayMenu() {
    printf("\n========== IESCO Power Grid Monitoring System ==========\n");
    printf("1. Update Sector Status\n");
    printf("2. Query Sector Status\n");
    printf("3. Run System Diagnostic\n");
    printf("4. Exit\n");
    printf("========================================================\n");
}

void updateSectorStatus(int grid[5][5], int rows, int cols) {
    int row, col, flag, action;

    printf("\nEnter Sector Coordinates (Row and Column): ");
    scanf("%d %d", &row, &col);

    if (row < 0 || row >= rows || col < 0 || col >= cols) {
        printf("Invalid coordinates!\n");
        return;
    }

    printf("Select Status Flag to Modify:\n");
    printf("1. Power Status (ON/OFF)\n");
    printf("2. Overload Warning (Set/Clear)\n");
    printf("3. Maintenance Required (Set/Clear)\n");
    printf("Enter flag number: ");
    scanf("%d", &flag);

    printf("Choose Action: 1 = Set, 0 = Clear: ");
    scanf("%d", &action);

    int bitmask;
    switch (flag) {
        case 1: bitmask = POWER_ON; break;
        case 2: bitmask = OVERLOAD; break;
        case 3: bitmask = MAINTENANCE; break;
        default:
            printf("Invalid flag!\n");
            return;
    }

    if (action == 1)
        grid[row][col] |= bitmask;    
    else
        grid[row][col] &= ~bitmask;    

    printf("Sector (%d, %d) updated successfully!\n", row, col);
}

void querySectorStatus(int grid[5][5], int rows, int cols) {
    int row, col;
    printf("\nEnter Sector Coordinates (Row and Column): ");
    scanf("%d %d", &row, &col);

    if (row < 0 || row >= rows || col < 0 || col >= cols) {
        printf("Invalid coordinates!\n");
        return;
    }

    int value = grid[row][col];

    printf("\nSector (%d, %d) Status Report:\n", row, col);
    printf("---------------------------------\n");
    printf("Power Status:        %s\n", (value & POWER_ON) ? "ON" : "OFF");
    printf("Overload Warning:    %s\n", (value & OVERLOAD) ? "OVERLOADED" : "NORMAL");
    printf("Maintenance Required:%s\n", (value & MAINTENANCE) ? "YES" : "NO");
}

void runSystemDiagnostic(int grid[5][5], int rows, int cols) {
    int overloadCount = 0;
    int maintenanceCount = 0;
    int i, j;
    for (i = 0; i < rows; i++) {
        for ( j = 0; j < cols; j++) {
            if (grid[i][j] & OVERLOAD)
                overloadCount++;
            if (grid[i][j] & MAINTENANCE)
                maintenanceCount++;
        }
    }

    printf("\n========== System Diagnostic Report ==========\n");
    printf("Total Sectors: %d\n", rows * cols);
    printf("Overloaded Sectors: %d\n", overloadCount);
    printf("Sectors Requiring Maintenance: %d\n", maintenanceCount);
    printf("==============================================\n");
}

