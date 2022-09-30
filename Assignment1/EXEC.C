#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdio.h>


int main(void)
{
    pid_t child_pid = fork();
    int status;

    if(child_pid==0)
    {
        execl("/bin/ls" , "ls" , NULL);
        exit(EXIT_SUCCESS);
    }

    // #wait for the child process to stop.
    waitpid(child_pid , &status , 0);

    return 0;

}