#include <stdlib.h>
#include <stdio.h>
#include "operations.h"
#include "helper.h"

#define MAX_MESSAGE_CHARACTERS 40
#define PRIORITY 3
#define MAX_SEMAPHORES 5

static int PID = 0;
List * readyProcesses[PRIORITY];
List * runningProcesses;
List * send;
List * receive;


void ListInit() {
    readyProcesses[HIGH] = List_create();
    readyProcesses[NORMAL] = List_create();
    readyProcesses[LOW] = List_create();
    runningProcesses = List_create();
}

int Create(int priority) {
    PID++;
    PCB * process = malloc(sizeof (PCB));
    process->ID = PID;
    process->state = READY;
    process->priority = priority;

    process->message = (Message *) malloc(sizeof (Message));
    process->message->content = (char *) malloc(sizeof (char) * MAX_MESSAGE_CHARACTERS);

    List_prepend(readyProcesses[priority], process);
    List_prepend(runningProcesses, process);
    printList(runningProcesses);
    printList(readyProcesses[priority]);

    return PID;
}

int Fork() {
    PCB * process = List_last(runningProcesses);
    if(process) {
        return Create(process->priority);
    }
    return -1;
}

int Kill(int id) {
    COMPARATOR_FN comparator = (COMPARATOR_FN) &compareID;
    Node * foundNode = List_search(runningProcesses, comparator, (void *)&id);
    if(foundNode) {
        PCB * removedProcess = List_remove(runningProcesses);
        return removedProcess->ID;
    }
    for (int i = 0; i < PRIORITY; i++) {
        foundNode = List_search(readyProcesses[i], comparator, (void *)&id);
        if (foundNode) {
            PCB *removedProcess = List_remove(readyProcesses[i]);
            return removedProcess->ID;
        }
    }
    return -1;
}

int Exit() {
    List_last(runningProcesses);
    PCB * removedProcess = List_trim(runningProcesses);
    if(removedProcess) {
        return removedProcess->ID;
    }
    return -1;
}
