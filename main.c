#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include "operations.h"

int main() {

    ListInit();
    char command;
    do {
        printf("Enter Command: ");
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
                break;
            }
            case 'F': {
                printf("Fork\n");
                printf("Copy the currently running process and put it on the ready Q corresponding to the original process' priority.\n");
                Fork();
                break;
            }
            case 'K': {
                printf("Kill\n");
                printf("kill the named process and remove it from the system.\n");
                printf("PID to remove: ");
                int p = -1;
                scanf(" %d", &p);

                Kill(p);
                break;
            }
            case 'E': {
                printf("Exit\n");
                printf("kill the currently running process.\n");
                int id = Exit();
                printf("Killed PID: %d \n", id);
                break;
            }
            case 'Q' : {
                printf("Quantum\n");
                printf("time quantum of running process expires.\n");
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
                char * message = "Hello123";
//                scanf(" %s", message);
                Send(p, message);
            }
            case 'N':
            {
                printf("New Semaphore\n");
                int sid= -1;
                int initialValue=-1;
                do {
                    printf("Enter the Semaphore ID (Between 0 to 4) : \n");
                    scanf("%d", &sid);
                }while(sid > 4 || sid < 0);

                do {
                    printf("\n Enter the Initial Value for the Semaphore (0 or Higher): \n");
                    scanf("%d", &initialValue);
                }while(initialValue < 0);
                newSemaphore(sid,initialValue);
                break;
            }
            case 'P':
            {
                printf("Semaphore P\n");
                int sid= -1;
                do {
                    printf("Enter the Semaphore ID (Between 0 to 4) : \n");
                    scanf("%d", &sid);
                }while(sid > 4 || sid < 0);
                SemaphoreP(sid);
                break;
            }
            case 'V':
            {
                printf("Semaphore P\n");
                int sid= -1;
                do {
                    printf("Enter the Semaphore ID (Between 0 to 4) : \n");
                    scanf("%d", &sid);
                }while(sid > 4 || sid < 0);
                SemaphoreV(sid);
                break;
            }
            case 'I':
            {
                printf("Process Info:\n");
                getPIDfromUser();
                break;
            }
            case 'T':
            {
                totalInfo();
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