/*
** EPITECH PROJECT, 2023
** rpg
** File description:
** trigger.c
*/
#include "rpg.h"
#include "helper.h"


static void handle_interact(npc_t *tmp, rpg_t *rpg, sfVector2f mouse)
{
    if (in_bounds(tmp->asset, mouse)) {
        if (tmp->oninteract){
            tmp->oninteract(rpg, tmp);
        }
    }
}

void trigger_npc(rpg_t *rpg)
{
    sfVector2f pos = rpg->player->pos;
    npc_t *tmp = rpg->npcs;

    if (rpg->state != PLAYING)
        return;
    while (tmp) {
        if (tmp->should_display(rpg) == 1) {
            handle_interact(tmp, rpg, pos);
        }
        tmp = tmp->next;
    }
}
