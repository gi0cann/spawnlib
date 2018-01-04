#include "process.h"

int create_process(char *command, process *new_process) {
    //puts("creating process");
    pipe(new_process->pipeinfd);
    pipe(new_process->pipeoutfd);
    new_process->pid = fork();
    //printf("pid: %d\n", new_process->pid);
    if (new_process->pid < 0) {
        puts("failed to fork process");
        return -1;
    } else if (new_process->pid == 0) {
        //puts("child");
        close(new_process->pipeoutfd[1]);
        close(new_process->pipeinfd[0]);
        dup2(new_process->pipeoutfd[0], STDIN_FILENO);
        dup2(new_process->pipeinfd[1], STDOUT_FILENO);

        prctl(PR_SET_PDEATHSIG, SIGTERM);
        //puts("trying to replace process");
        execl(command, "tee", (char *) NULL);
        //puts("execl failed");
        exit(1);
        return 0;
    } else {
        //puts("process forked");
        return 0;
    }
    return 0;
}

int read_process(process *process) {
    return 0;
}

int write_process(FILE *process, char *input) {
    return 0;
}
    
