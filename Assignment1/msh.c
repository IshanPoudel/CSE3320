#define _GNU_SOURCE

#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <signal.h>

#define WHITESPACE " \t\n"      // We want to split our command line up into tokens
                                // so we need to define what delimits our tokens.
                                // In this case  white space
                                // will separate the tokens on our command line

#define MAX_COMMAND_SIZE 255    // The maximum command-line size

#define MAX_NUM_ARGUMENTS 10     // Mav shell only supports four arguments

#define MAX_HISTORY 20

 struct ListofCommands
  {
    char *command;
    struct ListofCommands *next;
  };


  struct ListofPids
  {
    pid_t pid;
    struct ListofPids *next;

  };

  struct ListofCommands *head_command;
  struct ListofPids *head_pids;


  void stack_commands(char *command_to_add){
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
  return;
  }

  void stack_pid(pid_t pid)
  {
	// printf("I am here\n");

	struct ListofPids * temp;
	temp = (struct ListofPids*) malloc(sizeof(struct ListofPids));
	
  temp->pid = pid;
	temp->next = NULL;

	if (head_pids== NULL)
	{
		head_pids = temp;
		printf("%d is added as the first entry \n", head_pids->pid );
		return;
	}

	temp->next = head_pids;
	head_pids= temp;
	printf("%d is added\n" , head_pids->pid);
  return;
  }

  void print_command()
  {
    struct ListofCommands * temp;
	  temp = (struct ListofCommands*) malloc(sizeof(struct ListofCommands));
    printf("List of commands:");
    while(temp!=NULL)

    {
      printf("%s ",temp->command); 
      temp=temp->next;   
    }
    printf("\n");


  }

   void print_pid()
  {
    struct ListofPids * temp;
	  temp = (struct ListofPids*) malloc(sizeof(struct ListofPids));
    printf("List of pid:");
    while(temp!=NULL)

    {
      printf("%d ",temp->pid); 
      temp=temp->next;   
    }
    printf("\n");


  }


 


int main()
{

  



  

 

  




  char * command_string = (char*) malloc( MAX_COMMAND_SIZE );

 
  

  while( 1 )
  {
    
    // Print out the msh prompt
    printf ("msh> ");

    // Read the command from the commandline.  The
    // maximum command that will be read is MAX_COMMAND_SIZE
    // This while command will wait here until the user
    // inputs something since fgets returns NULL when there
    // is no input


    // Pointer to point to the token
    // parsed by strsep
    char *argument_ptr;                                         
    while( !fgets (command_string, MAX_COMMAND_SIZE, stdin) );

    /* Parse input */
    char *token[MAX_NUM_ARGUMENTS];

    int   token_count = 0;                                 
    char *working_string  = strdup( command_string );                

    // we are going to move the working_string pointer so
    // keep track of its original value so we can deallocate
    // the correct amount at the end
    char *head_ptr = working_string;

     if ( command_string[0] == '\n')
     {
     continue;
     }

    // Tokenize the input strings with whitespace used as the delimiter
    while ( ( (argument_ptr = strsep(&working_string, WHITESPACE ) ) != NULL) && 
              (token_count<MAX_NUM_ARGUMENTS))
    {
      token[token_count] = strndup( argument_ptr, MAX_COMMAND_SIZE );
      if( strlen( token[token_count] ) == 0 )
      {
        token[token_count] = NULL;
      }
        token_count++;
    }

    // Now print the tokenized input as a debug check
    // \TODO Remove this code and replace with your shell functionality

    int token_index  = 0;
    for( token_index = 0; token_index < token_count; token_index ++ ) 
    {
      printf("token[%d] = %s\n", token_index, token[token_index] );  
    }

    //Once you get the token.
    //fork process. 

    //5. quit function
    char quit[] = "quit";

    int result = strcmp(token[0] , quit);

    if (result == 0)
    {

      exit(EXIT_SUCCESS);

    }

    pid_t child_pid = fork();



    //Once a child_pid is run succesfully , have it store the history of the function.
    
    int a = 0;

    if (child_pid == 0)
    {
        a = a+1;
        printf("%d" , a);
        
        printf(" Created a process. %d\n" ,  getpid());

        // Store the ppid in a stack. Last in First Out. 
        stack_pid(getpid());
        stack_commands(command_string);
        print_command();
        print_pid();

        if ((strcmp(token[0] , "cd") )==0)
        {

          stack_commands(command_string);
        
          printf("You changed the directory\n");
          chdir(token[1]);
        }

        else if ((strcmp(token[0] , "listpids") )==0)
        {
          stack_commands(command_string);

          printf("You are about to get the listpids\n");
        }
        else if ((strcmp(token[0] , "!") )==0)
        {
          printf("You are about to get the history\n");

        }

        else 
        {
          printf("I am in the actual function\n");

          // #Add the token to the command line arg
          char * argument_list[MAX_NUM_ARGUMENTS] ; 

          for( int token_index = 0; token_index < token_count; token_index ++ ) 
          {
            argument_list[token_index] = token[token_index];  
          }


          //have a queue for listpids.

          //have a list for commands. 

          stack_commands(command_string);

          


          // Run the argument . Store the status in execvp.
          int status = execvp(argument_list[0] , argument_list);


          //find a way to get the parent_ppid after execvp has been called. 
          //  Before you call ececvp , store it in a struct//linked list.

          if (status == -1)
          {
              //if command failed.
              //remove the process id
              //
              printf("%s : Command not found\n" , command_string );

          }

        }
        

        
    }
    else
    {
        // wait for the child function to exit. 
        
        int status;
        printf("%d" , a);
        waitpid(child_pid , &status , 0);
    }

    free( head_ptr );

  }
  return 0;
  // e2520ca2-76f3-90d6-0242ac120003
}