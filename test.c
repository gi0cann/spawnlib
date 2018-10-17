#include <string.h>
#include <sys/wait.h>
#include "spawnlib.h"

int main()
{
    process test_proc;
    int create_process_result;
    int bytes_read;
    test_proc.status = 0;
    create_process_result = create_process("./hello", &test_proc);
    if (create_process_result == -1)
        exit(1);
    if (test_proc.status == -1)
        exit(1);

    read_process(&test_proc);
    printf("%s\n", test_proc.buf);
    printf("total bytes: %ld\n", strlen(test_proc.buf));
    free(test_proc.buf);

    /*kill(test_proc.pid, SIGKILL);
    waitpid(test_proc.pid, &test_proc.status, 0);*/
    return 0;
}
