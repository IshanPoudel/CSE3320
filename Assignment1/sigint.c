#include <stdio.h>
#include <unistd.h>
#include <signal.h>
#include <string.h>

static void handle_signal(int sig)
{
    printf("Caught signal %d\n" , sig);
}

int main(int argc , char *argv[])
{

    struct sigaction act;
    // 
    // *(sa_handler int)
    // *sa_sigaction (int , siginfo_t * )
    // sigset_r sa_mask;

    memset(&act , '\0' , sizeof(act));
    // Copies the  character c to the fisrt n characters of the string pointed to , by the argument str

    // sets everything to null

    act.sa_handler = &handle_signal;

    // act.sa_handler gets the handle signal function

    if (sigaction(SIGINT , &act , NULL)<0)
    {
        perror("sigaction:");
        return 1;
    }

    while(1)
    {
        sleep(1);
    }

    return 0;



}