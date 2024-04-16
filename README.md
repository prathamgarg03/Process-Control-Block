# Process-Control-Block

This project is a simulation of a process scheduler in a multitasking operating system. It is implemented in C language and uses a priority-based scheduling algorithm.

## Getting Started

These instructions will get you a copy of the project up and running on your local machine for development and testing purposes.

### Prerequisites

- A C compiler (like gcc)
- A text editor or an IDE (like CLion)

### Installing

1. Clone the repository to your local machine.
2. Open the project in your preferred text editor or IDE.
3. Compile the project using your C compiler.

## Usage

The project simulates a process scheduler with different operations such as creating a process, scheduling a process, sending and receiving messages between processes, and semaphore operations.

The main operations include:

- `Create(int priority)`: Creates a new process with the given priority.
- `Fork()`: Creates a new process with the same priority as the currently running process.
- `Kill(int id)`: Terminates the process with the given id.
- `Exit()`: Terminates the currently running process.
- `Quantum()`: Moves the currently running process to the ready queue and schedules the next process.
- `Send(int id, char * message)`: Sends a message to the process with the given id.
- `Receive()`: Receives a message from another process.
- `Reply(int id, char * message)`: Replies to a message from the process with the given id.
- `newSemaphore(int sid, int initialValue)`: Creates a new semaphore with the given id and initial value.
- `SemaphoreP(int sid)`: Decrements the semaphore value and blocks the process if the value is less than zero.
- `SemaphoreV(int sid)`: Increments the semaphore value and unblocks a process if any are blocked.
- `getPIDfromUser()`: Prompts the user to enter a process id and displays information about the process.
- `processInfo(int pid)`: Displays information about the process with the given id.
- `TotalInfo()`: Displays information about all processes in the system.

Sure, you can add the following section to your README file to guide users on how to run the program:

## Running the Program

1. Open a terminal window.
2. Navigate to the project directory using the `cd` command.
3. Compile the program using the `gcc` compiler. For example, if your main file is `main.c`, you would type:
```bash
gcc -o main main.c operations.c helper.c list.o
```
4. Run the program by typing `./main`.

Please replace `main.c`, `operations.c`, and `helper.c` with the actual names of your C files. If there are more C files in your project, add them to the `gcc` command.

This assumes that the user has `gcc` installed and in their system's PATH. If not, they would need to install it first.
