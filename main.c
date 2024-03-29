#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include "string.h"
#include "operations.h"

int main() {
//e,k,f,c
    ListInit();
    char command;
    do {
        printf("\n-------------------------------------------------\n");
        printf("C - Create \n");
        printf("F - Fork \n");
        printf("K - Kill \n");
        printf("E - Exit \n");
        printf("Q - Quantum \n");
        printf("S - Send \n");
        printf("R - Receive \n");
        printf("Y - Reply \n");
        printf("N - New Semaphore \n");
        printf("P - Semaphore P \n");
        printf("V - Semaphore V \n");
        printf("I - Process Information \n");
        printf("T - Total Information \n");
        printf("X - Exit Program \n");
        printf("Enter Command: \n");

        scanf(" %c", &command);
        command = toupper(command);
        switch (command) {
            case 'C': {
                printf("Create \n");
                printf("create a process and put it on the appropriate ready Queue.\n");
                int priority = 0;
                do {
                    printf("Enter Priority: ");
                    scanf(" %d", &priority);
                } while (priority != HIGH && priority != NORMAL && priority != LOW);
                int id = Create(priority);
                printf("PID: %d \n", id);
                printf("SUCCESS!! A New Process Was Created.\n");
                break;
            }
            case 'F': {
                printf("Fork\n");
                printf("Copy the currently running process and put it on the ready Q corresponding to the original process' priority.\n");
                int id = Fork();
                printf("PID: %d \n", id);
                printf("SUCCESS\n");
                break;
            }
            case 'K': {
                printf("Kill\n");
                printf("Kill the named process and remove it from the system.\n");
                printf("PID to remove: ");
                int p = -1;
                scanf(" %d", &p);

                int isKill = Kill(p);
                if (isKill == -1)
                    printf("FAIL!! The PID did not Exist.\n");
                else
                    printf("SUCCESS!! The PID Process was Killed.\n");
                break;
            }
            case 'E': {
                printf("Exit\n");
                printf("Kill the currently running process.\n");
                int id = Exit();
                printf("Killed PID: %d \n", id);
                if (id == -1)
                    printf("FAIL!! The Current Process was not Killed.\n");
                else
                    printf("SUCCESS!! The Current Process was Killed.\n");
                break;
            }
            case 'Q' : {
                printf("Quantum\n");
                printf("Time quantum of running process expires.\n");
                Quantum();
                break;
            }
            case 'S': {
                printf("Send\n");
                printf("send a message to another process - block until reply\n");
                printf("PID to send: ");
                int p = -1;
                scanf(" %d", &p);
                printf("Message to send: ");
                char *message = malloc(sizeof(char *));
                scanf("40%s", message);
                Send(p, message);
                free(message);
                break;
            }
            case 'R': {
                printf("Receive\n");
                printf("receive a message - block until one arrives\n");
                Recieve();
                break;
            }
            case 'Y': {
                printf("Reply\n");
                printf("unblocks sender and delivers reply\n");
                printf("PID to send: ");
                int p = -1;
                scanf(" %d", &p);
                printf("Message to send: ");
                char *message = malloc(sizeof(char *));
                scanf("40%s", message);
                Reply(p, message);
                free(message);
                break;
            }
            case 'T': {
                printf("Total Info\n");
                printf("display all process queues and their contents\n");
                TotalInfo();
                break;
            }
            case 'N': {
                printf("New Semaphore\n");
                int sid = -1;
                int initialValue = -1;
                do {
                    printf("Enter the Semaphore ID (Between 0 to 4) : \n");
                    scanf("%d", &sid);
                } while (sid > 4 || sid < 0);

                do {
                    printf("\nEnter the Initial Value for the Semaphore (0 or Higher): \n");
                    scanf("%d", &initialValue);
                } while (initialValue < 0);
                newSemaphore(sid, initialValue);
                break;
            }
            case 'P': {
                printf("Semaphore P\n");
                int sid = -1;
                do {
                    printf("Enter the Semaphore ID (Between 0 to 4) : \n");
                    scanf("%d", &sid);
                } while (sid > 4 || sid < 0);
                SemaphoreP(sid);
                break;
            }
            case 'V': {
                printf("Semaphore V\n");
                int sid = -1;
                do {
                    printf("Enter the Semaphore ID (Between 0 to 4) : \n");
                    scanf("%d", &sid);
                } while (sid > 4 || sid < 0);
                SemaphoreV(sid);
                break;
            }
            case 'I': {
                printf("Process Info:\n");
                getPIDfromUser();
                break;
            }
            default: {
                printf("Invalid Argument.\n");
                break;
            }

        }


    } while (command != 'X');

//    free(ready[HIGH]);
//    free(ready[NORMAL]);
//    free(ready[LOW]);
    return 0;
}