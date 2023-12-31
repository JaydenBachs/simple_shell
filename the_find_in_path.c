#include "shell.h"

int check_file(char *full_path);

/**
 * Find Program - Search for an executable program in the PATH.
 * @data: A pointer to the program's data.
 *
 * This function attempts to locate an executable program in the PATH environment variable.
 * If the program is found, its full path is updated in the program's data structure.
 *
 * @return: 0 if the program is found and executable, an error code otherwise.
 */
int find_program(data_of_program *data)
{
	int i = 0, ret_code = 0;
	char **directories;

	if (!data->command_name)
		return (2);

	/* Check if it's a full path or an executable in the current directory */
	if (data->command_name[0] == '/' || data->command_name[0] == '.')
		return (check_file(data->command_name));

	free(data->tokens[0]);
	data->tokens[0] = str_concat(str_duplicate("/"), data->command_name);
	if (!data->tokens[0])
		return (2);

	directories = tokenize_path(data);/* Search in the PATH */

	if (!directories || !directories[0])
	{
		errno = 127;
		return (127);
	}
	for (i = 0; directories[i]; i++)
	{
		/* Append the program name to the path */
		directories[i] = str_concat(directories[i], data->tokens[0]);
		ret_code = check_file(directories[i]);
		if (ret_code == 0 || ret_code == 126)
		{/* The file was found, is not a directory, and has execute permissions */
			errno = 0;
			free(data->tokens[0]);
			data->tokens[0] = str_duplicate(directories[i]);
			free_array_of_pointers(directories);
			return (ret_code);
		}
	}
	free(data->tokens[0]);
	data->tokens[0] = NULL;
	free_array_of_pointers(directories);
	return (ret_code);
}

/**
 * Tokenize Path - Tokenize the PATH environment variable into an array of directories.
 * @data: A pointer to the program's data.
 *
 * This function tokenizes the PATH environment variable into an array of directory paths.
 *
 * @return: An array of directory paths.
 */
char **tokenize_path(data_of_program *data)
{
	int i = 0;
	int counter_directories = 2;
	char **tokens = NULL;
	char *PATH;

	/* PATH not found or empty */
	PATH = env_get_key("PATH", data);
	if ((PATH == NULL) || PATH[0] == '\0')
	{/*path not found*/
		return (NULL);
	}

	PATH = str_duplicate(PATH);

	/* Find the number of directories in the PATH */
	for (i = 0; PATH[i]; i++)
	{
		if (PATH[i] == ':')
			counter_directories++;
	}

	/* Reserve space for the array of pointers */
	tokens = malloc(sizeof(char *) * counter_directories);

	/* Tokenize and duplicate each token of PATH */
	i = 0;
	tokens[i] = str_duplicate(_strtok(PATH, ":"));
	while (tokens[i++])
	{
		tokens[i] = str_duplicate(_strtok(NULL, ":"));
	}

	free(PATH);
	PATH = NULL;
	return (tokens);

}

/**
 * Check File - Check if a file exists, is not a directory, and has execute permissions.
 * @full_path: Pointer to the full file name.
 *
 * This function checks whether a file exists, is not a directory, and has execute permissions.
 *
 * @return: 0 on success, or an error code if the file does not meet the criteria.
 */
int check_file(char *full_path)
{
	struct stat sb;

	if (stat(full_path, &sb) != -1)
	{
		if (S_ISDIR(sb.st_mode) ||  access(full_path, X_OK))
		{
			errno = 126;
			return (126);
		}
		return (0);
	}
	/* If the file does not exist */
	errno = 127;
	return (127);
}

