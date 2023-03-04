#include "shell.h"

/**
*encoder - encodes '|' and '&' characters
*@input: input string
*@encode: boolean indicating whether to encode or decode
*Return: encoded or decoded string
*The purpose of encoding the characters '|' and '&' as 0x10 and 0x0C respectively
*is likely to avoid any confusion between them and the actual '|' and '&'
*characters used in the shell for logical OR and AND operations
*By encoding them as different characters, the shell can still interpret
*them correctly without confusing them with the logical operators
*/
char *encoder(char *input, int encode)
{
	int i;

	if (encode == 1)
	{
		for (i = 0; input[i] != '\0'; i++)
		{
			if (input[i] == 16)
				input[i] = '|';
			if (input[i] == 12)
				input[i] = '&';
		}
	}
	else
	{
		while (*input != '\0')
		{
			if (*input == '|')
			{
				if (*(input + 1) != '|')
					*input = 16;
				else
					input++;
			}
			if (*input == '&')
			{
				if (*(input + 1) != '&')
					*input = 12;
				else
					input++;
			}
			input++;
		}
	}
	return (input);
}

/**
*parse_input - function for parsing input by use of separators
*Calls function to create node of the resulting tokens
*@head: head of SeparatorNode list
*@start: start of CommandLineNode list
*@input: user modified input
*Return: void
*/
void parse_input(SeparatorNode **head, CommandLineNode **start, char *input)
{
	int i = 0;
	char delim[4] = ";|&";
	char *sep_token; /*token based on separators*/
	input = encoder(input, 0);

	while (input[i])
	{
		if (input[i] == ';')
			add_SeparatorNode(head, input[i]);

		if (input[i] == '|' || input[i] == '&')
		{
			add_SeparatorNode(head, input[i]);
			i++;
		}
		i++;
	}
    
    /*tokenize the input by separators and add to the command list*/
	sep_token = my_strtok(input, delim);

	while (sep_token != NULL)
	{
		sep_token = encoder(sep_token, 1);
		printf("sep_token\n");
		add_CommandLineNode(start, sep_token);
		sep_token = my_strtok(NULL, delim);
	}
}

/**
 * get_next - Traverses the command linked list and returns
 *                     the next node to be executed
 * @head: The start of the command linked list
 * @start: The start of the separator linked list
 * @ptr: The shell data struct
 *
 * Return: void
 */
void get_next(CommandLineNode **head, SeparatorNode **start, ShellData *ptr)
{
        int separator_loop;
        SeparatorNode *temp = *start;
        CommandLineNode *curr = *head;

        separator_loop = 1;
        while (temp != NULL && separator_loop)
        {
                if ((*ptr).exit_status == 0)
                {
                        if (temp->symbol == '&' || temp->symbol == ';')
                                separator_loop = 0;
                        if (temp->symbol == '|')
                                curr = curr->next, temp = temp->next;
                }
                else
                {
                        if (temp->symbol == '|' || temp->symbol == ';')
                                separator_loop = 0;
                        if (temp->symbol == '&')
                                curr = curr->next, temp = temp->next;
                }
                if (temp != NULL && !separator_loop)
                        temp = temp->next;
        }

	*start = temp;
	*head = curr;
        
}


/**
*execute_commands - split a command line input into separate
*commands separated by specific separator characters (;, |, or &)
*@ptr: pointer to struct shell
*@input: user input
*Return: If the function encounters an error while executing a command or
*if the user enters an exit command, the function returns 0 and terminates
*/

int execute_commands(ShellData *ptr, char *input)
{
	SeparatorNode *head = NULL, *curr;
	CommandLineNode *start = NULL, *temp;
	int flag;
	
	parse_input(&head, &start, input);
	curr = head;
	temp = start;
	printf("Outside is cool\n");
	
	if (temp == NULL)
		printf("I am null\n");
	while (temp != NULL)
	{
		printf("I was not a joke to reach here");
		(*ptr).user_input = temp->command;
		(*ptr).parsed_input_args = tokenize((*ptr).user_input, TOK_DELIM);

		flag = execute(ptr);
		free((*ptr).parsed_input_args);

		if (flag == 0)
			break;
		get_next(&temp, &curr, ptr);
		if (temp != NULL)
			temp = temp->next;
	}

	free_SeparatorNode_list(&head);
	free_CommandLineNode_list(&start);
	if (flag == 0)
		return (0);
	return (1);
}
