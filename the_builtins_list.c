#include "shell.h"

/**
 * Execute Built-in Commands - Search and execute the matching built-in command.
 * @data: Structure containing program data.
 *
 * This function scans for a matching built-in command in the command list.
 * If a match is found, it executes the corresponding function and returns its result.
 * If no match is found, it returns -1.
 *
 * @return: The return value of the executed function on a match, or -1 if there is no match.
 **/
int builtins_list(data_of_program *data)
{
    int iterator;
    builtins options[] = {
        {"exit", builtin_exit},
        {"help", builtin_help},
        {"cd", builtin_cd},
        {"alias", builtin_alias},
        {"env", builtin_env},
        {"setenv", builtin_set_env},
        {"unsetenv", builtin_unset_env},
        {NULL, NULL}
    };

    /* Iterate through the built-in commands list */
    for (iterator = 0; options[iterator].builtin != NULL; iterator++)
    {
        /* Check for a match between the provided command and a built-in command */
        if (str_compare(options[iterator].builtin, data->command_name, 0))
        {
            /* Execute the corresponding function and return its result */
            return (options[iterator].function(data));
        }
    }

    /* Return -1 when there is no match */
    return (-1);
}

