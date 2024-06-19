/*
** EPITECH PROJECT, 2023
** rpg
** File description:
** trigger.c
*/
#include "rpg.h"
#include "helper.h"

static void handle_interactt(asset_t *tmp, rpg_t *rpg, sfVector2f mouse)
{
    if (in_bounds(tmp, mouse)) {
        if (tmp->oninteract)
            tmp->oninteract(rpg, tmp);
    }
}

void trigger_assets(rpg_t *rpg)
{
    asset_t *tmp = rpg->assets;
    sfVector2f mouse = rpg->player->pos;

    while (tmp) {
        if (tmp->should_display(rpg) == 1) {
            handle_interactt(tmp, rpg, mouse);
        }
        tmp = tmp->next;
    }
}
