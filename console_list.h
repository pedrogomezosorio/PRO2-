/*
 * TITLE: PROGRAMMING II LABS
 * SUBTITLE: Practical 2
 * AUTHOR 1: Samuel Mouriño Cernadas  LOGIN 1: samuel.mourino@udc.es
 * AUTHOR 2: Pedro Gómez Osorio LOGIN 2: pedro.gomez.osorio@udc.es
 * GROUP: 2.3
 * DATE: 01 / 04 / 2025
 */

#ifndef CONSOLE_LIST_H
#define CONSOLE_LIST_H


#include <stdbool.h>
#include "types.h"
#include "bid_stack.h"


// Definición de la estructura de un elemento de la lista
typedef struct {
    tUserId seller;
    tConsoleId consoleId;
    tConsoleBrand consoleBrand;
    tConsolePrice consolePrice;
    tBidCounter bidCounter;
    tStack bidStack; // Pila con las pujas recibidas
} tItemL;

// Definición del nodo de la lista
typedef struct tNode *tPosL;
struct tNode {
    tItemL item;
    tPosL next;
};

typedef tPosL tList;
#define LNULL NULL
typedef struct tNode *tPosL;



//Inicializa la lista como vacía.
void createEmptyList(tList *L);

// Verifica si la lista está vacía.
bool isEmptyList(tList L);

//Inserta un nuevo elemento en la lista de forma ordenada por consoleId.
//Devuelve true si la inserción fue exitosa, false en caso contrario.
bool insertItem(tItemL d, tList *L);

//Elimina el elemento de la lista en la posición indicada.
//Precondición: La consola en dicha posición debe tener una pila de pujas vacía.
void deleteAtPosition(tPosL p, tList *L);

//Devuelve la posición de un elemento en la lista basado en su consoleId.
//Si no existe, devuelve LNULL.
tPosL findItem(tConsoleId id, tList L);

//Devuelve el elemento en la posición indicada.
tItemL getItem(tPosL p, tList L);

//Modifica el elemento en la posición indicada.
void updateItem(tItemL d, tPosL p, tList *L);

//Devuelve la posición del primer elemento en la lista.
tPosL first(tList L);

//Devuelve la posición del último elemento en la lista.
tPosL last(tList L);

//Devuelve la posición del siguiente elemento en la lista.
tPosL next(tPosL p, tList L);

//Devuelve la posición del elemento anterior en la lista.
tPosL previous(tPosL p, tList L);

#endif // PRO2_2025_P2_CONSOLE_LIST_H

