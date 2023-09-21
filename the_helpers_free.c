#include "shell.h"

/**
 * Free Recurrent Data - Release memory for fields used in each loop iteration.
 * @data: A pointer to the program's data structure.
 *
 * This function frees memory for the fields that need to be cleared in each loop iteration.
 *
 * @return: Nothing.
 */
void free_recurrent_data(data_of_program *data)
{
	if (data->tokens)
		free_array_of_pointers(data->tokens);
	if (data->input_line)
		free(data->input_line);
	if (data->command_name)
		free(data->command_name);

	data->input_line = NULL;
	data->command_name = NULL;
	data->tokens = NULL;
}

/**
 * Free All Data - Release memory for all fields in the program's data structure.
 * @data: A pointer to the program's data structure.
 *
 * This function frees memory for all fields in the program's data structure.
 *
 * @return: Nothing.
 */
void free_all_data(data_of_program *data)
{
	if (data->file_descriptor != 0)
	{
		if (close(data->file_descriptor))
			perror(data->program_name);
	}
	free_recurrent_data(data);
	free_array_of_pointers(data->env);
	free_array_of_pointers(data->alias_list);
}

/**
 * Free Array of Pointers - Free each pointer in an array of pointers and the array itself.
 * @array: An array of pointers to be freed.
 *
 * This function releases memory for each pointer in an array of pointers and then frees the array itself.
 *
 * @return: Nothing.
 */
void free_array_of_pointers(char **array)
{
	int i;

	if (array != NULL)
	{
		for (i = 0; array[i]; i++)
			free(array[i]);

		free(array);
		array = NULL;
	}
}

