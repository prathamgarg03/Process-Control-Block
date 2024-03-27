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

void addToRunningProc(int priority)
{
    PID++;
    PCB * process = malloc(sizeof (PCB));
    process->ID = PID;
    process->state = READY;
    process->priority = priority;

    process->message = (Message *) malloc(sizeof (Message));
    process->message->content = (char *) malloc(sizeof (char) * MAX_MESSAGE_CHARACTERS);
    List_prepend(runningProcesses, process);
    printList(runningProcesses);
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
//    List_prepend(runningProcesses, process);
//    printList(runningProcesses);
    printList(readyProcesses[priority]);

    return PID;
}

//complete
int Fork() {
//    printList(runningProcesses);
    PCB * process = List_last(runningProcesses);
    if(process) {
//        printList(runningProcesses);
        return Create(process->priority);
    }
    return -1;
}

int Kill(int id) {
//    printList(runningProcesses);
    COMPARATOR_FN comparator = (COMPARATOR_FN) &compareID;
    Node * foundNode = List_search(runningProcesses, comparator, (void *)&id);
    if(foundNode) {
        PCB * removedProcess = List_remove(runningProcesses);
//        printList(runningProcesses);
        return removedProcess->ID;
    }
    for (int i = 0; i < PRIORITY; i++) {
        foundNode = List_search(readyProcesses[i], comparator, (void *)&id);
        if (foundNode) {
            PCB *removedProcess = List_remove(readyProcesses[i]);
//            printList(runningProcesses);
            return removedProcess->ID;
        }
    }

    return -1;
}

void ProcessSchedule() {
//    printList(runningProcesses);
    int highest_priority = -1;
    for (int i = 0; i < PRIORITY; i++) {
        if (List_count(readyProcesses[i])) {
            highest_priority = i;
            break;
        }
    }
    if (highest_priority != -1) {
        PCB *next_process = List_trim(readyProcesses[highest_priority]);
        if(!List_append(runningProcesses, next_process)) {
            next_process->state = RUNNING;
            printf("Success! Process PID: %d now gets control of the CPU", next_process->ID);
//            printList(runningProcesses);
        } else {
            printf("Failure! Process PID: %d doesn't get control of the CPU", next_process->ID );
        }
    } else {
        printf("No process available to run\n");
    }
}

int Exit() {
//    printList(runningProcesses);
    List_last(runningProcesses);
    PCB * removedProcess = List_trim(runningProcesses);
    if(removedProcess) {
        ProcessSchedule();
        if(List_count(runningProcesses) != 0)
//            printList(runningProcesses);
        return removedProcess->ID;
    }
    return -1;
}

void Quantum() {
//    printList(runningProcesses);
    PCB *process;
    process = List_last(runningProcesses);
    if (process->ID != 0) {
        process = List_remove(runningProcesses);
//        if (process->priority < 2) {
//            process->priority++;
//        }
        process->state = READY;
        if (process) {
            List_prepend(readyProcesses[process->priority], process);
            printf("pid: %i placed on ready queue.\n", process->ID);
        }
    }
    else {
        process->state = READY;
    }
    ProcessSchedule();
//    printList(runningProcesses);
}