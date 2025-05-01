#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "types.h"
#include "console_list.h"
#include "bid_stack.h"

#define MAX_BUFFER 255

void new(char *commandNumber, char command, char *consoleId, char *userId, char *consoleBrand, char *consolePrice, tList *L) {
    tItemL item;

    printf("********************\n");
    double price = atof(consolePrice);
    printf("%s %c: console %s seller %s brand %s price %.2f\n", commandNumber, command, consoleId, userId, consoleBrand, price);

    if (findItem(consoleId, *L) != LNULL) {
        printf("+ Error: New not possible\n");
        return;
    }

    strcpy(item.consoleId, consoleId);
    strcpy(item.seller, userId);

    if(strcmp(consoleBrand, "nintendo") == 0) {
        item.consoleBrand = nintendo;
    } else if (strcmp(consoleBrand, "sega") == 0) {
        item.consoleBrand = sega;
    } else {
        printf("+ Error: New not possible\n");
        return;
    }

    item.consolePrice = price;
    item.bidCounter = 0;
    createEmptyStack(&item.bidStack);

    if (insertItem(item, L)) {
        printf("* New: console %s seller %s brand %s price %.2f\n", consoleId, userId, consoleBrand, price);
    } else {
        printf("+ Error: New not possible\n");
    }
}

void bid(char *commandNumber, char command, char *consoleId, char *userId, char *newPriceStr, tList *L) {
    printf("********************\n");
    double newPrice = atof(newPriceStr);
    printf("%s %c: console %s bidder %s price %.2f\n", commandNumber, command, consoleId, userId, newPrice);

    tPosL pos = findItem(consoleId, *L);
    if (pos == LNULL) {
        printf("+ Error: Bid not possible\n");
        return;
    }

    tItemL item = getItem(pos, *L);

    if (strcmp(item.seller, userId) == 0) {
        printf("+ Error: Bid not possible\n");
        return;
    }

    double minPrice = item.consolePrice;
    if (!isEmptyStack(item.bidStack)) {
        tItemS topBid = peek(item.bidStack);
        minPrice = topBid.consolePrice;
    }

    if (newPrice <= minPrice) {
        printf("+ Error: Bid not possible\n");
        return;
    }

    tItemS newBid;
    strcpy(newBid.bidder, userId);
    newBid.consolePrice = newPrice;

    if (!push(newBid, &item.bidStack)) {
        printf("+ Error: Bid not possible\n");
        return;
    }

    item.bidCounter++;
    updateItem(item, pos, L);

    printf("* Bid: console %s bidder %s brand %s price %.2f bids %d\n",
           item.consoleId, userId,
           (item.consoleBrand == nintendo) ? "nintendo" : "sega",
           newPrice, item.bidCounter);
}

void stats(char *commandNumber, char command, tList *L) {
    printf("********************\n");
    printf("%s %c\n", commandNumber, command);

    if (isEmptyList(*L)) {
        printf("+ Error: Stats not possible\n");
        return;
    }

    tPosL p;
    int nintendoCount = 0, segaCount = 0;
    double nintendoTotal = 0.0, segaTotal = 0.0;
    double maxIncrease = -1.0;
    tItemL topItem;
    tItemS topBid;
    bool hasBids = false;

    for (p = first(*L); p != LNULL; p = next(p, *L)) {
        tItemL item = getItem(p, *L);

        printf("Console %s seller %s brand %s price %.2f",
               item.consoleId, item.seller,
               (item.consoleBrand == nintendo) ? "nintendo" : "sega",
               item.consolePrice);

        if (!isEmptyStack(item.bidStack)) {
            tItemS top = peek(item.bidStack);
            printf(" bids %d top bidder %s\n", item.bidCounter, top.bidder);

            float increase = ((top.consolePrice - item.consolePrice) / item.consolePrice) * 100.0;

            if (increase > maxIncrease) {
                maxIncrease = increase;
                topItem = item;
                topBid = top;
            }
            hasBids = true;
        } else {
            printf(". No bids\n");
        }

        if (item.consoleBrand == nintendo) {
            nintendoCount++;
            nintendoTotal += item.consolePrice;
        } else {
            segaCount++;
            segaTotal += item.consolePrice;
        }
    }

    printf("\nBrand     Consoles    Price  Average\n");
    printf("Nintendo  %8d %8.2f %8.2f\n",
           nintendoCount, nintendoTotal,
           (nintendoCount > 0) ? nintendoTotal / nintendoCount : 0.0);
    printf("Sega      %8d %8.2f %8.2f\n",
           segaCount, segaTotal,
           (segaCount > 0) ? segaTotal / segaCount : 0.0);

    if (hasBids) {
        printf("Top bid: console %s seller %s brand %s price %.2f bidder %s top price %.2f increase %.2f%%\n",
               topItem.consoleId, topItem.seller,
               (topItem.consoleBrand == nintendo) ? "nintendo" : "sega",
               topItem.consolePrice, topBid.bidder, topBid.consolePrice, maxIncrease);
    } else {
        printf("Top bid not possible\n");
    }
}

void deleteConsole(char *commandNumber, char command, char *consoleId, tList *L) {
    printf("********************\n");
    printf("%s %c: console %s\n", commandNumber, command, consoleId);

    tPosL pos = findItem(consoleId, *L);
    if (pos == LNULL) {
        printf("+ Error: Delete not possible\n");
        return;
    }

    tItemL item = getItem(pos, *L);

    printf("* Delete: console %s seller %s brand %s price %.2f",
           item.consoleId, item.seller,
           (item.consoleBrand == nintendo) ? "nintendo" : "sega",
           item.consolePrice);

    if (!isEmptyStack(item.bidStack)) {
        printf(" bids %d\n", item.bidCounter);
    } else {
        printf("\n");
    }

    deleteAtPosition(pos, L);
}


