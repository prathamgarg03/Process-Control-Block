#ifndef ASSIGNMENT3_OPERATIONS_H
#define ASSIGNMENT3_OPERATIONS_H

#include "data_structure.h"

void ListInit();
int Create(int);
int Fork();
int Kill(int);
int Exit();
void Quantum();
void Send(int, char *);
void Recieve();
void Reply(int, char *);
void TotalInfo();
int newSemaphore(int sid,int initialValue);
void SemaphoreP(int sid);
void SemaphoreV(int sid);
void getPIDfromUser();
void processInfo(int pid);

#endif
