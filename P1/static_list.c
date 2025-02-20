/*
 * TITLE: PROGRAMMING II LABS
 * SUBTITLE: Practical 1
 * AUTHOR 1: Samuel Mouriño Cernadas LOGIN 1: samuel.mourino@udc.es
 * AUTHOR 2: Pedro Gomez Osorio LOGIN 2: pedro.gomez.osorio@udc.es
 * GROUP: 2.3
 * DATE:
*/

#include "static_list.h"
#include <stdbool.h>
#include <string.h>

void createEmptyList(tList *L) {
    L->lastPos = LNULL;
}

bool insertItem(tItemL d, tPosL p, tList *L) {
    tPosL i;

    if (L->lastPos == MAX-1)   // lista llena
        return false;

    L->lastPos++;
    if (p == LNULL)   // insertar en la última posición
        L->data[L->lastPos] = d;
    else
    {    // insertar en una posición intermedia
        for (i = L->lastPos; i > p; i--)
            L->data[i] = L->data[i-1];

        L->data[p] = d;
    }

    return true;
}

void updateItem(tItemL d, tPosL p, tList *L) {
    L->data[p] = d;
}

void deleteAtPosition(tPosL p, tList *L) {
    tPosL i;
    L->lastPos--;

    for (i = p; i <= L->lastPos; i++)
        L->data[i] = L->data[i+1];
}

tPosL findItem(tConsoleId n, tList L) {
    tPosL p;

    // if (L.lastPos == LNULL) { // lista vacía
    // return LNULL;
    if (isEmptyList(L))
        return LNULL;
    else
    {
        for (p = first(L); p != last(L) && (strcmp(L.data[p].consoleId, n) != 0); p = next(p, L));
        if (strcmp(L.data[p].consoleId, n) == 0)
            return p;
        else
            return LNULL;
    }
}

bool isEmptyList(tList L) {
    return L.lastPos == LNULL;
}

tItemL getItem(tPosL p, tList L) {
    return L.data[p];
}

tPosL first(tList L) {
    return 0;
}

tPosL last(tList L) {
    return L.lastPos;
}

tPosL previous(tPosL p, tList L) {
    return --p;
}

tPosL next(tPosL p, tList L) {
    if (p == L.lastPos)
        return LNULL;
    else
        return ++p;

}