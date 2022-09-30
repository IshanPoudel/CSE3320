#include <stdio.h>
#include <unistd.h>

int main()
{
    char* command = "ls";
    char * argument_list[] = {"ls" , "-l" , NULL};

    printf("Before calling execevp()\n");

    printf("Creating another process using fork().......\n");

    for (int i=0 ; i<10; i++)
    {
         pid_t child_pid = 0;
         child_pid = fork();


        if (child_pid == 0)
        {
            // new process created.

            // #execvp

            int status_code = execvp(command , argument_list);




        }

    }



   
}