#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <signal.h>
#ifdef __linux__
    #include <sys/prctl.h>
#endif

typedef struct {
    pid_t pid;
    int pipeinfd[2];
    int pipeoutfd[2];
    char *buf;
    int status;
} process;

int create_process(char *command, process *new_process);
int read_process(process *process);
int write_process(process *process, char *input);
