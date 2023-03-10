#include "shell.h"

/**
*is_command_executable - checks if a command is executable by verifying if the
*@command: parsed user input as a result of separator operators
*@ptr: pointer to shell
*Return: It returns the index where the file name begins in the command string
*if it is executable, -1 if it is not executable or there was an error.
*/
int is_command_executable(char *command, ShellData *ptr)
{
	struct stat st;
	int i, index = -1;

	for (i = 0; command[i]; i++)
	{
		if (command[i] == '.')
		{
			if (command[i + 1] == '.')
				return (-1);
			if (command[i + 1] == '/')
				continue;
			else
				break;
		}
		else if (command[i] == '/' && i != 0)
		{
			if (command[i + 1] == '.')
				continue;
			i++;
			index = i;
			break;
		}
		else
			break;
	}
	if (index == -1)
		return (0);

	if (stat(command + index, &st) == 0)
	{
		if (S_ISREG(st.st_mode) && (st.st_mode & S_IXUSR))
			return (index);
	}
	handle_error(ptr, 127);
	return (-1);
}

/**
 * is_path_segment - checks if a given path segment ends and starts with ':'
 * @path: path to check
 * @index: pointer to the current index being checked
 *
 * Return: 1 if the path segment ends with ':', 0 otherwise
 */
int is_path_segment(char *path, int *index)
{
	if (path[*index] == ':')
		return (1);

	for (; path[*index]; (*index)++)
	{
		if (path[*index] == ':')
		return (1);
	}

	return (0);
}
/**
*get_path - used to search for the location of a command
*within the directories listed in the PATH environment variable
*@cmd: command
*@envp: pointer to environment variables
*Return: string having the path to the executable command
*/
char *get_path(char *cmd, char **envp)
{
	char *path, *ptr_path, *token, *dir;
	int dir_len, cmd_len, i;
	struct stat st;

	path = _getenv("PATH", envp);
	if (path)
	{
		ptr_path = _strdup(path);
		cmd_len = _strlen(cmd);
		token = my_strtok(ptr_path, ":");
		i = 0;

		do {
			if (is_path_segment(path, &i))
			{
				if (stat(cmd, &st) == 0)
					return (cmd);
			}
			dir_len = _strlen(token);
			dir = malloc(dir_len + cmd_len + 2);
			sprintf(dir, "%s/%s", token, cmd);
			if (stat(dir, &st) == 0)
			{
				free(ptr_path);
				return (dir);
			}
			free(dir);
			token = my_strtok(NULL, ":");
		} while (token != NULL);
		free(ptr_path);
		if (stat(cmd, &st) == 0)
		return (cmd);
		return (NULL);
	}
	if (cmd[0] == '/')
	{
		if (stat(cmd, &st) == 0)
			return (cmd);
	}
	return (NULL);
}

/**
*execute_cmd - to execute a shell command given
*its arguments, wait for the command to complete
*and set the status of the data_shell struct accordingly
*@shell_data: pointer to shell struct
*Return: first checks if the command is executable and returns 1 if not
*then, it checks if the command exists
*in the PATH environment variable and sets its path accordingly
*If there is an error with the command, the function returns 1
*the function forks a child
*process to execute the command using the execve system call
*/
int execute_cmd(ShellData *shell_data)
{
	pid_t pid;
	pid_t wait_pid;
	int status;
	int exec_flag;
	char *directory, *arg_in = shell_data->parsed_input_args[0];
	char **envp = shell_data->environment_vars;

	(void) wait_pid;
	exec_flag = is_command_executable(arg_in, shell_data);
	if (exec_flag == -1)
		return (1);
	if (exec_flag == 0)
	{
		directory = get_path(arg_in, envp);
		if (search_cmd_error(directory, shell_data) == 1)
			return (1);
	}
	pid = fork();

	if (pid == 0)
	{
		if (exec_flag == 0)
			directory = get_path(arg_in, envp);
		else
			directory = arg_in;
		execve(directory + exec_flag, shell_data->parsed_input_args, envp);
	}
	else if (pid < 0)
	{
		perror(shell_data->command_line_args[0]);
		return (1);
	}
	else
	{
		do {
			wait_pid = waitpid(pid, &status, WUNTRACED);
		} while (!WIFEXITED(status) && !WIFSIGNALED(status));
	}
	shell_data->exit_status = (status / 256);
	return (1);
}


/**
*execute - execute built-in commands or
*external programs based on the given command line arguments
*@ptr: pointer to shell struct
*Return: 1
*/
int execute(ShellData *ptr)
{
	int (*builtin)(ShellData *ptr);

	if ((*ptr).parsed_input_args[0] == NULL)
	{
	/*Empty command line*/
		return (1);
	}

	/*Check if command is a builtin*/
	builtin = find_builtin_func((*ptr).parsed_input_args[0]);

	if (builtin != NULL)
		return (builtin(ptr));

	/*Execute external command*/
	return (execute_cmd(ptr));
}
