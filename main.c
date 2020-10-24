//Patrick Stumbaugh
//"smallsh", Portfolio Project, Assignment 3 


#include<stdio.h> 
#include<string.h> 
#include<stdlib.h> 
#include<unistd.h> 
#include<sys/types.h> 
#include<sys/wait.h> 

#define MAX 100

//FUNCTION DECLARATIONS
int processString(char* str, char ** parsed);
void parseSpace(char* str, char** parsed);
int commandHandler(char** parsed);
void execArgs(char** parsed);


int main()
{
    char inputString[2049];
    char *parsedArgs[512];
    int execFlag = 0;
    
    //set NULL to every position in parsedArgs array
    for (int c = 0; c <=512; c++)
    {
        parsedArgs[c] = NULL;
    }
    
    printf("$ smallsh\n"); //print name of new shell
    fflush(stdin);
    
    while (1) //start infinate loop to create small shell
    {
        
        printf(": "); //command line prompt
        fflush(stdin);
        fgets(inputString, 2048, stdin); //get user command line

        //exclude comments, anything starting with #
        if (inputString[0] != '#')
        {
            //process the string for spaces and special characters
            //put parsed string into parsedArgs
            processString(inputString, parsedArgs);
            //execute the parsedArgs arguments
            execArgs(parsedArgs);
        }
        
        //break;
    }

    
    
    return 0;
}




//*********
//FUNCTIONS
//*********
int processString(char* str, char ** parsed)
{
    parseSpace(str, parsed); //parse spaces for command words
    
    //if(commandHandler(parsed)); //pass the parsed words to the command handler fuction
    //    return 0;
    //else
        return 1;
}


void parseSpace(char* str, char** parsed)
{

    
    // convert input line to list of arguments
    for (int spaces = 0; spaces < MAX && *str; str++) 
    {
        if (*str == ' ') //if space, continue (more words coming)
            continue;
        if (*str == '\n') //if new line, it's at end of command, break and return
            break;
        //else add the current word to parsed[spaces], increment spaces, check if str is still valid (not new line)
        //set current str word to null
        for (parsed[spaces++] = str; *str && *str != ' ' && *str != '\n'; str++);
            *str = '\0';
    }
    return;
}

int commandHandler(char** parsed)
{
    int numberOfCommands = 1;
    int counter = 0;
    int switchOwnArg = 0;
    char* listOfOwnCommands[numberOfCommands];
    
    switch (switchOwnArg)
    {
        case 1:
        {
            
        }
        default:
            break;
    }
    
    return 0;
}


void execArgs(char** parsed)
{
    //Forking a child
    int wstatus = 0;
    
    pid_t pid = fork();
        // fork child and execute program
        
        signal(SIGINT, SIG_DFL);
        if (pid == -1) //error forking child
        {
            perror("Error forking child");
            fflush(stdin);
            printf("\n");
            fflush(stdin);
            return;
        }
        else if (pid == 0) 
        {
            //run execvp, if error, print error message
            if(execvp(parsed[0], parsed) == -1)
            {
                perror("Error executing command.");
                fflush(stdin);
                printf("\n");
                fflush(stdin);
            }
        }
        else
        {
            waitpid(pid, &wstatus, WUNTRACED); //wait for child to exit
            signal(SIGINT, SIG_IGN);
            return;
        }
    return;
}


    




