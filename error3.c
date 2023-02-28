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
