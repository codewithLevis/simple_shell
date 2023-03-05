#include "shell.h"

/**
 * cd_parent_dir - Change to the parent directory.
 * @ptr: Pointer to data relevant to the shell (environment variables).
 * Return: void
 */
void cd_parent_dir(ShellData *ptr)
{
	char current_dir[PATH_MAX], *directory, *cwd_copy, *pwd_copy;

	getcwd(current_dir, sizeof(current_dir));
	cwd_copy = _strdup(current_dir);
	_set2env("OLDPWD", cwd_copy, ptr);
	directory = ptr->parsed_input_args[1];
	/* If the directory is "." do nothing. */
	if (_strcmp(".", directory) == 0)
	{
		_set2env("PWD", cwd_copy, ptr);
		free(cwd_copy);
		return;
	}
	/* If the directory is "/" and the current directory is also "/", do nothing. */
	if (_strcmp("/", cwd_copy) == 0)
	{
		free(cwd_copy);
		return;
	}
	/* Reverse the current working directory string. */
	pwd_copy = cwd_copy;
	_strrev(pwd_copy);
	/* Get the parent directory. */
	pwd_copy = my_strtok(pwd_copy, "/");
	if (pwd_copy != NULL)
	{
		pwd_copy = my_strtok(NULL, "\0");

		if (pwd_copy != NULL)
			_strrev(pwd_copy);
	}
	/* Change to the parent directory and update the PWD environment variable. */
	if (pwd_copy != NULL)
		chdir(pwd_copy), _set2env("PWD", pwd_copy, ptr);

	else
		chdir("/"), _set2env("PWD", "/", ptr);

	(*ptr).exit_status = 0;
	free(cwd_copy);
}

/**
 * cd_change_dir - Change to the directory specified by the user.
 * @ptr: Pointer to data relevant to the shell (directories).
 * Return: void
 */
void cd_change_dir(ShellData *ptr)
{
	char current_dir[PATH_MAX];
	char *specified_dir, *cp_current_dir, *cp_specified_dir;

	/* Get the current working directory.*/
	getcwd(current_dir, sizeof(current_dir));

	/* Get the specified directory from the argument list.*/
	specified_dir = (*ptr).parsed_input_args[1];

	/*changing the current working dir to the specified dir.*/
	if (chdir(specified_dir) == -1)
	{
		handle_error(ptr, 2);
		return;
	}

	/* Update the OLDPWD environment variable.*/
	cp_current_dir = _strdup(current_dir);
	_set2env("OLDPWD", cp_current_dir, ptr);
	free(cp_current_dir);

	/* Update the PWD environment variable.*/
	cp_specified_dir = _strdup(specified_dir);
	_set2env("PWD", cp_specified_dir, ptr);
	free(cp_specified_dir);

	(*ptr).exit_status= 0;
	chdir(specified_dir);
}

/**
 * cd_prev_dir - moves to the earlier directory
 * @ptr: Pointer to data relevant to the shell
 * Return: void
 */
void cd_prev_dir(ShellData *ptr)
{
	char cwd[PATH_MAX];
	char *oldpwd_value, *new_pwd, *old_pwd;

	if (getcwd(cwd, sizeof(cwd)) == NULL)
	{
		perror("getcwd() error");
		return;
	}

	oldpwd_value = _getenv("OLDPWD", (*ptr).environment_vars);

	if (oldpwd_value == NULL)
	{
		dprintf(STDERR_FILENO, "OLDPWD not set\n");
		return;
	}

	old_pwd = _strdup(cwd);

	if (chdir(oldpwd_value) == -1)
	{
		perror("chdir() error");
		free(old_pwd);
		return;
	}

	new_pwd = _strdup(oldpwd_value);
	_set2env("PWD", new_pwd, ptr);
	_set2env("OLDPWD", old_pwd, ptr);

	printf("%s\n", new_pwd);

	free(old_pwd);
	free(new_pwd);

	ptr->exit_status = 0;
}

/**
* cd_home_dir - changes to home directory
* @ptr: pointer to struct shell
* Return: void
*/
void cd_home_dir(ShellData *ptr)
{
	char *previous_pwd, *home_dir;
	char pwd[PATH_MAX];

	getcwd(pwd, sizeof(pwd));
	previous_pwd = _strdup(pwd);

	home_dir = _getenv("HOME", (*ptr).environment_vars);

	if (home_dir == NULL)
	{
		_set2env("OLDPWD", previous_pwd, ptr);
		free(previous_pwd);
		return;
	}

	if (chdir(home_dir) == -1)
	{
		handle_error(ptr, 2);
		free(previous_pwd);
		return;
	}

	_set2env("OLDPWD", previous_pwd, ptr);
	_set2env("PWD", home_dir, ptr);
	free(previous_pwd);
	(*ptr).exit_status  = 0;
}

/**
 * change_directory - changes current directory based on given arguments
 * @ptr: pointer to shell struct
 * Return: 1
 */
int change_directory(ShellData *ptr)
{
	char *argument;
	int i;

	if ((*ptr).parsed_input_args[1] == NULL)
	{
		cd_home_dir(ptr);
		return (1);
	}

	for (i = 1; (*ptr).parsed_input_args[i] != NULL; i++)
	{
		argument = (*ptr).parsed_input_args[i];

		if (_strcmp("$HOME", argument) == 0 || _strcmp("~", argument) == 0 || _strcmp("--", argument) == 0)
		{
			cd_home_dir(ptr);
			continue;
		}

		if (_strcmp("-", argument) == 0)
		{
			cd_prev_dir(ptr);
			continue;
		}

		if (_strcmp(".", argument) == 0 || _strcmp("..", argument) == 0)
		{
			cd_parent_dir(ptr);
			continue;
		}

		cd_change_dir(ptr);
	}

	return (1);
}
