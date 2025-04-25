/*
 * TITLE: PROGRAMMING II LABS
 * SUBTITLE: Practical 2
 * AUTHOR 1: Samuel Mouriño Cernadas LOGIN 1: samuel.mourino@udc.es
 * AUTHOR 2: Pedro Gómez Osorio LOGIN 2: pedro.gomez.osorio@udc.es
 * GROUP: 2.3
 * DATE: 25 / 04 / 2025
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "types.h"
#include "console_list.h"
#include "bid_stack.h"

#define MAX_BUFFER 255

tList L;

void new(char *commandNumber, char command, char *consoleId, char *userId, char *consoleBrand, char *consolePrice, tList *L){
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
    double price = atof(newPriceStr);
    printf("%s %c: console %s bidder %s price %s\n", commandNumber, command, consoleId, userId, newPriceStr);

    tPosL pos = findItem(consoleId, *L);
    if (pos == LNULL) {
        printf("+ Error: Bid not possible\n");
        return;
    }

    tItemL item = getItem(pos, *L);
    tConsolePrice newPrice = atof(newPriceStr);

    if (strcmp(item.seller, userId) == 0 || newPrice <= item.consolePrice) {
        printf("+ Error: Bid not possible\n");
        return;
    }

    tItemS bidItem;
    strcpy(bidItem.bidder, userId);
    bidItem.consolePrice = newPrice;

    if (!push(bidItem, &item.bidStack)) {
        printf("+ Error: Bid not possible\n");
        return;
    }

    item.consolePrice = newPrice;
    item.bidCounter++;
    updateItem(item, pos, L);

    printf("* Bid: console %s bidder %s brand %s price %.2f bids %d\n",
           item.consoleId, userId,
           (item.consoleBrand == nintendo) ? "nintendo" : "sega",
           item.consolePrice, item.bidCounter);
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
    float nintendoTotal = 0, segaTotal = 0;
    float maxIncrease = -1;
    tItemL topItem;
    tItemS topBid;

    for (p = first(*L); p != LNULL; p = next(p, *L)) {
        tItemL item = getItem(p, *L);
        printf("Console %s seller %s brand %s price %.2f. ",
               item.consoleId, item.seller,
               (item.consoleBrand == nintendo) ? "nintendo" : "sega",
               item.consolePrice);

        if (!isEmptyStack(item.bidStack)) {
            tItemS top = peek(item.bidStack);
            printf("bids %d top bidder %s\n", item.bidCounter, top.bidder);

            float basePrice = item.bidStack.items[0].consolePrice;
            float increase = ((top.consolePrice - basePrice) / basePrice) * 100.0;
            if (increase > maxIncrease) {
                maxIncrease = increase;
                topItem = item;
                topBid = top;
            }
        } else {
            printf("No bids\n");
        }

        if (item.consoleBrand == nintendo) {
            nintendoCount++;
            nintendoTotal += item.consolePrice;
        } else {
            segaCount++;
            segaTotal += item.consolePrice;
        }
    }

    printf("\nBrand        Consoles    Price    Average\n");
    printf("Nintendo    %8d %8.2f %8.2f\n", nintendoCount, nintendoTotal,
           (nintendoCount > 0) ? nintendoTotal / nintendoCount : 0.0);
    printf("Sega        %8d %8.2f %8.2f\n", segaCount, segaTotal,
           (segaCount > 0) ? segaTotal / segaCount : 0.0);

    if (maxIncrease >= 0) {
        printf("Top bid: console %s seller %s brand %s price %.2f bidder %s top price %.2f increase %.2f%%\n",
               topItem.consoleId, topItem.seller,
               (topItem.consoleBrand == nintendo) ? "nintendo" : "sega",
               topItem.consolePrice, topBid.bidder, topBid.consolePrice, maxIncrease);
    } else {
        printf("Top bid not possible\n");
    }
}

void processCommand(char *commandNumber, char command, char *param1, char *param2, char *param3, char *param4) {
    switch (command) {
        case 'N':
            new(commandNumber, command, param1, param2, param3, param4, &L);
            break;
        case 'B':
            bid(commandNumber, command, param1, param2, param3, &L);
            break;
        case 'S':
            stats(commandNumber, command, &L);
            break;
        default:
            break;
    }
}

void readTasks(char *filename) {
    FILE *f = NULL;
    char *commandNumber, *command, *param1, *param2, *param3, *param4;
    const char delimiters[] = " \n\r";
    char buffer[MAX_BUFFER];

    f = fopen(filename, "r");
    createEmptyList(&L);

    if (f != NULL) {
        while (fgets(buffer, MAX_BUFFER, f)) {
            commandNumber = strtok(buffer, delimiters);
            command = strtok(NULL, delimiters);
            param1 = strtok(NULL, delimiters);
            param2 = strtok(NULL, delimiters);
            param3 = strtok(NULL, delimiters);
            param4 = strtok(NULL, delimiters);
            processCommand(commandNumber, command[0], param1, param2, param3, param4);
        }
        fclose(f);
    } else {
        printf("Cannot open file %s.\n", filename);
    }
}

int main(int nargs, char **args) {
    char *file_name = "new.txt";

    if (nargs > 1) {
        file_name = args[1];
    } else {
#ifdef INPUT_FILE
        file_name = INPUT_FILE;
#endif
    }

    readTasks(file_name);
    return 0;
}
