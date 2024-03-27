#ifndef ASSIGNMENT3_OPERATIONS_H
#define ASSIGNMENT3_OPERATIONS_H

#include "data_structure.h"

void ListInit();
void addToRunningProc(int priority);
int Create(int);
int Fork();
int Kill(int);
int Exit();
void Quantum();

#endif
