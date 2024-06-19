/*
** EPITECH PROJECT, 2023
** rpg
** File description:
** window.c
*/
#include "rpg.h"

sfRenderWindow *create_window(void)
{
    sfVideoMode mode = {1920, 1080, 32};
    sfRenderWindow *window;

    window = sfRenderWindow_create(mode, "RPG", sfClose | sfResize, NULL);
    return window;
}
