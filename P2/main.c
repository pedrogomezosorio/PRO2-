/*
 * TITLE: PROGRAMMING II LABS
 * SUBTITLE: Practical 1
 * AUTHOR 1: SAMUEL MOURIÑO CERNADAS    LOGIN 1: samuel.mourino@udc.es
 * AUTHOR 2: PEDRO  GÓMEZ   OSORIO      LOGIN 2: pedro.gomez.osorio@udc.es
 * GROUP: 2.3
 * DATE: 20 / 03 / 2025
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

/*
* Objetivo: Añadir una nueva consola a la lista L.
* Entradas:
- commandNumber: Número de comando leído del archivo.
- command: Letra del comando ('N' en este caso).
- consoleId: Identificador de la consola (único en cada una de ellas).
- userId: Identificador del vendedor.
- consoleBrand: Marca de la consola (puede ser o Nintendo o Sega).
- consolePrice: Precio de salida de la consola.
- L: Puntero a la lista de consolas en subasta.
* Precondiciones:
- La lista debe estar inicializada.
- No debe existir una consola con el mismo id.
- La marca de la consola debe ser "Nintendo" o "Sega".
- El precio debe ser un número válido.
* Postcondiciones:
- Se agrega la consola a la lista si cumple con los requisitos.
- Se muestra un mensaje el cual nos dice si se ha introducido la consola, o por el contrario, si hubo algún fallo.
 */


void new(char *commandNumber, char command, char *consoleId, char *userId, char *consoleBrand, char *consolePrice, tList *L)
{
    tItemL item;

    printf("%s %c: console %s seller %s brand %s price %s\n", commandNumber, command, consoleId, userId,
           consoleBrand, consolePrice);

    if (findItem(consoleId, *L) != LNULL) {
        printf("+ Error: New not possible\n");
        return;
    }

    strcpy(item.consoleId , consoleId);
    strcpy(item.seller , userId);

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
    if (insertItem(item, LNULL, L)) {
        printf("* New: console %s seller %s brand %s price %.2f\n", consoleId, userId,consoleBrand,
               atof(consolePrice));
    } else {
        printf("+ Error: New not possible\n");
    }
}

/*
* Objetivo: Mostrar las estadísticas de todas las consolas en la lista L.
* Entradas:
- commandNumber: Número de comando leído del archivo.
- command: Letra del comando ('S' en este caso).
- L: Puntero a la lista de consolas.
* Precondiciones:
- La lista debe estar inicializada.
* Postcondiciones:
- Se muestran las estadísticas de las consolas en la lista.
 */


void stats(char *commandNumber, char command, tList *L)
{
    tItemL item;
    tPosL pos;
    int countNintendo = 0, countSega = 0;
    float totalPriceNintendo = 0.0, totalPriceSega = 0.0;

    printf("%s %c\n", commandNumber, command);

    if (isEmptyList(*L))
    {
        printf("+ Error: Stats not possible\n");
        return;
    }

    pos = first(*L);

    while (pos != LNULL)
    {
        item = getItem(pos, *L);
        printf("Console %s seller %s brand %s price %.2f bids %d\n",
               item.consoleId, item.seller, (item.consoleBrand == nintendo) ? "nintendo" : "sega",
               item.consolePrice, item.bidCounter);

        if (item.consoleBrand == nintendo) {
            countNintendo++;
            totalPriceNintendo += item.consolePrice;
        } else {
            countSega++;
            totalPriceSega += item.consolePrice;
        }

        pos = next(pos, *L);
    }

    printf("\nBrand        Consoles    Price    Average\n");
    printf("Nintendo    %8d %8.2f %8.2f\n",
           countNintendo, totalPriceNintendo, (countNintendo > 0) ? totalPriceNintendo / countNintendo : 0.0);
    printf("Sega        %8d %8.2f %8.2f\n",
           countSega, totalPriceSega, (countSega > 0) ? totalPriceSega / countSega : 0.0);
}

/*
* Objetivo: Eliminar una consola de la lista L.
* Entradas:
- commandNumber: Número de comando leído del archivo.
- command: Letra del comando ('D' en este caso).
- consoleId: Identificador de la consola que vamos a eliminar.
- L: Puntero a la lista de consolas.
* Precondiciones:
- La lista debe estar inicializada.
- La consola debe existir en la lista.
* Postcondiciones:
- Se elimina la consola de la lista si existía.
- Se muestra un mensaje de éxito o error según el resultado.
 */



