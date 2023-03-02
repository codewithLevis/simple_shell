#include "shell.h"

/**
*free_SeparatorNode_list - Frees the memory allocated for the separator node list
*@head: Pointer to the head of the separator node list
*Return: void
*/

void free_SeparatorNode_list(SeparatorNode **head)
{
	SeparatorNode *temp;
	SeparatorNode *curr;
	if (head != NULL)
	{
		curr = *head;
		for (; curr != NULL; curr = temp)
		{
			temp = curr->next;
			free(curr);
		}
		*head = NULL;
	}
}

/**
*free_CommandLineNode_list - Frees the memory allocated for the command node list
*@head: Pointer to the head of the command node list
*Return: void
*/
void free_CommandLineNode_list(CommandLineNode **start)
{
	CommandLineNode *temp;
	CommandLineNode *curr;

	if (start != NULL)
	{
		curr = *start;
		for (; curr != NULL; curr = temp)
		{
			temp = curr->next;
			free(curr);
		}
		*start = NULL;
	}
}

/**
* free_shell_data - Frees the memory allocated for the shell data struct
* @ptr: A pointer to the shell data struct
* Return: void
*/
void free_shell_data(ShellData *ptr)
{
	unsigned int i = 0;

	while (ptr->environment_vars[i] != NULL)
	{
		free(ptr->environment_vars[i]);
		i++;
	}

	free(ptr->environment_vars);
	free(ptr->process_id);
}
