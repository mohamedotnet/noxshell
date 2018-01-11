#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>
#include <stdlib.h>

#define MAXLINE 80

/*
 * TODO: - Add history feature for up to 10 commands;
 *       - Implement exit syscall;
 *       - Impelement Tab-Completing;
 *       - Add > < for io redirection;
 *       - Add & feature;
 */
int main(void){
    char command[MAXLINE], *args[3];
    //args[3] = NULL;
    int run = 1;
    char *history[10];
    int i = 0;
    while (run){
        printf("noxshell> ");
        int i = 0;
        /*
         * Splitting string to get: process, params, &
         */
        fgets(command, MAXLINE, stdin);
        char *token = strtok(command, " \n\r");
        while (token != NULL){
            args[i] = token;
            token = strtok(NULL, " \n\r");
            i++;
        }
        args[i] = token;
        /*
         * Execute the command
         */
        if (strcmp(args[0], "exit")==0) run = 0;
        int status;
        int pid = fork();
        if (pid < 0){
            fprintf(stderr, "Error on executing..");
            exit(1);
        }else if(pid == 0){
            execvp(args[0], args);
        }else {
            wait(&status);
        }
    }
    return 0;
}
