#include <stdlib.h>
#include "helper.h"

int compareID(void * pItem, void * pComparisonArg) {
    PCB * ID1 = (PCB *)pItem;
    int * ID2 = (int *) pComparisonArg;
    if(ID1->ID == *ID2) {
        return 1;
    }
    return 0;
}

void printList(char * listName, List * list) {
    printf("%s List: ", listName);
    Node *temp = list->pFirstNode;
    while (temp->pNext!= NULL) {
        PCB *it = temp->pItem;
        printf("%d , ", it->ID);
        temp = temp->pNext;
    }
    void *it = temp->pItem;
    printf(" %d ", *(int *)it);
    temp = temp->pNext;
    printf("\n");
}

bool isProcessFound(List * list, int id) {
    COMPARATOR_FN comparator = (COMPARATOR_FN) &compareID;
    if(List_search(list, comparator, (void *)&id)) {
        return true;
    }
    return false;
}

int freeProcess(PCB * process) {
    int freedProcessID = process->ID;
    free(process->message->content);
    free(process->message);
    free(process);
    return freedProcessID;
}
