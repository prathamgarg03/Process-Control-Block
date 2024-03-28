#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "operations.h"
#include "helper.h"

#define MAX_MESSAGE_CHARACTERS 41
#define PRIORITY 3
#define MAX_SEMAPHORES 5

static int PID = 0;
List * readyProcesses[PRIORITY];
PCB * runningProcess;
List * send;
List * receive;
List * semaphoreQueue;

void ListInit() {
    readyProcesses[HIGH] = List_create();
    readyProcesses[NORMAL] = List_create();
    readyProcesses[LOW] = List_create();
    send = List_create();
    receive = List_create();
    semaphoreQueue = List_create();
}

void ProcessSchedule() {
    int highest_priority = -1;
    for (int i = 0; i < PRIORITY; i++) {
        if (List_count(readyProcesses[i])) {
            highest_priority = i;
            break;
        }
    }
    if (highest_priority != -1) {
        PCB *next_process = List_trim(readyProcesses[highest_priority]);
        next_process->state = RUNNING;
        runningProcess = next_process;
        printf("Success! PID: %d now gets control of the CPU.\n", runningProcess->ID);
    } else {
        printf("No process available to run\n");
    }
}

int Create(int priority) {
    PID++;
    PCB * process = malloc(sizeof (PCB));
    process->ID = PID;
    process->state = READY;
    process->priority = priority;
    process->message = (Message *) malloc(sizeof (Message));
    process->message->content = (char *) malloc(sizeof (char) * MAX_MESSAGE_CHARACTERS);

    if(!runningProcess) {
        process->state = RUNNING;
        runningProcess = process;
    } else {
        List_prepend(readyProcesses[priority], process);
        char* priorityNames[] = {
                "HIGH",
                "NORMAL",
                "LOW"
        };
        printList(priorityNames[priority] , readyProcesses[priority]);
    }
    return PID;
}

int Fork() {
    return runningProcess ? Create(runningProcess->priority) : -1;
}

int Kill(int id) {
    if(runningProcess->ID == id) {
        Exit();
    }
    for (int i = 0; i < PRIORITY; i++) {
        if (isProcessFound(readyProcesses[i], id)) {
            PCB * removedProcess = List_remove(readyProcesses[i]);
            return freeProcess(removedProcess);
        }
    }
    return -1;
}

int Exit() {
    int freedProcess = freeProcess(runningProcess);
    ProcessSchedule();
    return freedProcess;
}

void Quantum() {
    if (runningProcess) {
        PCB * readyProcess = runningProcess;
        readyProcess->state = READY;
        List_prepend(readyProcesses[readyProcess->priority], readyProcess);
        printf("PID: %d placed on ready queue. \n",readyProcess->ID);
    }
    ProcessSchedule();
}

void Send(int id, char * message) {
    if(runningProcess) {
        PCB * sender = runningProcess;
        if(isProcessFound(receive, id)) {
            PCB * receiver = List_remove(receive);

            receiver->message->senderID = sender->ID;
            strcpy(receiver->message->content, message);
            receiver->state = READY;
            List_prepend(readyProcesses[sender->priority], sender);

            sender->state = BLOCKED;
            List_prepend(send, sender);
            printf("Message sent to PID: %d, from PID: %d \n", receiver->ID, sender->ID);
        } else {
            printf("No receiver available to receive.\n");
            return;
        }
    } else {
        printf("No sender available to send message.\n");
    }
    ProcessSchedule();
}
int newSemaphore(int sid,int initialValue) {

    printf("Checked that the given sid already exists or not ");
    Semaphore *sem = getSemaphoreFromId(sid);
    if(sem!=NULL){
        printf("FAIL!! Semaphore Already Exists.");
        return -1;
    }
    else{
        printf("SUCCESS!! Added Semaphore to the list");
        Semaphore  newSem;
        newSem.ID = sid;
        newSem.value = initialValue;
        newSem.list=List_create();
        return 0;
    }
}

void SemaphoreP(int sid)
{
    Semaphore *semaphore= getSemaphoreFromId(sid);
    if(semaphore==NULL)
    {
        printf("ERROR!! Semaphore doesn't exist");
        return;
    }
    semaphore->value--;
    if(semaphore->value < 0)
    {
        Node *foundNode;
        runningProcess->state = BLOCKED;
        for(int i=0;i<PRIORITY;i++) {
            COMPARATOR_FN comparator = (COMPARATOR_FN) &compareID;
            foundNode = List_search(readyProcesses[i], comparator, (void *) &runningProcess->ID);
        }
        if(foundNode!= NULL) {
            List_remove(readyProcesses[runningProcess->ID]);
        }
        List_append(semaphore->list,runningProcess);
    }
}

void SemaphoreV(int sid)
{
    Semaphore *semaphore = getSemaphoreFromId(sid);
    semaphore->value++;
    if(semaphore->value <= 0)
    {
        List_first(semaphore->list);
        PCB* processFromRunningToReady = List_remove(semaphore->list);
        processFromRunningToReady->state =  READY;
        List_prepend(readyProcesses[processFromRunningToReady->priority], processFromRunningToReady);
    }
}

Semaphore* getSemaphoreFromId(int sid) {
    Semaphore * temp = List_first(semaphoreQueue);
    for(int i=0;i< List_count(semaphoreQueue);i++)
    {
        if(temp->ID == sid)
            return temp;

        List_next(semaphoreQueue);
    }
    return NULL;
}