/*
Name : Ishan Poudel
ID: 1001838432

*/



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

#define MAX_HISTORY 15
#define MAX_PIDS 20

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
    /*

    print_command() 
    Parameters: None
    Goes through the ListofCommands stack data and prints the first 15 elements in the stack 
    (which is the last 15 commands entered by the user)

    */
    
    struct ListofCommands *temp_2 = (struct ListofCommands*) malloc(sizeof(struct ListofCommands));
    temp_2 = head_command;

    int count = 0;
    // have an array to store values becuase you want to print the stack in the reverse way
    char *commandList[MAX_HISTORY];
    
    while(temp_2!=NULL && count < MAX_HISTORY)
    {
      commandList[count++] = strdup(temp_2->command);
      temp_2 = temp_2->next; 
    }
    
     // counter is the global count of all commands. We want to start from the last value , as that is the first value in the stack
    int local_counter = counter;
    // if there are more than 15 elements in the stack , get only the first 15 in the stack , which will be the last 15 entered
    if (counter > MAX_HISTORY)
    {
      local_counter = MAX_HISTORY;
    }

    //iterate through the stack 
    for (int i=local_counter-1;i>=0; i--)
    {
       printf("%d : %s \n" , local_counter-i-1 , commandList[i]);
    }
  }

void stack_commands(char *command_to_add)
{

  /*
  Parameter: String pointer which contains the command the user entered.
  Adds the string to the ListofCommands data structure.

  */
  //Declare a temporary node to store value
	struct ListofCommands * temp;
	temp = (struct ListofCommands*) malloc(sizeof(struct ListofCommands));

  temp->command = strdup(command_to_add);
  temp->next = head_command;
  
  // store the temp node as the first element
	head_command= temp;

  //Increase the global counter
  counter++;
}
 

void stack_pid(int pid)
{

  /*
  Parameters: interer value which contains the process id of a process.
  Stacked into the ListofPids data structure. 
  */

  

  char str[6];
	
  // Declare a temp struct to store the pid . The pid is converted to char.
	struct ListofPids * temp;
	temp = (struct ListofPids*) malloc(sizeof(struct ListofPids)); 

  sprintf(str , "%d" , pid);
	
  temp->processID = strdup(str);
	temp->next = head_pids;
  // Declare the temp struct as the head.
	head_pids= temp;

	//Increase the pid counter
  pid_counter++;
  return;
}

  

void print_pid()
  {

    /*
    prints the last 20 process's pid value.
    */
    
    
    struct ListofPids * temp;
	  temp = (struct ListofPids*) malloc(sizeof(struct ListofPids));

    //Have an array to store the values because you wanted it printed the reverse way
    char *pidList[MAX_PIDS];

    temp = head_pids;
    int local_counter = 0;
    
    //Go through the stack and store each value in the array
    while(temp!=NULL && local_counter<MAX_PIDS)

    {
      pidList[local_counter++] = temp->processID;  
      temp=temp->next;   
    }
  
    // print through the array list
    local_counter = pid_counter;
    if (pid_counter> MAX_PIDS)
    {
      local_counter = MAX_PIDS;
    }

    //now that you have the value. 
    for (int i=local_counter-1;i>=0; i--)
    {
      printf("%d : %s \n" , local_counter-i-1 , pidList[i]);
    }
      


  }


char* getCommand(int num)
{

  /*
  Parameter : nth command. 
  Return the nth command entered by the user.
  */

  // Create an array to store stack value.
  char *cmdList[MAX_HISTORY];

  int a =0;
  // Declare a variable , which will get the nth command.
  char *cmdReturn = malloc(MAX_COMMAND_SIZE);

  struct ListofCommands *temp_3 = (struct ListofCommands*) malloc(sizeof(struct ListofCommands));
  temp_3 = head_command;
  //Create an array
  while (temp_3!=NULL)
  {
     cmdList[a++] = strdup(temp_3->command);
     temp_3 = temp_3->next; 
  }

 
  int local_counter = counter;
  if (counter > 15)
  {
      local_counter = 15;
  }

  //return the value from the array list. 
  // nth number as specified by the user would be local_counter-num-1th item in the stack
  return cmdList[local_counter-num-1];
}


int main()
{

  char * command_string = (char*) malloc( MAX_COMMAND_SIZE );

  //Initialize command_counter and pid_counter to zero
  counter = 0;
  pid_counter = 0;
  
  //Initialize the head pointers of linkedlist to zero
  head_command = NULL;
  head_pids = NULL;

  int sendFromHistory = 0;


  //These two are needed if we nened to tokenize from history 
  char *storage_token[MAX_COMMAND_SIZE];
  // Declare a counter
  int count_tokens = 0;

  

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

    // for (int i=0; i<token_count;i++)
    // {
    //   printf("%s\n" , &token[token_count]);
    // }

    // printf("%s\n" , token[token_count]);    // \TODO Remove this code and replace with your shell functionality

    //5. quit function
   
    if ((strcmp(token[0] , "quit") )==0 || (strcmp(token[0] , "exit") )==0)
    {
      printf("I/m about to quit");

      exit(EXIT_SUCCESS);
    }

  
    if ((strcmp(token[0] , "cd") )==0)
    {
      stack_commands(command_string);
      chdir(token[1]);
    }
    else if ((strcmp(token[0] , "listpids") )==0)
    {
      stack_commands(command_string);
      print_pid();
    }
    else if ((strcmp(token[0] , "history"))==0)
    {
      stack_commands(token[0]);
      print_command();
      
    }
    else if (command_string[0] == '!')
    {
      
      // get which index we want to store
      int num = atoi(&command_string[1]); 
      if (num > counter || num > 15)
      {
        printf("Invalid choice \n");
        continue;
      }
    

      char st[MAX_COMMAND_SIZE];
      //call the getCommand function to return the command at the nth position.
      strcpy(st , getCommand(num));
      
      // have a copy of the command before we tokenize
      char cmd_copy[MAX_COMMAND_SIZE];
      strcpy(cmd_copy , st);

      //tokenize the input

      
      char *token_2; 
      token_2  = strtok(st , WHITESPACE);

      // Declaring a char array to store all the values from the tokenizer.
      while (token_2 != NULL)
      {
        storage_token[count_tokens++]= strdup(token_2);
        token_2 = strtok(NULL , WHITESPACE);
      }

      storage_token[count_tokens] = NULL;

      

      // fork a child here and stack it.
      pid_t child_pid = fork();
      if (child_pid == 0)
      {
        int status = execvp(storage_token[0] , storage_token);
        if (status == -1)
        {
            printf("%s : Command not found\n" , cmd_copy );
        }
        exit(1);
      }
      else
      {
        int status;
       
        waitpid(child_pid , &status , 0);
        // printf("I am about to stack from the history command\n");
        stack_commands(cmd_copy);
        stack_pid(child_pid);
      }

      //clear store_token
      count_tokens = 0;
    }
    
    else 
    {
      //fork a process
      pid_t child_pid = fork();

      if (child_pid == 0)
      {
        // Run the argument . Store the status in execvp.
      
        int status = execvp(token[0] , token);

        if (status == -1)
        {
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
      

        int status;
       
        waitpid(child_pid , &status , 0);

        

        stack_commands(command_string);
        stack_pid((int)child_pid); 
      }
  }
    
  free( head_ptr );
  }

  
  return 0;
  // e2520ca2-76f3-90d6-0242ac120003
}
