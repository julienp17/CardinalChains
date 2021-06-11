/*
** EPITECH PROJECT, 2021
** strace [WSL: Ubuntu-20.04]
** File description:
** my_strisnumpos
*/

#include <stdbool.h>

bool my_str_isnum_pos(char const *str)
{
    unsigned int i = 0;

    if (str[0] == 0)
        return (false);
    while (str[i]) {
        if (str[i] < '0' || str[i] > '9')
            return (false);
        i = i + 1;
    }
    return (true);
}