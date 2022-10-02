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
        
        return;
    }
    
    temp->next = head_command;
    head_command= temp;

    printf("\n\n Current Stack \n\n");
    struct ListofCommands * temp2 = (struct ListofCommands*) malloc(sizeof(struct ListofCommands));
    temp2= head_command;

    while(temp2!=NULL)
    {
      printf("%s\n" , temp2->command);
      printf("%p\n" , temp2->next);
      temp2 = temp2->next;
    }
    
    return;
}
   

  // #When you add a pointer the head has got to return back to the top
 



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
    stack_commands("ls_b");
    stack_commands("ls -a");
    print_command();

    

   
   
    return 0;

}