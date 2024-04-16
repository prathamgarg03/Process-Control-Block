#include <stdlib.h>
#include <string.h>
#include "helper.h"

int compareID(void * pItem, void * pComparisonArg) {
    PCB * ID1 = (PCB *)pItem;
    int * ID2 = (int *) pComparisonArg;
    if(ID1->ID == *ID2) {
        return 1;
    }
    return 0;
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
    free(process->message);
    free(process);
    return freedProcessID;
}

int compareMessage(void * pItem, void * pComparisonArg) {
    MessagePacket * ID1 = (MessagePacket *)pItem;
    int * ID2 = (int *) pComparisonArg;
    if(ID1->receiverID == *ID2) {
        return 1;
    }
    return 0;
}

bool anyMessage(List * list, int id) {
    COMPARATOR_FN comparator = (COMPARATOR_FN) &compareMessage;
    if(List_search(list, comparator, (void *)&id)) {
        return true;
    }
    return false;
}

char * freeMessage(MessagePacket * msg) {
    char * receivedMessage = malloc(sizeof(char) * (strlen(msg->content) + 1));
    strcpy(receivedMessage, msg->content);
    free(msg->content);
    free(msg);
    return receivedMessage;
}

int compareSemaphore(void * pItem, void * pComparisonArg) {
    Semaphore * ID1 = (Semaphore *)pItem;
    int * ID2 = (int *) pComparisonArg;
    if(ID1->ID == *ID2) {
        return 1;
    }
    return 0;
}

bool isSemaphoreFound(List * list, int id) {
    COMPARATOR_FN comparator = (COMPARATOR_FN) &compareSemaphore;
    if(List_search(list, comparator, (void *)&id)) {
        return true;
    }
    return false;
}

void printList(char * listName, List * list) {
    printf("%s list: [", listName);
    if(List_count(list) == 0) {
        printf("...Empty...");
    } else {
        Node *temp = list->pFirstNode;
        while (temp->pNext != NULL) {
            PCB *it = temp->pItem;
            printf("%d ,", it->ID);
            temp = temp->pNext;
        }
        PCB *it = temp->pItem;
        printf(" %d ", it->ID);
    }
    printf("]\n");
}

void printInfo(PCB * process, int i) {
    char * state[] = {
            "RUNNING",
            "READY",
            "BLOCKED"
    };
    char * priority[] = {
            "RUNNING",
            "READY",
            "BLOCKED"
    };
    printf("PID: %d \n", process->ID);
    printf("Process state: %s \n", state[process->state]);
    printf("Process priority: %s \n", priority[process->priority]);
    if(process->message) {
        printf("Process message: %s \n", process->message);
    } else {
        printf("No message.");
    }
    char * listName = "No List";
    switch (i) {
        case 1:
            listName = "HIGH priority ready list\n";
            break;
        case 2:
            listName = "NORMAL priority ready list\n";
            break;
        case 3:
            listName = "LOW priority ready list\n";
            break;
        case 4:
            listName = "sender list\n";
            break;
        case 5:
            listName = "receiver list\n";
            break;
        case 6:
            listName = "semaphore list\n";
            break;
        default:
            listName = "no list\n";
            break;
    }
    printf("Process list: %s", listName);
}

