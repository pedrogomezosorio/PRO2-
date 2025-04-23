#include <stdio.h>
#include <string.h>

#ifdef DYNAMIC_LIST
#include "dynamic_list.h"
#endif
#ifdef STATIC_LIST
#include "static_list.h"
#endif


void print_list(tList list) {
    tPosL pos;
    tItemL item;

    printf("(");
    if (!isEmptyList(list)) {
        pos = first(list);
        while (pos != LNULL) {
            item = getItem(pos, list);
            printf(" %s price %.2f", item.consoleId, item.consolePrice);
            pos = next(pos, list);
        }
    }
    printf(" )\n");
}

int main() {
    tList list;
    tPosL pos;
    tItemL item1, item2;

    /* init */
    item1.consoleBrand = nintendo;
    strcpy(item1.seller, "user1");
    item1.consolePrice = 100;


    /* create */
    createEmptyList(&list);
    print_list(list);


    /* insert */
    strcpy(item1.consoleId, "p3");
    insertItem(item1, LNULL, &list);
    print_list(list);

    strcpy(item1.consoleId, "p1");
    insertItem(item1, first(list), &list);
    print_list(list);

    strcpy(item1.consoleId, "p5");
    insertItem(item1, LNULL, &list);
    print_list(list);

    strcpy(item1.consoleId, "p2");
    insertItem(item1, next(first(list),list), &list);
    print_list(list);

    strcpy(item1.consoleId, "p4");
    insertItem(item1, last(list), &list);
    print_list(list);


    /* find */
    pos = findItem("p33", list);
    if (pos == LNULL) {
        printf("p33 Not found\n");
    }

    pos = findItem("p3", list);
    item2 = getItem(pos, list);
    printf("%s\n", item2.consoleId);


    /* update */
    item2.consolePrice = 500;
    updateItem(item2, pos, &list);
    item2 = getItem(pos, list);
    printf("%s\n", item2.consoleId);
    print_list(list);


    /* remove */
    deleteAtPosition(next(first(list),list), &list);
    print_list(list);

    deleteAtPosition(previous(last(list),list), &list);
    print_list(list);

    deleteAtPosition(first(list),&list);
    print_list(list);

    deleteAtPosition(last(list),&list);
    print_list(list);

    deleteAtPosition(first(list),&list);
    print_list(list);

    insertItem(item1, LNULL, &list);
    print_list(list);


}
