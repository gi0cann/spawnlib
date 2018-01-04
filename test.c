#include <string.h>
#include <sys/wait.h>
#include "spawnlib.h"

int main()
{
    process test_proc;
    int create_process_result;
    test_proc.status = 0;
    create_process_result = create_process("/bin/ls", &test_proc);
    if (create_process_result == -1)
        exit(1);
    if (test_proc.status == -1)
        exit(1);

    read(test_proc.pipeinfd[0], test_proc.buf, 20);
    printf("%s\n", test_proc.buf);

    kill(test_proc.pid, SIGKILL);
    waitpid(test_proc.pid, &test_proc.status, 0);
    return 0;
}
