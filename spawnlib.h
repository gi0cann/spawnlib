#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <signal.h>
#include <string.h>
#include <sys/select.h>
#include <fcntl.h>
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
int process_read(process *process, int len);
int process_readline(process *process);
int process_readuntil(process *process, char *end);
int process_readall(process *process);
int process_write(process *process, char *input);
int process_writeline(process *process, char *input);
