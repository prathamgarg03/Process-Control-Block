#ifndef A3_DATA_STRUCTURE_H
#define A3_DATA_STRUCTURE_H

#include "list.h"

enum ProcessPriority {
    HIGH,
    NORMAL,
    LOW
};

enum ProcessState {
    RUNNING,
    READY,
    BLOCKED
};

typedef struct {
    char * content;
    int senderID;
    int receiverID;
} Message;

typedef struct {
    int ID;
    enum ProcessPriority priority;
    enum ProcessState state;
    Message * message;
} PCB;

typedef struct {
    int ID;
    int value;
    List * list;
} Semaphore;

#endif
