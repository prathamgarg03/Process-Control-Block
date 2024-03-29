#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "operations.h"
#include "helper.h"

#define MAX_MESSAGE_CHARACTERS 40
#define PRIORITY 3
#define MAX_SEMAPHORES 5

static int PID = 0;
List * readyProcesses[PRIORITY];
PCB * runningProcess;
List * send;
List * receive;
List * messages;
List * semaphoreQueue;


void ListInit() {
    readyProcesses[HIGH] = List_create();
    readyProcesses[NORMAL] = List_create();
    readyProcesses[LOW] = List_create();
    send = List_create();
    receive = List_create();
    messages = List_create();
    semaphoreQueue=List_create();
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
    process->message = malloc(sizeof (char) * MAX_MESSAGE_CHARACTERS);

    if(!runningProcess) {
        process->state = RUNNING;
        runningProcess = process;
    } else {
        List_prepend(readyProcesses[priority], process);
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
            strcpy(receiver->message, message);
            receiver->state = READY;
            List_prepend(readyProcesses[sender->priority], sender);
        } else {
            MessagePacket * msg = malloc(sizeof (MessagePacket));
            msg->content = malloc(sizeof (char *));
            msg->senderID = sender->ID;
            msg->receiverID = id;
            List_prepend(messages, msg);
        }
        sender->state = BLOCKED;
        List_prepend(send, sender);
        printf("Message sent to PID: %d, from PID: %d \n", sender->ID, id);
    } else {
        printf("No sender available to send message.\n");
    }
    ProcessSchedule();
}

void Recieve() {
    if(runningProcess) {
        PCB * receiver = runningProcess;
        if(anyMessage(messages, receiver->ID)) {
            MessagePacket * msg = List_remove(messages);
            int sid = msg->senderID;
            stpcpy(receiver->message, msg->content);
            printf("An inbox message from PID: %d \n%s \n", sid, receiver->message);
            freeMessage(msg);
            List_prepend(readyProcesses[receiver->priority], receiver);
        } else {
            receiver->state = BLOCKED;
            List_prepend(receive, receiver);
            printf("PID: %d, in receive queue. \n", receiver->ID);
        }
    } else {
        printf("No receiver available to receive message.\n");
    }
    ProcessSchedule();
}

void Reply(int id, char * message) {
    if(runningProcess) {
        PCB * reply = runningProcess;
        if(isProcessFound(send, id)) {
            PCB * sender = List_remove(send);
            strcpy(sender->message, message);
            sender->state = READY;
            List_prepend(readyProcesses[sender->priority], sender);
        } else {
            printf("No process available to reply to.\n");
        }
    } else {
        printf("No sender available to reply.\n");
    }
}

void TotalInfo() {
    char* priorityNames[] = {
            "HIGH priority ready",
            "NORMAL priority ready",
            "LOW priority ready"
    };
    for(int i = 0; i < PRIORITY; i++) {
        printList(priorityNames[i] , readyProcesses[i]);
    }

}

int newSemaphore(int sid, int initialValue) {

    printf("Checked that the given sid already exists or not or if the list size is 0\n");
    Semaphore *sem = getSemaphoreFromId(sid);
    if (sem != NULL) {
        printf("FAIL!! Semaphore Already Exists.\n");
        return -1;
    } else {
        printf("SUCCESS!! Added Semaphore to the list\n");
        Semaphore* newSem = malloc(sizeof(Semaphore));
        newSem->ID = sid;
        newSem->value = initialValue;
        newSem->list = List_create();
        List_prepend(semaphoreQueue,newSem);
        return 0;
    }
}

void SemaphoreP(int sid) {
    Semaphore *semaphore = getSemaphoreFromId(sid);
    if (semaphore == NULL) {
        printf("ERROR!! Semaphore doesn't exist\n");
        printf("FAIL\n");
        return;
    }
    semaphore->value--;
    if (semaphore->value < 0) {
        runningProcess->state = BLOCKED;
        printf("Changed the state of currently running process from RUNNING to BLOCKED The Current Process. PID : %d \n",
               semaphore->ID);

        List_prepend(semaphore->list, runningProcess);
        printf("SUCCESS\n");
    }
    ProcessSchedule();
}


void SemaphoreV(int sid) {
    Semaphore *semaphore = getSemaphoreFromId(sid);
    semaphore->value++;
    if (semaphore->value <= 0) {
        List_first(semaphore->list);
        PCB *processFromRunningToReady = List_remove(semaphore->list);
        processFromRunningToReady->state = READY;
        printf("Changed the state from BLOCKED to READY . PID : %d \n", semaphore->ID);

        List_prepend(readyProcesses[processFromRunningToReady->priority], processFromRunningToReady);
    }
}

Semaphore* getSemaphoreFromId(int sid) {

    printf("Finding the Semaphore by its ID and Checking if the Queue is Empty \n");

    if(List_count(semaphoreQueue)==0)
        return NULL;

    Semaphore * temp = List_first(semaphoreQueue);
    for(int i=0;i< List_count(semaphoreQueue);i++)
    {
        if(temp->ID == sid)
            return temp;

        List_next(semaphoreQueue);
    }
    return NULL;
}


void getPIDfromUser() {
    int pid = -1;
    bool isfound = false;

    while (!isfound) {
        printf("Enter the PID of the process you want information about: \n");
        scanf("%d", &pid);

        for (int i = 0; i < PRIORITY; i++) {
            isfound = isProcessFound(readyProcesses[i], pid);
            if (isfound) {
                processInfo(pid);
                break;
            }
        }

        if (!isfound) {
            printf("Process with PID %d not found in any queue. Please try again.\n", pid);
        }
    }
}

PCB *getProcessFromId(int pid) {
    printf("Finding the Process by its ID\n");
    int (*comparator)(void *, void *);
    Node *node;
    PCB *process;

    comparator = &compareID;

    for (int i = 0; i < PRIORITY; i++) {
        List_first(readyProcesses[i]);
        node = List_search(readyProcesses[i], (COMPARATOR_FN) comparator, (void *) &pid);
        if (node) {
            process = (PCB *)node->pItem;
            return process;
        }
    }
    return NULL;
}

void processInfo(int pid) {
    PCB * p_block = getProcessFromId(pid);
    printf("PROCESS ID : %d\n",p_block->ID);
    char* state;
    if(p_block->state==RUNNING)
        state="RUNNING";
    else if(p_block->state == READY)
        state="READY";
    else
        state="BLOCKED";

    printf("PROCESS STATE : %s\n",state);

    char* priority;
    if(p_block->priority==0)
    {
        priority="HIGH PRIORITY LIST";
    }
    else if(p_block->priority==1)
    {
        priority="NORMAL PRIORITY LIST";
    }
    else
    {
        priority="LOW PRIORITY LIST";
    }
    printf("PROCESS IS IN : %s\n",priority);
    printf("PROCESS MESSAGGE : %s\n",p_block->message);
}