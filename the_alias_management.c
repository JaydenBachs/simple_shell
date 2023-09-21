#include "shell.h"

/**
 * print_alias - Display, add, remove, or list aliases.
 * @data: Structure holding program data.
 * @alias: Name of the alias to display.
 *
 * This function displays the specified alias or lists all aliases if none is provided.
 * It iterates through the alias list and displays aliases matching the given name.
 *
 * @return: Zero if successful, a non-zero value if the alias is not found.
 */
int print_alias(data_of_program *data, char *alias)
{
    int i, j, alias_length;
    char buffer[250] = {'\0'};

    if (data->alias_list)
    {
        alias_length = str_length(alias);
        for (i = 0; data->alias_list[i]; i++)
        {
            if (!alias || (str_compare(data->alias_list[i], alias, alias_length)
                && data->alias_list[i][alias_length] == '='))
            {
                for (j = 0; data->alias_list[i][j]; j++)
                {
                    buffer[j] = data->alias_list[i][j];
                    if (data->alias_list[i][j] == '=')
                        break;
                }
                buffer[j + 1] = '\0';
                buffer_add(buffer, "'");
                buffer_add(buffer, data->alias_list[i] + j + 1);
                buffer_add(buffer, "'\n");
                _print(buffer);
            }
        }
    }

    return (0);
}


/**
 * get_alias - Retrieve the value of an alias.
 * @data: Structure holding program data.
 * @name: Name of the alias to retrieve.
 *
 * This function retrieves the value of the specified alias.
 * It iterates through the alias list and checks for a match with the provided name.
 *
 * @return: The value of the alias if found, or NULL if not found.
 */
char *get_alias(data_of_program *data, char *name)
{
    int i, alias_length;

    /* Validate the arguments */
    if (name == NULL || data->alias_list == NULL)
        return (NULL);

    alias_length = str_length(name);

    for (i = 0; data->alias_list[i]; i++)
    {
        /* Iterate through the alias list and check for a match with the provided name */
        if (str_compare(name, data->alias_list[i], alias_length) &&
            data->alias_list[i][alias_length] == '=')
        {
            /* Return the value of the alias when a match is found */
            return (data->alias_list[i] + alias_length + 1);
        }
    }

    /* Returns NULL if the alias is not found */
    return (NULL);
}

/**
 * set_alias - Create or overwrite an alias.
 * @alias_string: Alias to be set in the format (name='value').
 * @data: Structure holding program data.
 *
 * This function creates or overwrites an alias.
 * It iterates through the alias list and checks if the alias already exists.
 * If the alias exists, it is replaced with the new alias.
 * If the alias value is another alias, it resolves the value and sets the alias accordingly.
 *
 * @return: Zero if successful, a non-zero value if an error occurs.
 */
int set_alias(char *alias_string, data_of_program *data)
{
    int i, j;
    char buffer[250] = {'0'}, *temp = NULL;

    /* Validate the arguments */
    if (alias_string == NULL || data->alias_list == NULL)
        return (1);

    /* Iterate through the alias string to find the '=' character */
    for (i = 0; alias_string[i]; i++)
    {
        if (alias_string[i] != '=')
            buffer[i] = alias_string[i];
        else
        {
            /* Search if the value of the alias is another alias */
            temp = get_alias(data, alias_string + i + 1);
            break;
        }
    }

    /* Iterate through the alias list and check if the alias already exists */
    for (j = 0; data->alias_list[j]; j++)
    {
        if (str_compare(buffer, data->alias_list[j], i) &&
            data->alias_list[j][i] == '=')
        {
            /* If the alias already exists, free the memory */
            free(data->alias_list[j]);
            break;
        }
    }

    /* For adding the alias */
    if (temp)
    {
        /* If the alias value is another alias, proceed with this */
        buffer_add(buffer, "=");
        buffer_add(buffer, temp);
        data->alias_list[j] = str_duplicate(buffer);
    }
    else
    {
        /* If the alias does not exist, proceed with this */
        data->alias_list[j] = str_duplicate(alias_string);
    }

    return (0);
}

