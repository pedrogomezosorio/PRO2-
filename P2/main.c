/*
 * TITLE: PROGRAMMING II LABS
 * SUBTITLE: Practical 2
 * AUTHOR 1: ***************************** LOGIN 1: **********
 * AUTHOR 2: ***************************** LOGIN 2: **********
 * GROUP: *.*
 * DATE: ** / ** / **
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "types.h"
#include "console_list.h"
#include "bid_stack.h"

#define MAX_BUFFER 255

void newConsole(char *commandNumber, char *param1, char *param2, tList *list) {
    tItemL item;
    if (findItem(param1, *list) == LNULL) {
        strcpy(item.consoleId, param1);
        strcpy(item.category, param2);
        strcpy(item.state, "ACTIVE");
        createEmptyStack(&item.bidStack);
        insertItem(item, list);
        printf("%s ==> New: console %s category %s\n", commandNumber, param1, param2);
    } else {
        printf("%s ==> + Error: Console already exists\n", commandNumber);
    }
}

void deleteConsole(char *commandNumber, char *param1, tList *list) {
    tPosL p = findItem(param1, *list);
    if (p != LNULL) {
        deleteAtPosition(p, list);
        printf("%s ==> Delete: console %s\n", commandNumber, param1);
    } else {
        printf("%s ==> + Error: Console not found\n", commandNumber);
    }
}

void bidConsole(char *commandNumber, char *param1, char *param2, char *param3, tList *list) {
    tItemL item;
    tItemS bid;
    tPosL p = findItem(param1, *list);
    if (p != LNULL) {
        item = getItem(p, *list);
        if (strcmp(item.state, "ACTIVE") == 0) {
            strcpy(bid.bidder, param2);
            bid.price = atoi(param3);
            if (push(bid, &item.bidStack)) {
                updateItem(item, p, list);
                printf("%s ==> Bid: console %s bidder %s price %d\n", commandNumber, param1, bid.bidder, bid.price);
            } else {
                printf("%s ==> + Error: Stack overflow\n", commandNumber);
            }
        } else {
            printf("%s ==> + Error: Inactive console\n", commandNumber);
        }
    } else {
        printf("%s ==> + Error: Console not found\n", commandNumber);
    }
}

void awardConsole(char *commandNumber, char *param1, tList *list) {
    tItemL item;
    tItemS bid;
    tPosL p = findItem(param1, *list);
    if (p != LNULL) {
        item = getItem(p, *list);
        if (!isEmptyStack(item.bidStack)) {
            bid = peek(item.bidStack);
            strcpy(item.state, "AWARDED");
            updateItem(item, p, list);
            printf("%s ==> Award: console %s bidder %s price %d\n", commandNumber, param1, bid.bidder, bid.price);
        } else {
            printf("%s ==> + Error: No bids\n", commandNumber);
        }
    } else {
        printf("%s ==> + Error: Console not found\n", commandNumber);
    }
}

void rejectConsole(char *commandNumber, char *param1, tList *list) {
    tItemL item;
    tItemS bid;
    tPosL p = findItem(param1, *list);
    if (p != LNULL) {
        item = getItem(p, *list);
        if (!isEmptyStack(item.bidStack)) {
            bid = peek(item.bidStack);
            strcpy(item.state, "REJECTED");
            updateItem(item, p, list);
            printf("%s ==> Reject: console %s bidder %s price %d\n", commandNumber, param1, bid.bidder, bid.price);
        } else {
            printf("%s ==> + Error: No bids\n", commandNumber);
        }
    } else {
        printf("%s ==> + Error: Console not found\n", commandNumber);
    }
}

void statsConsole(char *commandNumber, tList *list) {
    if (!isEmptyList(*list)) {
        tPosL p;
        tItemL item;
        for (p = first(*list); p != LNULL; p = next(p, *list)) {
            item = getItem(p, *list);
            printf("Console %s category %s state %s bids %d\n",
                   item.consoleId,
                   item.category,
                   item.state,
                   item.bidStack.top + 1);
        }
    } else {
        printf("%s ==> + Error: No consoles\n", commandNumber);
    }
}

void withdrawBid(char *commandNumber, char *param1, tList *list) {
    tItemL item;
    tItemS bid;
    tPosL p = findItem(param1, *list);
    if (p != LNULL) {
        item = getItem(p, *list);
        if (!isEmptyStack(item.bidStack)) {
            bid = peek(item.bidStack);
            pop(&item.bidStack);
            updateItem(item, p, list);
            printf("%s ==> Withdraw: console %s bidder %s price %d\n", commandNumber, param1, bid.bidder, bid.price);
        } else {
            printf("%s ==> + Error: No bids\n", commandNumber);
        }
    } else {
        printf("%s ==> + Error: Console not found\n", commandNumber);
    }
}

void processCommand(char *commandNumber, char command, char *param1, char *param2, char *param3, char *param4, tList *list) {
    switch (command) {
        case 'N': newConsole(commandNumber, param1, param2, list); break;
        case 'D': deleteConsole(commandNumber, param1, list); break;
        case 'B': bidConsole(commandNumber, param1, param2, param3, list); break;
        case 'A': awardConsole(commandNumber, param1, list); break;
        case 'R': rejectConsole(commandNumber, param1, list); break;
        case 'S': statsConsole(commandNumber, list); break;
        case 'I': withdrawBid(commandNumber, param1, list); break;
        default: break;
    }
}

void readTasks(char *filename, tList *list) {
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
            processCommand(commandNumber, command[0], param1, param2, param3, param4, list);
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
    tList list;
    createEmptyList(&list);
    readTasks(file_name, &list);
    return 0;
}
