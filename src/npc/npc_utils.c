/*
** EPITECH PROJECT, 2023
** rpg
** File description:
** npc_utils.c
*/
#include "rpg.h"

npc_t *get_npc_by_asset(asset_t *asset, rpg_t *rpg)
{
    npc_t *tmp = rpg->npcs;

    while (tmp) {
        if (tmp->asset == asset)
            return (tmp);
        tmp = tmp->next;
    }
    return (NULL);
}

npc_t *get_npc_by_oninteract(void (*oninteract)(rpg_t *, npc_t *), rpg_t *rpg)
{
    npc_t *tmp = rpg->npcs;

    while (tmp) {
        if (tmp->oninteract == oninteract)
            return (tmp);
        tmp = tmp->next;
    }
    return (NULL);
}
