#define _GNU_SOURCE

#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <signal.h>
#include <string.h>
#define WHITESPACE " \t\n"      // We want to split our command line up into tokens
                                // so we need to define what delimits our tokens.
                                // In this case  white space
                                // will separate the tokens on our command line

#define MAX_COMMAND_SIZE 255    // The maximum command-line size

#define MAX_NUM_ARGUMENTS 10     // Mav shell only supports four arguments

#define MAX_HISTORY 20

#define MAX_PID 20

 
char listofcommand[MAX_HISTORY][MAX_COMMAND_SIZE];
int command_counter = 0;
int listofPid[MAX_PID];
int pid_counter = 0;
 


void print_command()
{

    printf("Your history is \n\n");

    for (int i=0 ; i<command_counter;i++)
    {
        printf("%s\n" , listofcommand[i]);
    }

}


void print_pid()
{
    printf("The process is is \n\n");
    for (int i=0 ; i<pid_counter;i++)
    {
        printf("%d\n" , listofPid[i]);
    }
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
    else if ((strcmp(token[0] , "showpids") )==0)
    {
      printf("You are about to get the history\n");
      print_command();
      
    }

    else 
    {

      printf("i AM IN THE FUNCTION");
      

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

        // int status;
       
        // waitpid(child_pid , &status , 0);

        printf("I am in the parent function.");

        if (pid_counter < MAX_PID)
        {
            listofPid[pid_counter++] = child_pid;
            printf("Added %d\n" , child_pid);
            
        }

        if (command_counter<MAX_HISTORY)
        {
            // *listofcommand[command_counter] = *command_string;
            // printf("Added %s \n" , listofcommand[command_counter]);
            printf("Adding %s\n" , command_string);
            strcpy(listofcommand[command_counter] , command_string);
           
            command_counter++;

        }

        int status;
        waitpid(child_pid , &status , 0);
        
        
        
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
