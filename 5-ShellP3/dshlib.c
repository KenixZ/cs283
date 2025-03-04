#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/wait.h>

#include "dshlib.h"

/*
 * Implement your exec_local_cmd_loop function by building a loop that prompts the 
 * user for input.  Use the SH_PROMPT constant from dshlib.h and then
 * use fgets to accept user input.
 * 
 *      while(1){
 *        printf("%s", SH_PROMPT);
 *        if (fgets(cmd_buff, ARG_MAX, stdin) == NULL){
 *           printf("\n");
 *           break;
 *        }
 *        //remove the trailing \n from cmd_buff
 *        cmd_buff[strcspn(cmd_buff,"\n")] = '\0';
 * 
 *        //IMPLEMENT THE REST OF THE REQUIREMENTS
 *      }
 * 
 *   Also, use the constants in the dshlib.h in this code.  
 *      SH_CMD_MAX              maximum buffer size for user input
 *      EXIT_CMD                constant that terminates the dsh program
 *      SH_PROMPT               the shell prompt
 *      OK                      the command was parsed properly
 *      WARN_NO_CMDS            the user command was empty
 *      ERR_TOO_MANY_COMMANDS   too many pipes used
 *      ERR_MEMORY              dynamic memory management failure
 * 
 *   errors returned
 *      OK                     No error
 *      ERR_MEMORY             Dynamic memory management failure
 *      WARN_NO_CMDS           No commands parsed
 *      ERR_TOO_MANY_COMMANDS  too many pipes used
 *   
 *   console messages
 *      CMD_WARN_NO_CMD        print on WARN_NO_CMDS
 *      CMD_ERR_PIPE_LIMIT     print on ERR_TOO_MANY_COMMANDS
 *      CMD_ERR_EXECUTE        print on execution failure of external command
 * 
 *  Standard Library Functions You Might Want To Consider Using (assignment 1+)
 *      malloc(), free(), strlen(), fgets(), strcspn(), printf()
 * 
 *  Standard Library Functions You Might Want To Consider Using (assignment 2+)
 *      fork(), execvp(), exit(), chdir()
 */
int exec_local_cmd_loop()
{
	char *cmd_buff = (char *)malloc(SH_CMD_MAX*sizeof(char));
	while(1){
		printf("%s", SH_PROMPT);
		if (fgets(cmd_buff, ARG_MAX, stdin) == NULL){
			printf("\n");
			break;
		}

		cmd_buff[strcspn(cmd_buff,"\n")] = '\0';

		// if no input or input is a space
		if(*cmd_buff == '\0' || strspn(cmd_buff, " ")){
			printf("%s\n", CMD_WARN_NO_CMD);
			continue;
		}

		char *commands[ARG_MAX];
		int count = 0;
		char *saveptr;
		char *cmd = strtok_r(cmd_buff, "|", &saveptr);
		while(cmd != NULL){
			// storing each command
			commands[count] = cmd;
			count++;
			cmd = strtok_r(NULL, "|", &saveptr); 
		}

		if(count == 0){
			continue;
		}

		int pipes[count - 1][2];
		pid_t pids[count];
		for(int i = 0; i < count - 1; i++){
			if(pipe(pipes[i]) == -1){
				perror("pipe");
				exit(0);
			}
		}
		for(int i = 0; i < count; i++){
			// separating each command into separate arguments
			char *args[ARG_MAX];
         int argCount = 0;
         char *arg = strtok(commands[i], " ");
         while(arg != NULL){
				args[argCount] = arg;
            argCount++;
            arg = strtok(NULL, " ");
         }
         args[argCount] = NULL;

         if(strcmp(args[0], "cd") == 0){
         	if(args[1] != NULL){
            	if(chdir(args[1]) != 0){
               	perror("cd failed");
               }
            }
            continue;
         }

			if(strcmp(args[0], EXIT_CMD) == 0){
				free(cmd_buff);
				exit(0);
			}

			pids[i] = fork();
			if(pids[i] == -1){
				perror("fork");
				exit(1);
			}

			if(pids[i] == 0){
				if(i > 0){
					dup2(pipes[i - 1][0], STDIN_FILENO);
				}

				if(i < count - 1){
					dup2(pipes[i][1], STDOUT_FILENO);
				}
				for(int j = 0; j < count - 1; j++){
					close(pipes[j][0]);
					close(pipes[j][1]);
				}
				execvp(args[0], args);
				perror("execvp");
				exit(1);
				}
			}
		for(int i = 0; i < count - 1; i++){
			close(pipes[i][0]);
			close(pipes[i][1]);
		}
		for(int i = 0; i < count; i++){
			wait(NULL);
		}
	}
	free(cmd_buff);
	return OK;
}
