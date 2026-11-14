#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main() {
    while(1) {
        printf("shell> ");
        fflush(stdout);

        char cmd[100];

        if(fgets(cmd, sizeof(cmd), stdin) == NULL) {
            printf("\n");
            break;
        }

        if(cmd[0] == '\n') continue;

        if(strcmp(cmd, "exit\n") == 0) break;

        // split command into arguments
        char *args[10];

        char *token = strtok(cmd, " \n");

        int i;
        for(i = 0; token != NULL && i < 9; i++) {
            args[i] = token;
            token = strtok(NULL, " \n");
        }

        args[i] = NULL;

        pid_t pid = fork();

        if(pid == 0) {
            execvp(args[0], args);

            perror("execvp failed");
            _exit(1);
        }
        else if(pid > 0) {
            waitpid(pid, NULL, 0);
        }
        else {
            perror("fork failed");
        }
    }
    
    return 0;
}