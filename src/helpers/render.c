/*
** EPITECH PROJECT, 2023
** rpg
** File description:
** render.c
*/
#include "rpg.h"

void render_shape(sfRenderWindow *window, sfRectangleShape *shape)
{
    sfRenderWindow_drawRectangleShape(window, shape, NULL);
}
