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
   int rc = 0;
   cmd_buff_t cmd;
	while(1){
		printf("%s", SH_PROMPT);
		if (fgets(cmd_buff,ARG_MAX, stdin) == NULL){
			printf("\n");
			break;
		}

		cmd_buff[strcspn(cmd_buff, "\n")] = '\0';

		if(*cmd_buff == '\0'){ // if no input
			printf("%s\n", CMD_WARN_NO_CMD);
			continue;
		}
		cmd.argc = 0;
		memset(cmd.argv, 0, sizeof(cmd.argv));

		char *arg = cmd_buff;
		bool quotes = false;
		while(arg != NULL){ // parsing and handling of quotes
			while(*arg == ' '){
				arg++;
			}
			if(*arg == '\0'){
				break;
			}
			if(*arg == '"'){
				quotes = true;
				arg++;
			}
			cmd.argv[cmd.argc] = arg;
			cmd.argc++;

			while(quotes || *arg != ' '){
				if(*arg == '"'){
					quotes = false;
					*arg = '\0';
				}
				arg++;
			}
			*arg = '\0'; // null terminate
			arg++;
		}

		if(strcmp(cmd.argv[0], "cd") == 0){
			if(cmd.argv[1] != NULL){
				if(chdir(cmd.argv[1]) != 0){
					perror("cd failed");
				}
			}
			continue;
		}
		if(strcmp(cmd.argv[0], EXIT_CMD) == 0){
			free(cmd_buff);
			exit(0);
		}
		int f_result = fork();
		if(f_result < 0){
			perror("fork failed");
			exit(1);
		}
		else if(f_result == 0){
			execvp(cmd.argv[0], cmd.argv);
			perror("fork failed");
			exit(1);
		} 
		else {
			wait(NULL);
		}
	}
	free(cmd_buff);
	return OK;
}
