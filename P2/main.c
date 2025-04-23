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

void new(char *commandNumber, char command, char *consoleId, char *userId, char *consoleBrand,
                char *consolePrice, tList *L)
{
    tItemL item;

    printf("%s %c: console %s seller %s brand %s price %s\n", commandNumber, command, consoleId, userId,
           consoleBrand, consolePrice);

    if (findItem(consoleId, *L) != LNULL)
    {
        printf("+ Error: New not possible\n");
        return;
    }

    strcpy(item.consoleId, consoleId);
    strcpy(item.seller, userId);

    if (strcmp(consoleBrand, "nintendo") == 0)
        item.consoleBrand = nintendo;
    else if (strcmp(consoleBrand, "sega") == 0)
        item.consoleBrand = sega;
    else {
        printf("+ Error: New not possible\n");
        return;
    }

    item.consolePrice = atof(consolePrice);
    item.bidCounter = 0;
    createEmptyStack(&item.bidStack);

    if (insertItem(item, L))
    {
        printf("* New: console %s seller %s brand %s price %.2f\n", consoleId, userId,consoleBrand,
               atof(consolePrice));
    } else {
        printf("+ Error: New not possible\n");
    }
}

void delete(char *commandNumber, char command, char *consoleId, tList *L)
{
    tItemL item;
    tPosL pos;
    printf("%s %c: console %s\n", commandNumber, command, consoleId);

    pos = findItem(consoleId, *L);

    if (pos == LNULL)
    {
        printf("+ Error: Delete not possible\n");
        return;
    }

    item = getItem(pos, *L);

    while(!isEmptyStack(item.bidStack))     // vaciamos la pila de pujas para poder eliminar la consola
    {
        peek(item.bidStack);
    }

    deleteAtPosition(pos, L);

    if (item.consoleBrand == 0)
        printf("* Delete: console %s seller %s brand %s price %.2f bids %d\n",item.consoleId,
               item.seller, "nintendo", item.consolePrice, item.bidCounter);
    else
        printf("* Delete: console %s seller %s brand %s price %.2f bids %d\n",item.consoleId,
               item.seller, "sega", item.consolePrice, item.bidCounter);
}

void bid(char *commandNumber, char command, char *consoleId, char *userId, char *consolePrice, tList *L)
{

}

void award(char *commandNumber, char command, char *consoleId, tList *L)
{

}

void invalidateBids(char *commandNumber, char command, tList *L)
{

}

void removeConsole(char *commandNumber, char command, tList *L)
{

}

void stats(char *commandNumber, char command, tList *L)
{

}

void processCommand(char *commandNumber, char command, char *param1, char *param2, char *param3, char *param4, tList *L) {
    switch (command)
    {
        case 'N':
            new(commandNumber, command, param1, param2, param3, param4, L);
            break;

        case 'D':
            delete(commandNumber, command, param1, L);
            break;

        case 'B':
            bid (commandNumber, command, param1, param2, param3, L);
            break;

        case 'A':
            award(commandNumber, command, param1, L);
            break;

        case 'I':
            invalidateBids(commandNumber, command, L);
            break;

        case 'R':
            removeConsole(commandNumber, command, L);
            break;

        case 'S':
            stats(commandNumber, command, L);
            break;

        default:
            printf("Unknown command\n");
            break;
    }
}

void readTasks(char *filename)
{
    FILE *f = NULL;
    char *commandNumber, *command, *param1, *param2, *param3, *param4;
    const char delimiters[] = " \n\r";
    char buffer[MAX_BUFFER];

    f = fopen(filename, "r");
    tList L;
    createEmptyList(&L);

    if (f != NULL)
    {
        while (fgets(buffer, MAX_BUFFER, f))
        {
            commandNumber = strtok(buffer, delimiters);
            command = strtok(NULL, delimiters);
            param1 = strtok(NULL, delimiters);
            param2 = strtok(NULL, delimiters);
            param3 = strtok(NULL, delimiters);
            param4 = strtok(NULL, delimiters);

            processCommand(commandNumber, command[0], param1, param2, param3, param4, &L);
        }
        fclose(f);
    }
    else {
        printf("Cannot open file %s.\n", filename);
    }
}

int main(int nargs, char **args)
{
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
