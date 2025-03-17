/*
 * TITLE: PROGRAMMING II LABS
 * SUBTITLE: Practical 1
 * AUTHOR 1: ***************************** LOGIN 1: **********
 * AUTHOR 2: ***************************** LOGIN 2: **********
 * GROUP: *.*
 * DATE: ** / ** / **xlwE
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "types.h"

#define MAX_BUFFER 255

#ifdef DYNAMIC_LIST
#include "dynamic_list.h"
#endif
#ifdef STATIC_LIST
#include "static_list.h"
#endif




void processCommand(tList *list,char *commandNumber, char command, char *param1, char *param2, char *param3, char *param4) {
    tItemL item;
    tPosL pos;
    switch (command) {
        case 'N':
            printf("********************\n");
            printf("Command: %s %c %s %s %s %s\n", commandNumber, command, param1, param2, param3, param4);
            strcpy(item.consoleId , param1);
            strcpy(item.seller , param2);
            item.consoleBrand = (strcmp(param3, "nintendo") == 0) ? nintendo : sega;
                printf("+ Error: New not possible\n");
            item.consolePrice = atof(param4);
            item.bidCounter = 0;
            if (insertItem(item, LNULL, &list)) {
                printf("* New: console %s seller %s brand %s price %.2f\n", param1, param2,param3,  param4);
            } else {
                printf("+ Error: New not possible\n");
            }
            break;
        case 'D':
            pos = findItem(param1, *list);
            if (pos == LNULL){
                printf("+ Error: Delete not possible\n");
            } else {
                item = getItem(pos, *list);
                deleteAtPosition(pos, &list);
                printf("* Delete: console %s seller %s brand %s price %.2f\n",param1, param2, param3, param4);
            }
            break;
        case 'B':
            pos = findItem(param1, *list);
            if (pos == LNULL) {
                printf("+ Error: Bid not possible\n");
            } else {
                item = getItem(pos, *list);
                if (strcmp(item.seller, param2) == 0 || atof(param3) <= item.consolePrice) {
                    printf("+ Error: Bid not possible\n");
                } else {
                    item.consolePrice = atof(param3);
                    item.bidCounter++;
                    updateItem(item, pos, list);
                    printf("* Bid: console %s seller %s brand %s price %.2f bids %d\n", item.consoleId, item.seller, param3, item.consolePrice, item.bidCounter);
                }
            }
            break;
        case 'S':
            if(isEmptyList(*list)){
                printf("+ Error: Stats not possible\n");
            } else {
               pos = first(*list);
                while (pos != LNULL) {
                item = getItem(pos, *list);
                printf("* Console: %s seller %s brand %s price %.2f bids %d\n", param1, param2, param3, param4);
                pos = next(pos, *list);
                }
            }
            break;
        default:
            printf("Unknown command\n");
            break;
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

            processCommand(list, commandNumber, command[0], param1, param2, param3, param4);
        }

        fclose(f);

    } else {
        printf("Cannot open file %s.\n", filename);
    }
}


int main(int nargs, char **args) {
    tList list;
    createEmptyList(&list);
    char *file_name = "new.txt";

    if (nargs > 1) {
        file_name = args[1];
    } else {
        #ifdef INPUT_FILE
        file_name = INPUT_FILE;
        #endif
    }

    readTasks(file_name, &list);

    return 0;
}

