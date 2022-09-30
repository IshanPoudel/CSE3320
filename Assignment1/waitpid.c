#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdio.h>
#include <string.h>


int main(void)
{

    pid_t pid = fork();
    int status;

    if (pid == 0)
    {
        sleep(1);

        printf("I am in the child process");

        // intentionally segfault the child process. 
        int *p = NULL;
        *p = 1;

        exit(EXIT_SUCCESS);



    }
    

    // wait for the child to exit. 

    waitpid(pid , &status , 0);

    // #See if the  child was terminated by a signal.
    if (WIFSIGNALED(status))
    {
        printf( "Child returned with status %d\n" , WTERMSIG(status) );
    }

    return 0;




}