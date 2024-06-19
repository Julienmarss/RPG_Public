/*
** EPITECH PROJECT, 2023
** rpg
** File description:
** onclick.c
*/
#include "rpg.h"

static int in_bounds2(asset_t *asset, sfVector2i mouse)
{
    sfFloatRect bounds = sfSprite_getGlobalBounds(asset->sprite);
    sfFloatRect bounds_shape = sfRectangleShape_getGlobalBounds(asset->shape);

    if (sfFloatRect_contains(&bounds, mouse.x, mouse.y))
        return 1;
    if (sfFloatRect_contains(&bounds_shape, mouse.x, mouse.y))
        return 1;
    return 0;
}

static int in_bounds3(asset_t *asset, sfVector2i pos)
{
    sfFloatRect bounds = sfText_getGlobalBounds(asset->text);

    if (sfFloatRect_contains(&bounds, pos.x, pos.y)){
        return 1;
    }
    return 0;
}

static void handle_click(asset_t *asset, rpg_t *rpg, sfVector2i pos)
{
    if (asset->text != NULL){
        if (in_bounds3(asset, pos)){
            asset->oninteract(rpg, asset);
        }
        return;
    }
    if (in_bounds2(asset, pos)) {
        if (asset->onclick)
            asset->onclick(rpg);
    }
}

void click(rpg_t *rpg, sfEvent event)
{
    asset_t *tmp = rpg->assets;
    sfVector2i mouse = sfMouse_getPositionRenderWindow(rpg->window);

    if (rpg->state == IN_FIGHT) {
        fight(rpg, mouse);
    }
    (void)event;
    while (tmp) {
        if (tmp->should_display(rpg) == 1) {
            handle_click(tmp, rpg, mouse);
        }
        tmp = tmp->next;
    }
}
