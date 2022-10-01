 #define _GNU_SOURCE

#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <signal.h>
 
 struct ListofCommands
  {
    char *command;
    struct ListofCommands *next;
  };

struct ListofCommands *head_command;

void stack_commands(char *command_to_add)
{

	// printf("I am here\n");
    
    struct ListofCommands * temp;
    temp = (struct ListofCommands*) malloc(sizeof(struct ListofCommands));
    
    temp->command = command_to_add;
    temp->next = NULL;

    if (head_command == NULL)
    {
        head_command = temp;
        printf("%s is added as the first entry \n", head_command->command );
        return;
    }
    
    temp->next = head_command;
    head_command= temp;
    printf("%s is added\n" , head_command->command);

  // #When you add a pointer the head has got to return back to the top
  return;
}


void print_command()
  {

    struct ListofCommands *temp = (struct ListofCommands*) malloc(sizeof(struct ListofCommands));
    temp = head_command;

    while (temp!=NULL)
    {

      printf("%s \n" , temp->command );
      temp = temp->next;

    }


  }




int main()
{

    int a = 1;

    

    stack_commands("abc");
    stack_commands("bcd");
    stack_commands("aef");

    print_command();

    return 0;

}