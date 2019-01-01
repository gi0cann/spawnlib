#include <string.h>
#include <sys/wait.h>
#include "spawnlib.h"

int main()
{
    process test_proc;
    int create_process_result;
    int bytes_read;
    test_proc.status = 0;
    //create_process_result = create_process("./hello", &test_proc);
    create_process_result = create_process("./proce.py", &test_proc);
    if (create_process_result == -1)
        exit(1);
    if (test_proc.status == -1)
        exit(1);
    
    // write to process
    process_write(&test_proc, "test");
    // write to process with new line
    process_writeline(&test_proc, "test");
    // read n bytes from process
    process_read(&test_proc, 3);
    printf("%s\n", test_proc.buf);
    // read until a match if found
    process_readuntil(&test_proc, "to");
    printf("%s\n", test_proc.buf);
    // read until newline character
    process_readline(&test_proc);
    printf("%s\n", test_proc.buf);
    // read until buffer is empty
    process_readall(&test_proc);
    printf("%s\n", test_proc.buf);
    free(test_proc.buf);

    /*kill(test_proc.pid, SIGKILL);
    waitpid(test_proc.pid, &test_proc.status, 0);*/
    return 0;
}
