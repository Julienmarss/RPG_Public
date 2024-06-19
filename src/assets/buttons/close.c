/*
** EPITECH PROJECT, 2023
** rpg
** File description:
** close.c
*/

#include "rpg.h"
#include "helper.h"

void close_game(rpg_t *rpg)
{
    if (rpg->state == WAITING)
        sfRenderWindow_close(rpg->window);
    back(rpg);
}

void init_close(rpg_t *rpg)
{
    char *path = "resources/images/close.png";
    asset_t *asset = add_asset(rpg, path, &should_always_display, &close_game);
    sfVector2u size = sfTexture_getSize(asset->texture);

    sfSprite_setScale(asset->sprite, (sfVector2f){0.1, 0.1});
    size.x /= 10;
    size.y /= 10;
    set_asset_pos(asset, (sfVector2f){0, 0}, size);
    init_demo(rpg);
}

void change_close_position(rpg_t *rpg)
{
    asset_t *asset = get_asset_from_onclick(rpg, &close_game);
    sfVector2f center = sfView_getCenter(rpg->view);
    sfVector2f size = sfView_getSize(rpg->view);
    sfVector2f TopLeft = {center.x - size.x / 2, center.y - size.y / 2};

    sfSprite_setPosition(asset->sprite, TopLeft);
}
