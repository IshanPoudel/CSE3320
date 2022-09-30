#include <sys/types.h>
#include <sys/wait.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(void)
{

    // Declare a pid process.
    pid_t pid = fork();
    // pid_t is a signed integer type which is capable of representing a process ID. 

    // fork()
    // proimary method of process creation. Function creates a new copy called the child , 
    // out of the original process, that is called the parent. 
    
    //Whenver you call fork , both the parent and child process calls it. 

    
    // The pid of the child process is zero

    if (pid == 0)
    {
        sleep(1);
        printf("Hello , you are in the child process. ");
        printf(" Hello World!\n");
        printf("%d\n" , pid);

    }

    else
    {
        //if you are in the parent process

        int status;

        waitpid(pid , &status , 0);
        printf("I am in the parent process");
        fflush(NULL);

        // #int status pointer  points to a location if the child process explicitly returns zero.

        // waitpid suspends the calling process until the system gets status information on the cjild.

        // waitpid suspends the calling process until the system gets status information on the child


    }


    return EXIT_SUCCESS;


}