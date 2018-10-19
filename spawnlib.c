#include "spawnlib.h"

int create_process(char *command, process *new_process) {
    //puts("creating process");
    int flags;
    pipe(new_process->pipeinfd);
    pipe(new_process->pipeoutfd);
    new_process->pid = fork();
    //printf("pid: %d\n", new_process->pid);
    if (new_process->pid < 0) {
        puts("failed to fork process");
        return -1;
    } else if (new_process->pid == 0) {
        //puts("child");
        flags = fcntl(new_process->pipeinfd[0], F_GETFL);
        if (flags == -1) {
            puts("fcntl get failed");
            exit(1);
        }
        flags |= O_NONBLOCK;
        if (fcntl(new_process->pipeinfd[0], F_SETFL, flags)) {
            puts("fcntl get failed");
            exit(1);
        }
        close(new_process->pipeoutfd[1]);
        close(new_process->pipeinfd[0]);
        dup2(new_process->pipeoutfd[0], STDIN_FILENO);
        dup2(new_process->pipeinfd[1], STDOUT_FILENO);
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
    int nread, len;
    char *new = (char *) malloc( 21 * sizeof (char));
    process->buf = (char *) malloc( 21 * sizeof (char));
    len = 0;
    while ((nread = read(process->pipeinfd[0], new, 20)) > 0) {
        len += nread;
        process->buf = realloc(process->buf, len+1);
        process->buf = strncat(process->buf, new, len);
    }
    return 0;
}

int write_process(process *process, char *input) {
    write(process->pipeoutfd[1], input, strlen(input));
    return 0;
}
    
