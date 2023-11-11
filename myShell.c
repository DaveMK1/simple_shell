#include "shell.h"
#include <ctype.h>

/**
 * displayPrompt - Displays the shell prompt ('$').
 *
 * This function displays the shell prompt ('$') to indicate that the shell
 * is ready for user input.
 *
 */

void displayPrompt(void)
{
	write(STDOUT_FILENO, PROMPT, strlen(PROMPT));
}

/**
 * builtin_env - Display environment variables
 *
 * Description: This function displays the current environment variables.
 */

void builtin_env(void)
{
	char **env = __environ;

	while (*env)
	{
		write(STDOUT_FILENO, *env, strlen(*env));
		write(STDOUT_FILENO, "\n", 1);
		env++;
	}
}

/**
 * processUserInput - Processes user input and executes commands.
 *
 * @buffer: The input buffer.
 *
 * @n: The number of bytes read.
 */

void processUserInput(char *buffer, ssize_t n)
{
	if (n > 0)
	{
		buffer[n - 1] = '\0';

		if (strcmp(buffer, "exit") == 0)
		{
			write(STDOUT_FILENO, "Exiting the shell\n", 19);
			exit(EXIT_SUCCESS);
		}

		for (ssize_t i = 0; i < n - 1; i++)
		{
			if (isspace(buffer[i]))
			{
				write(STDOUT_FILENO,
						"Invalid input. Please enter a single-word command.\n", 53);
				return;
			}
		}

		if (strlen(buffer) == 0)
		{
			return;
		}

		executeCommand(buffer, n);
	}
}

/**
 * main - The main function.
 *
 * This function initializes the shell
 * and enters the main loop to process user input.
 *
 * Return: 0 on successful execution.
 */

int main(void)
{
	char buffer[1024];
	ssize_t n;

	while (1)
	{
		displayPrompt();

		n = read(STDIN_FILENO, buffer, sizeof(buffer));

		if (n == -1)
		{
			perror("read");
			exit(EXIT_FAILURE);
		}

		if (n == 0)
		{
			write(STDOUT_FILENO, "\nExiting the shell\n", 20);
			exit(EXIT_SUCCESS);
		}

		processUserInput(buffer, n);
	}
	return (0);
}
