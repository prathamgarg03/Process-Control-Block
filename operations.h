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

#endif