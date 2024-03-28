#ifndef ASSIGNMENT3_OPERATIONS_H
#define ASSIGNMENT3_OPERATIONS_H

#include "data_structure.h"

void ListInit();
//void addToRunningProc(int priority);
int Create(int);
int Fork();
int Kill(int);
int Exit();
void Quantum();
void Send(int, char *);
int Send(int pid, char* msg);
void Receive();
int newSemaphore(int sid,int initialValue);
void SemaphoreP(int sid);
void SemaphoreV(int sid);
Semaphore* getSemaphoreFromId(int sid);
#endif