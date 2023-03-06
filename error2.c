#include "shell.h"

/**
 * handle_error - handles shell error messages
 * @ptr: pointer to data structure
 * @error_no: integer value of the error
 * Return: the integer value of the error
 */
int handle_error(ShellData *ptr, int error_no)
{
	char *error;

	if (error_no == -1)
		error = env_err(ptr);
	else if (error_no == 126)
		error = path_126_err(ptr);
	else if (error_no == 127)
		error = not_found_err(ptr);
	else if (error_no == 2)
	{
		if (_strcmp("exit", ptr->parsed_input_args[0]) == 0)
			error = exit_shell_err(ptr);
		else if (_strcmp("cd", ptr->parsed_input_args[0]) == 0)
			error = generate_cd_err(ptr);
	}
	if (error)
	{
		dprintf(STDERR_FILENO, "%s", error);
		free(error);
	}
	ptr->exit_status = error_no;
	return (error_no);
}

/**
*env_err - generates environ error
*@ptr: pointer to shell struct
*Return: err info
*/
char *env_err(ShellData *ptr)
{
	int len;
	char *err;
	char *str, *msg, *args, *arg_in;

	str = _itoa(ptr->command_counter);
	msg = ": Unable to add/remove from environment\n";
	len = _strlen(ptr->command_line_args[0]) + _strlen(str);
	len += _strlen(ptr->parsed_input_args[0]) + _strlen(msg) + 2;
	err = malloc(sizeof(char) * (len + 1));

	if (err == NULL)
	{
		free(err);
		free(str);
		return (NULL);
	}
	args = ptr->command_line_args[0];
	arg_in = ptr->parsed_input_args[0];
	sprintf(err, "%s: %s: %s%s", args, str, arg_in, msg);
	free(str);
	return (err);
}

/**
*path_126_err - to generate an error message string when a command
*is found but cannot be executed due to permission denied
*@ptr: pointer to struct shell
*Return: dynamically allocated string containing the error message
*or NULL if memory allocation fails
*/
char *path_126_err(ShellData *ptr)
{
	int length;
	char *counter_str;
	char *err;

	counter_str = _itoa(ptr->command_counter);
	length = _strlen(ptr->command_line_args[0]) + _strlen(counter_str) + 27;
	err = malloc(sizeof(char) * (length + 1));
	if (err == NULL)
	{
		free(err);
		free(counter_str);
		return (NULL);
	}
	sprintf(err, "%s: %s: %s: Permission denied\n",
	    ptr->command_line_args[0], counter_str, ptr->command_line_args[0]);
	free(counter_str);
	return (err);
}
/**
*not_found_err - if command not found
*@ptr: pointer
*Return: dynamically allocated string containing the error message
*or NULL if memory allocation fails
*/
char *not_found_err(ShellData *ptr)
{
	int len;
	char *err;
	char *str;
	char *args = ptr->command_line_args[0];
	char *arg_in = ptr->parsed_input_args[0];

	str = _itoa(ptr->command_counter);
	len =  _strlen(args) + _strlen(str) + _strlen(arg_in) + 1;
	err = malloc(sizeof(char) * (len + 14));
	if (err == NULL)
	{
		free(str);
		return (NULL);
	}
	sprintf(err, "%s: %s: %s: not found\n", args, str, arg_in);
	free(str);
	return (err);
}

/**
*exit_shell_err - error on exiting shell
*@ptr: pointer
*Return: dynamically allocated string containing the error message
*or NULL if memory allocation fails
*/

char *exit_shell_err(ShellData *ptr)
{
	int len, i;
	char *err;
	char *str;
	char *args = ptr->command_line_args[0];
	char *arg_in = ptr->parsed_input_args[0];
	char *arg_in1 = ptr->parsed_input_args[1];

	str = _itoa(ptr->command_counter);
	len = _strlen(args) + _strlen(str) + _strlen(arg_in);
	len += _strlen(arg_in1) + 1;
	err = malloc(sizeof(char) * (len + 23));
	if (err == NULL)
	{
		free(str);
		return (NULL);
	}
	snprintf(err, len + 23, "%s: %s: %s: Illegal number: %s\n",
		 args, str, arg_in, arg_in1);

	free(str);
	return (err);
}
