#include <stdio.h>
#include "common.h"
#include "ui.h"
#include <stdlib.h>
#include <string.h>
extern int *groc_ID;
extern int *groc_Quantity;
extern char (*groc_Name)[50];
extern float *groc_Price;
extern int count;
extern int capacity;
int getValidInt(char *prompt) {
    int value;
    char term;
    while (1) {
        printf("%s", prompt);
        if (scanf("%d%c", &value, &term) != 2 || term != '\n') {
            ui_error("Invalid input! Please enter a whole number.\n");
            while (getchar() != '\n');
        } else {
            return value;
        }
    }
}


float getValidFloat(char *prompt) {
    float value;
    char term;
    while (1) {
        printf("%s", prompt);
        if (scanf("%f%c", &value, &term) != 2 || term != '\n') {
            ui_error("Invalid input! Please enter a valid number.\n");
            while (getchar() != '\n');
        } else {
            return value;
        }
    }
}

void saveSystemData(void) {
     ui_info("Saving mall data...\n");
    FILE *file = fopen("SuperMallSystem.txt", "w");
    
    if (file == NULL) {
        ui_error("Could not open file for saving!\n");
        return;
    }

    // 2. Write the total item count first so load knows how many to read
    fprintf(file, "%d\n", count);

    // 3. Loop through your parallel arrays and write each item
    for (int i = 0; i < count; i++) {
        fprintf(file, "%d %s %d %.2f\n", 
                groc_ID[i], 
                groc_Name[i], 
                groc_Quantity[i], 
                groc_Price[i]);
    }

    
    fclose(file);
    ui_success("Mall data saved to 'SuperMallSystem.txt'\n");
}
    
void loadSystemData(void) {
    ui_info("Loading mall data...\n");
    FILE *file = fopen("SuperMallSystem.txt", "r");

    if (file == NULL) {
        ui_warn("No previous save file found. Starting fresh!\n");
        return;
    }

    // 1. Read and ignore the version line
    char buffer[100];
    fgets(buffer, sizeof(buffer), file);

    // 2. Read the total item count saved in the file
    int savedCount = 0;
    if (fscanf(file, "%d", &savedCount) != 1 || savedCount <= 0) {
        ui_error("Save file is empty or corrupted.\n");
        fclose(file);
        return;
    }

    // 3. Free any old memory and allocate fresh memory for the parallel arrays
    free(groc_ID);
    free(groc_Name);
    free(groc_Quantity);
    free(groc_Price);

    groc_ID = malloc(savedCount * sizeof(int));
    groc_Quantity = malloc(savedCount * sizeof(int));
    groc_Name = malloc(savedCount * sizeof(*groc_Name));
    groc_Price = malloc(savedCount * sizeof(float));

    capacity = savedCount;
    count = 0;

    // 4. Read each item back into your parallel arrays
    for (int i = 0; i < savedCount; i++) {
        int id, qty;
        char name[50];
        float price;

        if (fscanf(file, "%d %49s %d %f", &id, name, &qty, &price) == 4) {
            groc_ID[count] = id;
            strcpy(groc_Name[count], name);
            groc_Quantity[count] = qty;
            groc_Price[count] = price;
            count++;
        }
    }

    fclose(file);
    ui_success("Mall data loaded successfully!\n");
}