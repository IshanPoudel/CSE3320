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
#define MAX_PIDS 15

 struct ListofCommands
  {
    char *command;
    struct ListofCommands *next;
  };

  struct ListofPids
  {
    char *processID;
    struct ListofPids *next;

  };

  struct ListofCommands *head_command;
  struct ListofPids *head_pids;

  int counter;
  int pid_counter;

 



 void print_command()
  {

   

    struct ListofCommands *temp_2 = (struct ListofCommands*) malloc(sizeof(struct ListofCommands));
    temp_2 = head_command;

    int count = 0;

    while(temp_2!=NULL && count < MAX_HISTORY)
    {

      printf("%s\n" , temp_2->command );
      printf("%p\n" , temp_2 ->next);
      temp_2 = temp_2->next;
      count++;

    }


  }
//have a queue for listpids.

  //have a list for commands. 
void stack_commands(char *command_to_add)
{

	struct ListofCommands * temp;
	temp = (struct ListofCommands*) malloc(sizeof(struct ListofCommands));

 

  // printf("Command to add is %s" , command_to_add);
	
  

	// strcpy(temp->command , command_to_add);

  temp->command = strdup(command_to_add);

	temp->next = head_command;
  // printf("%s is added as entry number %d\n" , temp->command , counter);
	head_command= temp;


  
	
}
 

void stack_pid(int pid)
{

  char str[5];
	// printf("I am here\n");


	struct ListofPids * temp;
	temp = (struct ListofPids*) malloc(sizeof(struct ListofPids)); 

  sprintf(str , "%d" , pid);

  printf("PROCESS ID : %s\n" , str);
	
  temp->processID = strdup(str);
	temp->next = NULL;

	

	temp->next = head_pids;
	head_pids= temp;
	printf("%s is added as entry number %d \n" , temp->processID , pid_counter);
  return;
}

  

void print_pid()
  {
    int pid_counter = 0;
    struct ListofPids * temp;
	  temp = (struct ListofPids*) malloc(sizeof(struct ListofPids));

    temp = head_pids;
    printf("List of pid:");
    while(temp!=NULL && pid_counter<MAX_PIDS)

    {
      printf("%s ",temp->processID); 
      temp=temp->next; 
      pid_counter++;  
    }
    printf("\n");


  }


 


int main()
{

  char * command_string = (char*) malloc( MAX_COMMAND_SIZE );
  counter = 0;
  pid_counter = 0;

  head_command = NULL;
  head_pids = NULL;




 
  

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

   



    //Once a child_pid is run succesfully , have it store the history of the function.
    
  

    
        

    if ((strcmp(token[0] , "cd") )==0)
    {

      // stack_commands(command_string);
    
      printf("You changed the directory\n");
      chdir(token[1]);
    }
    else if ((strcmp(token[0] , "listpids") )==0)
    {
      // stack_commands(command_string);

      printf("You are about to get the listpids\n");
      print_pid();
    }
    else if ((strcmp(token[0] , "!") )==0)
    {
      printf("You are about to get the history\n");
      // print_command(); 
    }
    else if ((strcmp(token[0] , "history"))==0)
    {
      print_command();
    }

    else 
    {

     
      

      pid_t child_pid = fork();

      if (child_pid == 0)
      {
        // #Add the token to the command line arg
        char * argument_list[MAX_NUM_ARGUMENTS] ; 

        for( int token_index = 0; token_index < token_count; token_index ++ ) 
        {
          argument_list[token_index] = token[token_index];  
        }

          // Run the argument . Store the status in execvp.
       
        // stack_pid(child_pid);
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

        exit(1);



            
      }

      else if (child_pid==-1)
      {
        printf("Error creating the process");

      }
      else
       // wait for the child function to exit. 
      {
        //in the parent function
        

        // printf("The childs pid is %d" , child_pid);

        int status;
       
        waitpid(child_pid , &status , 0);

        // printf("I am in the parent function.");
        counter++;
        pid_counter++;
        // printf("The current value of the counter is %d \n" , counter);
        printf("The current value of the pid counter is %d\n" , pid_counter);

        stack_commands(command_string);
        stack_pid((int)child_pid);
        // print_command();
        
        
        
        
      }
  }
    
  free( head_ptr );
  }

  
  return 0;
  // e2520ca2-76f3-90d6-0242ac120003
}

//Need to see when to store the command. 
// in the parent class. 
// can't print it.

// Need to see if I am in the same parent. 
// You are in the same parent , the counter is being updated.
