/*
** EPITECH PROJECT, 2023
** rpg
** File description:
** File to move sprites and set rectangles
*/
#include "helper.h"
#include "rpg.h"

void move_rect(sfIntRect *rect, int offset, int max_value)
{
    rect->left += offset;
    if (rect->left >= max_value) {
        rect->left = 0;
    }
}

sfIntRect set_rect(sfSprite *sprite, int width, int height)
{
    sfIntRect rect;

    rect.top = 0;
    rect.left = 0;
    rect.width = width;
    rect.height = height;
    sfSprite_setTextureRect(sprite, rect);
    return rect;
}

int in_bounds(asset_t *asset, sfVector2f mouse)
{
    sfFloatRect bounds;
    sfFloatRect bounds_shape;

    if (asset->sprite == NULL)
        return 0;
    bounds = sfSprite_getGlobalBounds(asset->sprite);
    bounds_shape = sfRectangleShape_getGlobalBounds(asset->shape);
    if (asset->oninteract != NULL)
    if (sfFloatRect_contains(&bounds, mouse.x, mouse.y)){
        return 1;
    }
    if (sfFloatRect_contains(&bounds_shape, mouse.x, mouse.y)) {
        return 1;
    }
    return 0;
}
