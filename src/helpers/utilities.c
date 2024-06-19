/*
** EPITECH PROJECT, 2023
** rpg
** File description:
** utilities.c
*/
#include "helper.h"

sfVector2f get_window_center(sfRenderWindow *window)
{
    sfVector2u size = sfRenderWindow_getSize(window);
    sfVector2f center = {size.x / 2, size.y / 2};

    return center;
}

sfVector2f get_sprite_center(sfSprite *sprite)
{
    sfFloatRect bounds = sfSprite_getGlobalBounds(sprite);
    sfVector2f center = {bounds.width / 2, bounds.height / 2};

    return center;
}

sfVector2f get_sprite_position(sfSprite *sprite)
{
    sfFloatRect bounds = sfSprite_getGlobalBounds(sprite);
    sfVector2f position = {bounds.left, bounds.top};

    return position;
}

sfVector2u get_window_size(sfRenderWindow *window)
{
    sfVector2u size = sfRenderWindow_getSize(window);

    return size;
}

void set_shape(sfRectangleShape *shape, sfVector2f pos)
{
    sfRectangleShape_setOutlineColor(shape, sfTransparent);
    sfRectangleShape_setOutlineThickness(shape, 2);
    sfRectangleShape_setFillColor(shape, sfTransparent);
    sfRectangleShape_setSize(shape, (sfVector2f){100, 100});
    sfRectangleShape_setOrigin(shape, (sfVector2f){0, 0});
    sfRectangleShape_setPosition(shape, pos);
}
