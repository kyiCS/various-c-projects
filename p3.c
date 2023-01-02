#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BUFFER_LEN 1024

int main(){
    char line[BUFFER_LEN];
    char* argv[100];
    char* path= "/bin/";
    char progpath[20];
    int argc;

    while(1){

        printf("blazersh> ");

        if(!fgets(line, BUFFER_LEN, stdin))  //checking user input
            break;
        size_t length = strlen(line);
        if (line[length - 1] == '\n')  //removing new line from the input
            line[length - 1] = '\0';


        if(strcmp(line, "exit")==0){            //check if command is exit
            printf("\nGoodbye\n");
            break;                    //exit the shell
        }

        if(strcmp(line, "help")==0){                //check if the command is help
            puts("\n***WELCOME TO MY SHELL HELP***"
                 "\nList of Commands supported:"
                 "\n>ls"
                 "\n>cd"
                 "\n>exit"
                 "\n>etc... (all other general commands available in UNIX shell)\n"
                 );
            continue;
        }

        char *token;                  //split command into separate strings
        token = strtok(line," ");     //at each space, split
        int i=0;
        while(token!=NULL){
            argv[i]=token;           //store in argv array
            token = strtok(NULL," ");
            i++;
        }
        argv[i]=NULL;                     //set last value to NULL for execvp


        if(strcmp(line, "cd")==0){            //check if command is cd
            chdir(argv[1]);                   //change the directory to the specified path
            continue;
        }

        strcpy(progpath, path);           //copy /bin/ to file path to execute general UNIX commands
        strcat(progpath, argv[0]);

        for(i=0; i<strlen(progpath); i++){    //removing new lines
            if(progpath[i]=='\n'){
                progpath[i]='\0';
            }
        }
        int pid= fork();              //fork child

        if(pid==0){               //Child
            execvp(progpath,argv);
            fprintf(stderr, "ERROR: Child process could not do execvp.\n");
            break;
        }else{                    //Parent
            wait(NULL);
        }

    }
}

