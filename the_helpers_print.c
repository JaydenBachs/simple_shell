#include "shell.h"

/**
 * Print to Standard Output - Writes an array of characters to the standard output.
 * @string: A pointer to the array of characters to be written.
 *
 * This function writes the specified array of characters to the standard output.
 *
 * @return: The number of bytes written, or -1 on error (with errno set).
 */
int _print(char *string)
{
	return (write(STDOUT_FILENO, string, str_length(string)));
}
/**
 * Print to Standard Error - Writes an array of characters to the standard error.
 * @string: A pointer to the array of characters to be written.
 *
 * This function writes the specified array of characters to the standard error.
 *
 * @return: The number of bytes written, or -1 on error (with errno set).
 */
int _printe(char *string)
{
	return (write(STDERR_FILENO, string, str_length(string)));
}

/**
 * Print Error Message - Writes an error message to the standard error.
 * @errorcode: The error code to print.
 * @data: A pointer to the program's data.
 *
 * This function writes an error message to the standard error based on the given error code and program data.
 *
 * @return: 0 if successful.
 */
int _print_error(int errorcode, data_of_program *data)
{
	char n_as_string[10] = {'\0'};

	long_to_string((long) data->exec_counter, n_as_string, 10);

	if (errorcode == 2 || errorcode == 3)
	{
		_printe(data->program_name);
		_printe(": ");
		_printe(n_as_string);
		_printe(": ");
		_printe(data->tokens[0]);
		if (errorcode == 2)
			_printe(": Illegal number: ");
		else
			_printe(": can't cd to ");
		_printe(data->tokens[1]);
		_printe("\n");
	}
	else if (errorcode == 127)
	{
		_printe(data->program_name);
		_printe(": ");
		_printe(n_as_string);
		_printe(": ");
		_printe(data->command_name);
		_printe(": not found\n");
	}
	else if (errorcode == 126)
	{
		_printe(data->program_name);
		_printe(": ");
		_printe(n_as_string);
		_printe(": ");
		_printe(data->command_name);
		_printe(": Permission denied\n");
	}
	return (0);
}

