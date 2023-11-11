#include "shell.h"

/**
 * executeCommand - Handle the command execution and display the exit status.
 *
 * @buffer: The input buffer containing the user's command.
 *
 * @n: The number of bytes read.
 *
 */

void executeCommand(char *buffer, ssize_t n)
{
	pid_t child_pid = fork();

	if (child_pid == -1)
	{
		perror("Fork error\n");
	}
	else if (child_pid == 0)
	{
		buffer[n - 1] = '\0';
		char *args[] = {buffer, NULL};


		if (execvp(buffer, args) == -1)
		{
			char error_message[] = "Command not found: ";

			write(STDOUT_FILENO, error_message, strlen(error_message));
			write(STDOUT_FILENO, buffer, n - 1);
			write(STDOUT_FILENO, "\n", 1);
			exit(EXIT_FAILURE);
		}
	}
	else
	{
		int status;

		waitpid(child_pid, &status, 0);
		displayExitStatus(status);
	}
}

/**
 * displayExitStatus - Display the exit status of the child process.
 *
 * @status: The exit status of the child process.
 */

void displayExitStatus(int status)
{
	if (WIFEXITED(status))
	{

	}
	else
	{
		char error_message[] = "Command did not exit normally\n";

		write(STDOUT_FILENO, error_message, strlen(error_message));
	}
}
