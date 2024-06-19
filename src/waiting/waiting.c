/*
** EPITECH PROJECT, 2023
** rpg
** File description:
** waiting.c
*/
#include "rpg.h"
#include "helper.h"

static void init_logo(rpg_t *rpg, sfVector2f pos)
{
    char *path = "resources/images/logo.png";
    asset_t *asset;
    sfVector2u size;

    asset = add_asset(rpg, path, &should_when_waiting, NULL);
    size = sfTexture_getSize(asset->texture);
    sfSprite_setScale(asset->sprite, (sfVector2f){0.2, 0.2});
    pos.x -= size.x / 9;
    pos.y -= size.y / 3;
    size.x /= 5;
    size.y /= 5;
    set_asset_pos(asset, pos, size);
    sfRectangleShape_setSize(asset->shape, (sfVector2f){size.x, size.y});
}

void init_waiting(rpg_t *rpg)
{
    sfVector2f pos = get_window_center(rpg->window);

    init_logo(rpg, pos);
}
