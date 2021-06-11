/*
** EPITECH PROJECT, 2019
** my_sokoban
** File description:
** Count the number of characters in a string until sep is found
*/

unsigned int my_count_until_sep(char const *str, char const sep)
{
    unsigned int count = 0;

    for (unsigned int i = 0 ; str[i] && str[i] != sep ; i++)
        count++;
    return (count);
}