#include "shell.h"

/**
*_create_env_var - create new environ name
*@name: name
*@value: new value
*Return: a new key value pair
*/
char *_create_env_var(char *name, char *value)
{
	int len = sprintf(NULL, "%s=%s", name, value) + 1;
	char *env_var = malloc(sizeof(char) * len);

	if (env_var == NULL)
		return (NULL);

	sprintf(env_var, "%s=%s", name, value);
	return (env_var);
	}

/**
*_setenv - reset name of environ
*@ptr: shell pointer
*Return: 1 success
*/
int _setenv(ShellData *ptr)
{
	int i;
	char *var_env, *name_env;
	char *name, *value;
	if (ptr->parsed_input_args[1] == NULL || ptr->parsed_input_args[2] == NULL)
	{
		handle_error(datash, -1);
		return (1);
	}

	*name = ptr->parsed_input_args[1];
	*value = ptr->parsed_input_args[2];

	for (i = 0; ptr->environment_vars[i]; i++)
	{
		var_env = _strdup(ptr->environment_vars[i]);
		name_env = _strtok(var_env, "=");
		if (_strcmp(name_env, name) == 0)
		{
			free(ptr->environment_vars[i]);
			ptr->environment_vars[i] = _create_env_var(name_env, value);
			free(var_env);
			return (1);
		}
		free(var_env);
	}

	ptr->environment_vars = _realloc_double_ptr(datash->_environ, i, sizeof(char *) * (i + 2));
	ptr->environment_vars[i] = _create_env_var(name, value);
	ptr->environment_vars[i + 1] = NULL;

	return (1);
}

/**
*_unsetenv - removes an environ variable
*@ptr: pointer
*Return: 1
*/
int _unsetenv(ShellData *ptr)
{
	char **new_environment_vars;
	char *var, *name;
	int i, j, k;

	if (ptr->args[1] == NULL)
	{
		handle_error(ptr, -1);
		return (1);
	}

	k = -1;
	i = 0;
	while (ptr->environment_vars[i])
	{
		var = _strdup(ptr->environment_vars[i]);
		name = _strtok(var, "=");
		if (_strcmp(name, ptr->parsed_input_args[1]) == 0)
			k = i;

		free(var);
		i++;
	}

	if (k == -1)
	{
		handle_error(ptr, -1);
		return (1);
	}

	new_environment_vars = malloc(sizeof(char *) * i);
	i = j = 0;
	while (ptr->environment_vars[i])
	{
		if (i != k)
		{
			new_environment_vars[j] = ptr->environment_vars[i];
			j++;
		}
		i++;
	}
	new_environment_vars[j] = NULL;
	free(ptr->environment_vars[k]);
	free(ptr->environment_vars);
	ptr->environment_vars = new_environment_vars;
	return (1);
}
