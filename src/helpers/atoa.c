/*
** EPITECH PROJECT, 2023
** rpg
** File description:
** atoa.c
*/
#include "rpg.h"
#include "stdlib.h"

void my_revstr(char *str)
{
    int i = 0;
    int j = 0;
    char tmp;

    while (str[i] != '\0')
        i++;
    i--;
    while (i > j) {
        tmp = str[i];
        str[i] = str[j];
        str[j] = tmp;
        i--;
        j++;
    }
}

char *my_itoa(int nb)
{
    int i = 0;
    char *str = malloc(sizeof(char) * 100);

    if (nb == 0)
        return "0";
    while (nb != 0) {
        str[i] = nb % 10 + '0';
        nb = nb / 10;
        i++;
    }
    str[i] = '\0';
    my_revstr(str);
    return str;
}
