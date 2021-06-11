/*
** EPITECH PROJECT, 2020
** MUL_my_rpg_2019
** File description:
** Returns the number of rows in an array of strings
*/

unsigned int my_strarr_len(char * const *arr)
{
    unsigned int len = 0;

    while (arr[len])
        len++;
    return (len);
}