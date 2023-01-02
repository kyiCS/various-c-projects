#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <time.h>
#include <string.h>
#include <fcntl.h>

void createarray(char *buf, char **array) {
    int i, len, count;

    len = strlen(buf);
    buf[len-1] = '\0'; /* replace last character (\n) with \0 */
    for (i = 0, array[0] = &buf[0], count = 1; i < len; i++) {
        if (buf[i] == ' ') {
            buf[i] = '\0';
            array[count++] = &buf[i+1];
        }
    }
    array[count] = (char *)NULL;
}

void sig_usr(int signo){
    if(signo == SIGINT){
        signal(signo, SIG_IGN);
        printf("\nChild process has been interrupted\n");
    }else if (signo == SIGTSTP){
        signal(signo, SIG_IGN);
        printf("\nChild process has been stopped\n");
    }
    fflush(stdout);
    signal(signo, sig_usr);
}

int main() {
    char line[BUFSIZ], buf[BUFSIZ], *args[BUFSIZ];
    int status;
    char cmd[256];
    char input[1024];
    FILE *fp;

    while(1) {
        printf("Enter command: ");
        fgets(cmd, 256, stdin);

        fp = popen(cmd, "r");
        strcpy(buf, cmd);
        createarray(cmd, args);

        int i;
        for (i = 0; args[i] != NULL; i++)
            printf("[%s] ", args[i]);
        printf("\n");

        if(strcmp(args[0], "cd")==0){            //check if command is cd
            chdir(args[1]);                   //change the directory to the specified path
            continue;
        }

        if (strcmp(args[0],"quit")==0) {
            printf("Quit");
            break;
        }

        if(signal(SIGINT, sig_usr) == SIG_ERR){
            printf("ERROR");
            exit(-1);
        }else if(signal(SIGTSTP, sig_usr) == SIG_ERR){
            printf("ERROR");
            exit(-1);
        }

        while (fgets(input, 1024, fp) != NULL) {
            printf("%s", input);
        }
    }
    pclose(fp);
}

