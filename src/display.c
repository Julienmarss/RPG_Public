/*
** EPITECH PROJECT, 2023
** rpg
** File description:
** display.c
*/
#include "rpg.h"
#include "helper.h"

void display_playing(rpg_t *rpg)
{
    sfRenderWindow_setView(rpg->window, rpg->view);
    sfRenderWindow_clear(rpg->window, sfBlack);
    if (rpg->map->sprite)
        sfRenderWindow_drawSprite(rpg->window, rpg->map->sprite, NULL);
}

static void display_asset(rpg_t *rpg, asset_t *tmp)
{
    if (tmp->sprite != NULL) {
        sfRenderWindow_drawSprite(rpg->window, tmp->sprite, NULL);
    }
    if (tmp->shape != NULL)
        render_shape(rpg->window, tmp->shape);
    if (tmp->should_display(rpg) && tmp->text)
        sfRenderWindow_drawText(rpg->window, tmp->text, NULL);
}

void display_assets(rpg_t *rpg)
{
    asset_t *tmp = rpg->assets;

    while (tmp != NULL) {
        if (tmp->should_display(rpg)) {
            display_asset(rpg, tmp);
        }
        tmp = tmp->next;
    }
}

void display_npc(rpg_t *rpg, npc_t *npc)
{
    if (npc == NULL)
        return;
    if (npc->text)
        sfRenderWindow_drawText(rpg->window, npc->text, NULL);
}

void display_npcs(rpg_t *rpg)
{
    npc_t *tmp = rpg->npcs;

    while (tmp != NULL) {
        if (tmp->should_display(rpg)){
            display_npc(rpg, tmp);
        }
        tmp = tmp->next;
    }
}
