/*
** EPITECH PROJECT, 2023
** rpg
** File description:
** move.c
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

static void handle_interact(npc_t *tmp, rpg_t *rpg, sfVector2i mouse)
{
    if (in_bounds2(tmp->asset, mouse)) {
        if (tmp->oninteract)
            tmp->oninteract(rpg, tmp);
    }
}

int move(rpg_t *rpg, sfEvent event)
{
    npc_t *tmp = rpg->npcs;
    sfVector2i mouse = sfMouse_getPositionRenderWindow(rpg->window);

    (void)event;
    while (tmp) {
        if (tmp->should_display(rpg) == 1) {
            handle_interact(tmp, rpg, mouse);
        }
        tmp = tmp->next;
    }
    return 0;
}
