#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

#include "dshlib.h"

/*
 *  build_cmd_list
 *    cmd_line:     the command line from the user
 *    clist *:      pointer to clist structure to be populated
 *
 *  This function builds the command_list_t structure passed by the caller
 *  It does this by first splitting the cmd_line into commands by spltting
 *  the string based on any pipe characters '|'.  It then traverses each
 *  command.  For each command (a substring of cmd_line), it then parses
 *  that command by taking the first token as the executable name, and
 *  then the remaining tokens as the arguments.
 *
 *  NOTE your implementation should be able to handle properly removing
 *  leading and trailing spaces!
 *
 *  errors returned:
 *
 *    OK:                      No Error
 *    ERR_TOO_MANY_COMMANDS:   There is a limit of CMD_MAX (see dshlib.h)
 *                             commands.
 *    ERR_CMD_OR_ARGS_TOO_BIG: One of the commands provided by the user
 *                             was larger than allowed, either the
 *                             executable name, or the arg string.
 *
 *  Standard Library Functions You Might Want To Consider Using
 *      memset(), strcmp(), strcpy(), strtok(), strlen(), strchr()
 */
int build_cmd_list(char *cmd_line, command_list_t *clist)
{
	memset(clist, 0, sizeof(command_list_t));
	char *savept, *saveptr;
	char *cmd;
	cmd = strtok_r(cmd_line, PIPE_STRING, &savept);
	int count = 0;

	while (cmd != NULL){
		//goes through leading sapces
		while(*cmd == SPACE_CHAR){
			cmd++;
		}
		//removes trailing spaces
		char *end = cmd + strlen(cmd) - 1;
		while(end > cmd && *end == SPACE_CHAR){
			*end = '\0';
			end--;
		}
		if(count >= CMD_MAX){
			return ERR_TOO_MANY_COMMANDS;
		}
		//saves the first token in the string
		char *exec = strtok_r(cmd, " ", &saveptr);
		if (strlen(exec) >= EXE_MAX){
			return ERR_CMD_OR_ARGS_TOO_BIG;
		}
		//stores into clist
		strcpy(clist->commands[count].exe, exec);
		//saves the rest of the string as arguments
		char *arg = strtok_r(NULL, "", &saveptr);
		if(arg != NULL){
			if(strlen(arg) >= ARG_MAX){
				return ERR_CMD_OR_ARGS_TOO_BIG;
			}
			//stores into clist
			strcpy(clist->commands[count].args, arg);
		} else {
			//if no arguments store a null terminator
			clist->commands[count].args[0] = '\0';
		}
		count++;
		// next command
		cmd = strtok_r(NULL, PIPE_STRING, &savept);
	}
	clist->num = count;
	return OK;
}
