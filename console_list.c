/*
 * TITLE: PROGRAMMING II LABS
 * SUBTITLE: Practical 2
 * AUTHOR 1: Samuel Mouriño Cernadas LOGIN 1: samuel.mourino@udc.es
 * AUTHOR 2: Pedro Gómez Osorio LOGIN 2: pedro.gomez.osorio@udc.es
 * GROUP: 2.3
 * DATE: 01 / 04 / 2025
 */

#include "console_list.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>


void createEmptyList(tList *L) {
    *L = LNULL;
}

bool isEmptyList(tList L) {
    return L == LNULL;
}

tPosL first(tList L) {
    return L;
}

tPosL last(tList L) {
    tPosL p;
    for (p = L; p != LNULL && p->next != LNULL; p = p->next);
    return p;
}

tPosL next(tPosL p, tList L) {
    return (p != LNULL) ? p->next : LNULL;
}

tPosL previous(tPosL p, tList L) {
    tPosL q;
    if (p == L) return LNULL;
    for (q = L; q->next != p; q = q->next);
    return q;
}

tPosL findItem(tConsoleId id, tList L) {
    tPosL p;
    for (p = L; p != LNULL; p = p->next) {
        if (strcmp(p->item.consoleId, id) == 0) {
            return p;
        }
    }
    return LNULL;
}

tItemL getItem(tPosL p, tList L) {
    return p->item;
}

void updateItem(tItemL d, tPosL p, tList *L) {
    if (p != LNULL) {
        p->item = d;
    }
}

bool insertItem(tItemL d, tList *L) {
    tPosL newNode, prev, curr;

    newNode = (tPosL)malloc(sizeof(struct tNode));
    if (newNode == NULL) return false;

    newNode->item = d;

    prev = LNULL;
    curr = *L;
    while (curr != LNULL && strcmp(curr->item.consoleId, d.consoleId) < 0) {
        prev = curr;
        curr = curr->next;
    }

    if (prev == LNULL) {
        newNode->next = *L;
        *L = newNode;
    } else {
        newNode->next = curr;
        prev->next = newNode;
    }

    return true;
}

void deleteAtPosition(tPosL p, tList *L) {
    tPosL prev;

    if (p == *L) {
        *L = p->next;
    } else {
        prev = previous(p, *L);
        prev->next = p->next;
    }

    free(p);
}
