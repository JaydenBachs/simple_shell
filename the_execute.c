#include "shell.h"
/**
 * Execute Command - Execute a command with its full path variables.
 * @data: A pointer to the program's data.
 *
 * This function attempts to execute a command by first checking if it's a built-in command.
 * If the command is built-in, it is executed and its return value is returned.
 * If the command is not built-in, the function searches for it in the file system.
 * If found, it creates a child process and executes the program within it using execve.
 * The parent process waits for the child process to complete and retrieves the exit status.
 *
 * @return: 0 if successful, or -1 if an error occurs.
 */
int execute(data_of_program *data)
{
	int retval = 0, status;
	pid_t pidd;

	/* Check if the program is a built-in command */
	retval = builtins_list(data);
	if (retval != -1)
		return (retval);

	/* Search for the program in the file system */
	retval = find_program(data);
	if (retval)
	{
		/* Program not found in the file system */
		return (retval);
	}
	else
	{
		/* Program found in the file system */
		pidd = fork(); /* create a child process */
		if (pidd == -1)
		{
			/* if the fork call failed */
			perror(data->command_name);
			exit(EXIT_FAILURE);
		}
		if (pidd == 0)
		{
			/* Child process: execute the program */
			retval = execve(data->tokens[0], data->tokens, data->env);
			if (retval == -1) /* If an error occurs during execution */
				perror(data->command_name), exit(EXIT_FAILURE);
		}
		else
		{/* Parent process: wait for the child and check its exit status */
			wait(&status);
			if (WIFEXITED(status))
				errno = WEXITSTATUS(status);
			else if (WIFSIGNALED(status))
				errno = 128 + WTERMSIG(status);
		}
	}
	return (0);
}

