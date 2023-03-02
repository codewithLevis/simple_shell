#include "shell.h"

/**
*_create_env_var - create new environ name
*@name: name
*@value: new value
*Return: a new key value pair
*/
char *_create_env_var(char *name, char *value)
{
	int len = _strlen(name) + _strlen(value) + 2;
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
		handle_error(ptr, -1);
		return (1);
	}

	*name = ptr->parsed_input_args[1];
	*value = ptr->parsed_input_args[2];

	for (i = 0; ptr->environment_vars[i]; i++)
	{
		var_env = _strdup(ptr->environment_vars[i]);
		name_env = my_strtok(var_env, "=");
		if (_strcmp(name_env, name) == 0)
		{
			free(ptr->environment_vars[i]);
			ptr->environment_vars[i] = _create_env_var(name_env, value);
			free(var_env);
			return (1);
		}
		free(var_env);
	}

	ptr->environment_vars = _realloc_double_ptr(ptr->environment_vars, i, sizeof(char *) * (i + 2));
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

	if ptr->parsed_input_args[1] == NULL)
	{
		handle_error(ptr, -1);
		return (1);
	}

	k = -1;
	i = 0;
	while (ptr->environment_vars[i])
	{
		var = _strdup(ptr->environment_vars[i]);
		name = my_strtok(var, "=");
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

/**
*_getenv - gets the value of the requested environment variable
*@value: name of the environment variable
*@env: pointer to the environment variables array
*Return: pointer to the value of the environment variable, NULL if not found
*/
char *_getenv(const char *value, char **env)
{
	char *ptr_env;
	int i, j;

	ptr_env = NULL;
	j = 0;

	for (i = 0; env[i]; i++)
	{

		j = 0;
		while (env[i][j] == value[j] && value[j] != '\0')
			j++;
		if (env[i][j] == '=' && value[j] == '\0')
		{
			ptr_env = &env[i][j + 1];
			break;
		}
	}

	return (ptr_env);
}


/**
 * set_environment_variable - sets an environment variable
 *
 * @key: name of the variable to be set
 * @value: value to be set for the variable
 * @datash: data relevant (environ)
 * Return: no return
 */
void _set2env(char *key, char *value, ShellData *ptr)
{
	int index, len_env;
	char *curr_value, *curr_key;

	len_env = 0;
	while ((*ptr).environment_vars[len_env] != NULL)
	{
		len_env++;
	}

	for (index = 0; index < len_env; index++)
	{
		curr_value = _strdup((*ptr).environment_vars[index]);
		curr_key = my_strtok(curr_value, "=");

		if (_strcmp(curr_key, key) == 0)
		{
			free((*ptr).environment_vars[index]);
			(*ptr).environment_vars[index] = _create_env_var(curr_key, value);
			free(curr_value);
			return;
		}

		free(curr_value);
	}

	(*ptr).environment_vars = my_reallocate((*ptr).environment_vars, len_env, sizeof(char *) * (len_env + 2));
	(*ptr).environment_vars[len_env] = _create_env_var(key, value);
	(*ptr).environment_vars[len_env + 1] = NULL;
}
