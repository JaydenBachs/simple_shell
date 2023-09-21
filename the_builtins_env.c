#include "shell.h"

/**
 * builtin_env - Display the current environment variables.
 * @data: A structure containing program data.
 *
 * This function shows the environment variables in the current shell session.
 * If no arguments are provided, it prints all environment variables.
 * If an argument in the format "name=value" is provided, it temporarily modifies the variable's value,
 * displays the updated environment, and then reverts the value back to its original state.
 *
 * @return: Zero on success, or a non-zero value on error.
 */
int builtin_env(data_of_program *data)
{
    int i;
    char cpname[50] = {'\0'};
    char *var_copy = NULL;

    /* If no arguments are provided */
    if (data->tokens[1] == NULL)
        print_environ(data);
    else
    {
        for (i = 0; data->tokens[1][i]; i++)
        {
            /* Check for the existence of '=' character */
            if (data->tokens[1][i] == '=')
            {
                /* Temporarily modify the value of the variable */
                var_copy = str_duplicate(env_get_key(cpname, data));
                if (var_copy != NULL)
                    env_set_key(cpname, data->tokens[1] + i + 1, data);

                /* Print the environment */
                print_environ(data);

                if (env_get_key(cpname, data) == NULL)
                {
                    /* Display the variable if it doesn't exist in the environment */
                    _print(data->tokens[1]);
                    _print("\n");
                }
                else
                {
                    /* Revert to the previous value of the variable */
                    env_set_key(cpname, var_copy, data);
                    free(var_copy);
                }
                return (0);
            }
            cpname[i] = data->tokens[1][i];
        }
        errno = 2;
        perror(data->command_name);
        errno = 127;
    }
    return (0);
}

/**
 * builtin_set_env - Set or modify an environment variable.
 * @data: A structure containing program data.
 *
 * This function sets or modifies an environment variable.
 * It requires two arguments in the format "name=value".
 * If a third argument is provided, an error is displayed.
 *
 * @return: Zero on success, or a non-zero value on error.
 */
int builtin_set_env(data_of_program *data)
{
    /* Validate arguments */
    if (data->tokens[1] == NULL || data->tokens[2] == NULL)
        return (0);

    if (data->tokens[3] != NULL)
    {
        errno = E2BIG;
        perror(data->command_name);
        return (5);
    }

    env_set_key(data->tokens[1], data->tokens[2], data);

    return (0);
}

/**
 * builtin_unset_env - Remove an environment variable.
 * @data: A structure containing program data.
 *
 * This function removes an environment variable.
 * It requires one argument, which is the name of the variable to be removed.
 * If more than one argument is provided, an error is displayed.
 *
 * @return: Zero on success, or a non-zero value on error.
 */
int builtin_unset_env(data_of_program *data)
{
    /* Validate arguments */
    if (data->tokens[1] == NULL)
        return (0);

    if (data->tokens[2] != NULL)
    {
        errno = E2BIG;
        perror(data->command_name);
        return (5);
    }

    env_remove_key(data->tokens[1], data);

    return (0);
}

