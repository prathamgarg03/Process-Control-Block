#ifndef ASSIGNMENT3_HELPER_H
#define ASSIGNMENT3_HELPER_H

#include "list.h"
#include "data_structure.h"
#include "stdio.h"

bool isProcessFound(List *, int);
int freeProcess(PCB *);
bool anyMessage(List *, int);
char* freeMessage(MessagePacket *);
void printList(char *, List *);
bool isSemaphoreFound(List *, int);
void printInfo(PCB *, int);

#endif