void awardConsole(char *commandNumber, char command, char *consoleId, tList *L) {
    printf("********************\n");
    printf("%s %c: console %s\n", commandNumber, command, consoleId);

    tPosL pos = findItem(consoleId, *L);
    if (pos == LNULL) {
        printf("+ Error: Award not possible.\n");
        return;
    }

    tItemL item = getItem(pos, *L);

    if (isEmptyStack(item.bidStack)) {
        printf("+ Error: Award not possible.\n");
        return;
    }

    tItemS topBid = peek(item.bidStack);

    printf("* Award: console %s bidder %s brand %s price %.2f\n",
           item.consoleId, topBid.bidder,
           (item.consoleBrand == nintendo) ? "nintendo" : "sega",
           topBid.consolePrice);

    deleteAtPosition(pos, L);
}

void invalidateBids(char *commandNumber, char command, tList *L) {
    printf("********************\n");
    printf("%s %c\n", commandNumber, command);

    if (isEmptyList(*L)) {
        printf("+ Error: InvalidateBids not possible.\n");
        return;
    }

    int totalConsoles = 0;
    int totalBids = 0;
    for (tPosL p = first(*L); p != LNULL; p = next(p, *L)) {
        tItemL item = getItem(p, *L);
        totalConsoles++;
        totalBids += item.bidCounter;
    }

    if (totalConsoles == 0) {
        printf("+ Error: InvalidateBids not possible.\n");
        return;
    }

    float average = (float) totalBids / (float) totalConsoles;
    bool anyInvalidated = false;

    for (tPosL p = first(*L); p != LNULL; p = next(p, *L)) {
        tItemL item = getItem(p, *L);

        if (item.bidCounter > 2 * average) {
            anyInvalidated = true;

            // Vaciar la pila correctamente respetando el TAD
            while (!isEmptyStack(item.bidStack)) {
                pop(&item.bidStack);
            }

            printf("* InvalidateBids: console %s seller %s brand %s price %.2f bids %d average bids %.2f\n",
                   item.consoleId, item.seller,
                   (item.consoleBrand == nintendo) ? "nintendo" : "sega",
                   item.consolePrice, item.bidCounter, average);

            item.bidCounter = 0;
            updateItem(item, p, L);
        }
    }

    if (!anyInvalidated) {
        printf("+ Error: InvalidateBids not possible.\n");
    }
}

void removeConsoles(char *commandNumber, char command, tList *L) {
    printf("********************\n");
    printf("%s %c\n", commandNumber, command);

    if (isEmptyList(*L)) {
        printf("+ Error: Remove not possible.\n");
        return;
    }

    bool anyRemoved = false;
    tPosL p = first(*L);

    while (p != LNULL) {
        tPosL nextP = next(p, *L);  // Guardamos el siguiente porque p puede ser eliminado
        tItemL item = getItem(p, *L);

        if (item.bidCounter == 0) {
            printf("Removing console %s seller %s brand %s price %.2f bids %d\n",
                   item.consoleId, item.seller,
                   (item.consoleBrand == nintendo) ? "nintendo" : "sega",
                   item.consolePrice, item.bidCounter);

            deleteAtPosition(p, L);
            anyRemoved = true;
        }

        p = nextP;
    }

    if (!anyRemoved) {
        printf("+ Error: Remove not possible.\n");
    }
}



void processCommand(char *commandNumber, char command, char *param1, char *param2, char *param3, char *param4, tList *L) {
    switch (command) {
        case 'N':
            new(commandNumber, command, param1, param2, param3, param4, L);
            break;
        case 'B':
            bid(commandNumber, command, param1, param2, param3, L);
            break;
        case 'S':
            stats(commandNumber, command, L);
            break;
        case 'D':
            deleteConsole(commandNumber, command, param1, L);
            break;
        case 'A':
            awardConsole(commandNumber, command, param1, L);
            break;
        case 'I':
            invalidateBids(commandNumber, command, L);
            break;
        case 'R':
            removeConsoles(commandNumber, command, L);
            break;
        default:
            break;
    }
}

void readTasks(char *filename, tList *L) {
    FILE *f = NULL;
    char *commandNumber, *command, *param1, *param2, *param3, *param4;
    const char delimiters[] = " \n\r";
    char buffer[MAX_BUFFER];

    f = fopen(filename, "r");

    if (f != NULL) {
        while (fgets(buffer, MAX_BUFFER, f)) {
            commandNumber = strtok(buffer, delimiters);
            command = strtok(NULL, delimiters);
            param1 = strtok(NULL, delimiters);
            param2 = strtok(NULL, delimiters);
            param3 = strtok(NULL, delimiters);
            param4 = strtok(NULL, delimiters);
            processCommand(commandNumber, command[0], param1, param2, param3, param4, L);
        }
        fclose(f);
    } else {
        printf("Cannot open file %s.\n", filename);
    }
}

int main(int nargs, char **args) {
    char *file_name = "new.txt";
    tList L;
    createEmptyList(&L);
    if (nargs > 1) {
        file_name = args[1];
    } else {
#ifdef INPUT_FILE
        file_name = INPUT_FILE;
#endif
    }

    readTasks(file_name, &L);
    return 0;
}
