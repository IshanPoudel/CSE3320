#include <stdio.h>
#include <unistd.h>

int main()
{
    int i;

    printf("I am calling a execvp function\n");
    

    //any binary executable file on the PATH environment variable.

    // int execvp(const char* command, char* argv[]);

    // char * commad represents the unix command which is in the unistd.h file
    // , argv[] represents the key arguments, argv[] must end with a null. 

    char* argument_list[] = {"lsh" , "-l" , NULL};

    int  status = execvp("lsh" , argument_list );

    if (status == -1)
    {
        printf("Process did not terminate correctly");
    }
}

