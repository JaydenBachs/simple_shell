#include "shell.h"

/**
 * Long to String - Convert a number to a string representation.
 * @number: The number to be converted to a string.
 * @string: A buffer to store the resulting string.
 * @base: The base for the conversion.
 *
 * This function converts a given number to a string representation using the specified base.
 *
 * @return: Nothing.
 */
void long_to_string(long number, char *string, int base)
{
	int index = 0, inNegative = 0;
	long cociente = number;
	char letters[] = {"0123456789abcdef"};

	if (cociente == 0)
		string[index++] = '0';

	if (string[0] == '-')
		inNegative = 1;

	while (cociente)
	{
		if (cociente < 0)
			string[index++] = letters[-(cociente % base)];
		else
			string[index++] = letters[cociente % base];
		cociente /= base;
	}
	if (inNegative)
		string[index++] = '-';

	string[index] = '\0';
	str_reverse(string);
}


/**
 * ATOI - Convert a string to an integer.
 * @s: A pointer to the source string.
 *
 * This function converts a string to an integer.
 *
 * @return: The integer value of the string, or 0.
 */
int _atoi(char *s)
{
	int sign = 1;
	unsigned int number = 0;
	
	while (!('0' <= *s && *s <= '9') && *s != '\0')
	{
		if (*s == '-')
			sign *= -1;
		if (*s == '+')
			sign *= +1;
		s++;
	}
	
	while ('0' <= *s && *s <= '9' && *s != '\0')
	{

		number = (number * 10) + (*s - '0');
		s++;
	}
	return (number * sign);
}

/**
 * Count Characters - Count the occurrences of a character in a string.
 * @string: A pointer to the source string.
 * @character: A string containing characters to be counted.
 *
 * This function counts the occurrences of characters from the "character" string within the "string."
 *
 * @return: The count of character occurrences.
 */
int count_characters(char *string, char *character)
{
	int i = 0, counter = 0;

	for (; string[i]; i++)
	{
		if (string[i] == character[0])
			counter++;
	}
	return (counter);
}

