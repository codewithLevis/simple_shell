#include "shell.h"

/**
*generate_cd_err - related to cd execution
*@ptr: pointer
*Return: err message
*/

char *generate_cd_err(ShellData *ptr)
{
    int len, len_id;
    char *err, *str, *msg;

    str = _itoa(ptr->command_counter);
    if ( ptr->parsed_input_args[1][0] == '-')
    {
        msg = ": Illegal option ";
        len_id = 2;
    }
    else
    {
        msg = ": can't cd to ";
        len_id = _strlen( ptr->parsed_input_args[1]);
    }
    len = _strlen( ptr->command_line_args[0]) + _strlen(ptr->parsed_input_args[0][0]);
    len += _strlen(str) + _strlen(msg) + len_id + 5;
    error = malloc(sizeof(char) * (length + 1));
    if (err == NULL)
    {
        free(_str);
        return (NULL);
    }

    sprintf(err, "%s: %s: %s%s%s", ptr->command_line_args[0], str, msg, ptr->parsed_input_args[1], "\n");

    free(str);
    return (err);
}

/**
 * search_cmd_error - Check if the command is valid
 * @dir: directory of the command
 * @ptr: the shell data
 * Return: 1 if there is an error, otherwise 0
 */
int search_cmd_error(char *dir, ShellData *ptr)
{
        if (dir == NULL)
        {
        handle_error(datash, 127);
        return (1);
        }

        if (_strcmp((*ptr).parsed_input_args[0], dir) != 0)
        {
                if (access(dir, X_OK) == -1)
                {
                        handle_error(ptr, 126);
                        free(dir);
                        return (1);
                }
                free(dir);
        }
        
        else
        {
                if (access((*ptr).parsed_input_args[0], X_OK) == -1)
                {
                        handle_error(datash, 126);
                        return (1);
                }
        }

        return (0);
}
