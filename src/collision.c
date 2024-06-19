/*
** EPITECH PROJECT, 2023
** rpg
** File description:
** collision.c
*/

#include "rpg.h"
#include "helper.h"

static int is_in_collision(rpg_t *rpg, int x, int y)
{
    sfColor pixelColor;
    sfColor pixelColor2;
    sfVector2u size;
    int sizeX;
    int sizeY;

    if (rpg->map->image_copy == NULL || rpg->map->image_copy2 == NULL)
        return 0;
    size = sfImage_getSize(rpg->map->image_copy);
    sizeX = size.x;
    sizeY = size.y;
    if (x < 0 || x >= sizeX || y < 0 || y >= sizeY) {
        printf("Out of bounds\n");
        return 0;
    }
    pixelColor = sfImage_getPixel(rpg->map->image_copy, x, y);
    pixelColor2 = sfImage_getPixel(rpg->map->image_copy2, x, y);
    return (pixelColor.a != 0 || pixelColor2.a != 0);
}

int check_collision(rpg_t *rpg, sfVector2f pos)
{
    sfFloatRect playerBounds = sfSprite_getGlobalBounds(rpg->player->sprite);
    int playerX = pos.x + playerBounds.width / 2;
    int playerY = pos.y + playerBounds.height / 2;

    return is_in_collision(rpg, playerX, playerY);
}

int check_surroundings(rpg_t *rpg, sfVector2f pos)
{
    sfFloatRect playerBounds = sfSprite_getGlobalBounds(rpg->player->sprite);
    int playerX = pos.x + playerBounds.width / 2;
    int playerY = pos.y + playerBounds.height / 2;
    int speed = 2;

    if (!is_in_collision(rpg, playerX - speed, playerY))
        return 0;
    if (!is_in_collision(rpg, playerX + speed, playerY))
        return 0;
    if (!is_in_collision(rpg, playerX, playerY - speed))
        return 0;
    if (!is_in_collision(rpg, playerX, playerY + speed))
        return 0;
    return 1;
}
