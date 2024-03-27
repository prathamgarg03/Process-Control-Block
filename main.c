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
            case 'A':
            {
                int priority = 0;
                do {
                    printf("Enter Priority: ");
                    scanf(" %d", &priority);
                } while (priority != HIGH && priority != NORMAL && priority != LOW);
                addToRunningProc(priority);
                break;
            }
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
                printf("pid to remove: ");
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
            case 'Q' :
            {
                printf("Quantum\n");
                Quantum();
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
