#include "spawnlib.h"

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
        
        #ifdef __linux__
        prctl(PR_SET_PDEATHSIG, SIGTERM);
        #endif
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
    int bytes_read = 0;
    int bytes_to_read = 21;
    int total_read = 0;
    int rv;
    fd_set set;
    struct timeval timeout;
    timeout.tv_sec = 6;
    timeout.tv_usec = 0;
    process->buf = (char *) malloc(21 * sizeof (char));
    memset(process->buf, 0, 21);
    while ((bytes_read = read(process->pipeinfd[0], (process->buf + total_read), 20)) > 0) {
        rv = select(process->pipeinfd[0], &set, NULL, NULL, &timeout);
        if (rv == -1) {
            puts("select failed");
        } else if (rv == 0) {
            puts("timeout");
            printf("timeout totalread: %d\n", total_read);
        }
        printf("bytes read: %d\n", bytes_read);
        total_read += bytes_read;
        if (bytes_read == 0) {
            break;
        } else if (bytes_read < 20) {
            process->buf[total_read] = '\0';
            break;
        } else {
            process->buf = realloc(process->buf, (total_read + 21) * sizeof (char));
        }
    }
    return 0;
}

int write_process(process *process, char *input) {
    return 0;
}
    