void delete(char *commandNumber, char command, char *consoleId, tList *L)
{
    tItemL item;
    tPosL pos;
    printf("%s %c: console %s\n", commandNumber, command, consoleId);

    pos = findItem(consoleId, *L);
    if (pos == LNULL)
        printf("+ Error: Delete not possible\n");
    else
    {
        item = getItem(pos, *L);
        deleteAtPosition(pos, L);
        if (item.consoleBrand == 0)
            printf("* Delete: console %s seller %s brand %s price %.2f bids %d\n",item.consoleId,
                   item.seller, "nintendo", item.consolePrice, item.bidCounter);
        else
            printf("* Delete: console %s seller %s brand %s price %.2f bids %d\n",item.consoleId,
                   item.seller, "sega", item.consolePrice, item.bidCounter);
    }
}

/*
* Objetivo: Realizar una puja por una consola que ya existe.
* Entradas:
- commandNumber: Número de comando leído del archivo.
- command: Letra del comando ('B' en este caso).
- consoleId: Identificador único de la consola por la que vamos a pujar.
- userId: Identificador del pujador.
- newPrice: Nuevo precio que queda después de la puja.
- L: Puntero a la lista de consolas.
* Precondiciones:
- La lista debe estar inicializada.
- La consola debe existir en la lista.
- El pujador no puede ser el vendedor.
- El nuevo precio debe ser mayor al precio actual (no puedes pujar si tu puja es una oferta menor a la que ya habia anteriormente).
* Postcondiciones:
- Se actualiza el precio y el número de pujas de la consola si la oferta es válida.
- Se muestra un mensaje de éxito o error según el resultado.
 */



void bid (char *commandNumber, char command, char *consoleId, char *userId, char *consoleBrand, tList *L){
    tItemL item;
    tPosL pos;
    printf("%s %c: console %s bidder %s price %s\n", commandNumber, command, consoleId, userId, consoleBrand);

    pos = findItem(consoleId, *L);
    if (pos == LNULL) {
        printf("+ Error: Bid not possible\n");
    } else {
        item = getItem(pos, *L);
        if (strcmp(item.seller, userId) == 0 || atof(consoleBrand) <= item.consolePrice) {
            printf("+ Error: Bid not possible\n");
        } else {
            item.consolePrice = atof(consoleBrand);
            item.bidCounter++;
            updateItem(item, pos, L);

            if (item.consoleBrand == 0)
                printf("* Bid: console %s seller %s brand %s price %.2f bids %d\n",item.consoleId,
                       item.seller, "nintendo", item.consolePrice, item.bidCounter);
            else
                printf("* Bid: console %s seller %s brand %s price %.2f bids %d\n",item.consoleId,
                       item.seller, "sega", item.consolePrice, item.bidCounter);
        }
    }
}

void processCommand(char *commandNumber, char command, char *param1, char *param2, char *param3, char *param4, tList *L)
{

    printf("********************\n");


    switch (command)
    {
        case 'N':
            /*[N]ew: Alta de una nueva consola.*/

            new(commandNumber, command, param1, param2, param3, param4, L);
            break;

        case 'D':
            /*[D]elete: Baja de una consola.*/
            delete(commandNumber, command, param1, L);
            break;

        case 'B':
            /*[B]id: Puja de un pujador por una determinada consola*/
            bid (commandNumber, command, param1, param2, param3, L);
            break;

        case 'S':
            /*[S]tats: Listado de las consolas actuales y sus datos.*/
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

    if (f != NULL) {

        while (fgets(buffer, MAX_BUFFER, f)) {
            commandNumber = strtok(buffer, delimiters);
            command = strtok(NULL, delimiters);
            param1 = strtok(NULL, delimiters);
            param2 = strtok(NULL, delimiters);
            param3 = strtok(NULL, delimiters);
            param4 = strtok(NULL, delimiters);

            processCommand(commandNumber, command[0], param1, param2, param3, param4, &L);
        }

        fclose(f);

    } else {
        printf("Cannot open file %s.\n", filename);
    }
}


int main(int nargs, char **args) {
    char *file_name = "prueba.txt";

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

