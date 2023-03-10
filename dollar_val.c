#include "shell.h"

/**
*search_env_var - function to check whether
*the name of the substring following the $ character
*corresponds to an environment variable name.
*@start: a double pointer to the start of the linked list
*@in: a pointer to the input string
*it is substrings of user input
*starting with $ followed by the name of an environment variable
*@ptr: a pointer to a ShellData struct that
*contains information about the shell
*/

void search_env_var(VarNode_t **start, char *in, ShellData *ptr)
{
	char **env_vars = (*ptr).environment_vars;
	int i, j, len_val;

	for (i = 0; env_vars[i]; i++)
	{
		j = 0;
		while (env_vars[i][j] && in[j] && env_vars[i][j] == in[j])
			j++;

		if (env_vars[i][j] == '=')
		{
			len_val = _strlen(env_vars[i] + j + 1);
			add_node(start, j, env_vars[i] + j + 1, len_val);
			return;
		}
	}

	j = 0;
	while (in[j] != '\0')
	{
		if (in[j] != ' ' || in[j] != '\t' || in[j] != ';' || in[j] != '\n')
			break;
		j++;
	}
	add_node(start, j, NULL, 0);
}

/**
*parse_vars -  checks for the presence of
*these special variables in a given input
*string, and creates a new node in a linked list data structure
*to store their values for later use in the shell program
*@head: pointer to a to linked list of VarNode_t
*@input: user input
*@status: current state of the Shell
*@ptr: pointer to struct ShellData
*Return: index (keep track of the current position in the input string)
*The purpose of this function is to expand
*variables ($$, $?) in a command string before executing it
*/
int parse_vars(VarNode_t **head, char *input, char *status, ShellData *ptr)
{
	int i, status_len = 0, pid_len = 0;

	status_len = _strlen(status);
	pid_len = _strlen(ptr->process_id);

	for (i = 0; input[i]; i++)
	{
		if (input[i] == '$')
		{
			if (input[i + 1] == '?')
				add_node(head, 2, status, status_len);

			else if (input[i + 1] == '$')
				add_node(head, 2, ptr->process_id, pid_len);

			else if (input[i + 1] == '\n' || input[i + 1] == '\0')
				add_node(head, 0, NULL, 0);

			else if (input[i + 1] == ' ' || input[i + 1] == '\t' || input[i + 1] == ';')
				add_node(head, 0, NULL, 0);
			else
				search_env_var(head, input + i, ptr);
		}
	}
	return (i);
}

/**
*expansion - function expands environment variables in the input string
*@start: pointer to head of a linked list
*@in: pointer user input
*@new: pointer to location to hold new string generated after the expansion
*@new_len: length of new
*Return: new string
*/

char *expansion(VarNode_t **start, const char *in, char *new, int new_len)
{
	VarNode_t *indx = *start;
	int i = 0, j = 0, k;

	while (in[i] != '\0' && j < new_len - 1)
	{
		if (in[i] == '$')
		{
			if (!(indx->len_var) && !(indx->len_val))
			{
				new[j] = in[i];
				i++;
				j++;
			}
			else if (indx->len_var && !(indx->len_val))
			{
				for (k = 0; k < indx->len_var && j < new_len - 1; k++, j++)
					new[j] = in[i + k];
				i += indx->len_var;
			}
			else
			{
				for (k = 0; k < indx->len_val && j < new_len - 1; k++, j++)
					new[j] = indx->val[k];
				i += indx->len_var;
			}
			indx = indx->next;
		}
		else
		{
			new[j] = in[i];
			i++;
			j++;
		}
	}

	new[j] = '\0';
	return (new);
}

/**
*expand_variables - replaces all occurrences
*of shell variables in the input string with
*their corresponding values, if they exist in the environment
*@input: pointer to a string representing the user input
*@ptr: struct that holds data related to the current shell session
*Return: a new string with the variable substitutions made
*expansion: helper function that actually replaces
*the variable occurrences with their values in the input string
*/

char *expand_variables(char *input, ShellData *ptr)
{
	VarNode_t *start, *temp;
	char *status, *new;
	int pos1, pos2;

	status = _itoa((*ptr).exit_status);
	start = NULL;
	pos1 = parse_vars(&start, input, status, ptr);

	if (start == NULL)
	{
		free(status);
		return (input);
	}
	temp = start;
	pos2 = 0;

	while (temp != NULL)
	{
		pos2 += (temp->len_val - temp->len_var);
		temp = temp->next;
	}
	pos2 += pos1;
	new = malloc(sizeof(char) * (pos2 + 1));

	new = expansion(&start, input, new, pos2);

	free(input);
	free(status);
	free_VarNode_t(&start);
	return (new);
}
