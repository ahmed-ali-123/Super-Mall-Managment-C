#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "common.h"
#include "ui.h"

extern int *groc_ID;
extern int *groc_Quantity;
extern char (*groc_Name)[50];
extern float *groc_Price;
extern int count;
extern int capacity;

/* Throw away the rest of the current input line. */
static void discardLine(void) {
    int c;
    while ((c = getchar()) != '\n' && c != EOF) { }
}

int getValidInt(char *prompt) {
    int value;
    char term;
    while (1) {
        printf("%s", prompt);
        int r = scanf("%d%c", &value, &term);
        if (r == EOF) {                       /* input closed: don't loop forever */
            ui_error("\nInput ended. Exiting.\n");
            exit(1);
        }
        if (r == 2 && term == '\n') {
            return value;
        }
        ui_error("Invalid input! Please enter a whole number.\n");
        discardLine();
    }
}

float getValidFloat(char *prompt) {
    float value;
    char term;
    while (1) {
        printf("%s", prompt);
        int r = scanf("%f%c", &value, &term);
        if (r == EOF) {
            ui_error("\nInput ended. Exiting.\n");
            exit(1);
        }
        if (r == 2 && term == '\n') {
            return value;
        }
        ui_error("Invalid input! Please enter a valid number.\n");
        discardLine();
    }
}

void saveSystemData(void) {
    ui_info("Saving mall data...\n");
    FILE *file = fopen("SuperMallSystem.txt", "w");

    if (file == NULL) {
        ui_error("Could not open file for saving!\n");
        return;
    }

    /* First line: item count, so load knows how many records follow */
    fprintf(file, "%d\n", count);

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

    /* Read the item count (the old code skipped this line with fgets,
       so the count was lost and the first record was misread). */
    int savedCount = 0;
    if (fscanf(file, "%d", &savedCount) != 1 || savedCount < 0) {
        ui_error("Save file is empty or corrupted.\n");
        fclose(file);
        return;
    }
    if (savedCount == 0) {
        fclose(file);
        ui_info("Save file contains no grocery items.\n");
        return;
    }

    int   *ids   = malloc(savedCount * sizeof(int));
    int   *qtys  = malloc(savedCount * sizeof(int));
    char (*names)[50] = malloc(savedCount * sizeof(*names));
    float *prices = malloc(savedCount * sizeof(float));

    if (!ids || !qtys || !names || !prices) {
        ui_error("Out of memory while loading data.\n");
        free(ids); free(qtys); free(names); free(prices);
        fclose(file);
        return;
    }

    int loaded = 0;
    for (int i = 0; i < savedCount; i++) {
        int id, qty;
        char name[50];
        float price;

        if (fscanf(file, "%d %49s %d %f", &id, name, &qty, &price) == 4) {
            ids[loaded] = id;
            strcpy(names[loaded], name);
            qtys[loaded] = qty;
            prices[loaded] = price;
            loaded++;
        } else {
            break;                            /* stop at first bad record */
        }
    }
    fclose(file);

    /* Replace the current data only once the new data is safely read */
    free(groc_ID);
    free(groc_Name);
    free(groc_Quantity);
    free(groc_Price);

    groc_ID       = ids;
    groc_Name     = names;
    groc_Quantity = qtys;
    groc_Price    = prices;
    count         = loaded;
    capacity      = savedCount;

    if (loaded == savedCount)
        ui_success("Mall data loaded successfully!\n");
    else
        ui_warn("Save file damaged: loaded %d of %d items.\n", loaded, savedCount);
}
