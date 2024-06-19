/*
** EPITECH PROJECT, 2023
** rpg
** File description:
** npc.c
*/
#include "rpg.h"
#include "helper.h"
#include <string.h>

void init_npc(rpg_t *rpg)
{
    rpg->npcs = NULL;
    init_apple_npc(rpg);
    init_mob_npc(rpg);
    init_smith_npc(rpg);
}

npc_t *add_npc(rpg_t *rpg, asset_t *asset,
    int (*should_display)(rpg_t *rpg),
    void (*oninteract)(rpg_t *rpg, npc_t *npc))
{
    npc_t *npc = malloc(sizeof(npc_t));
    npc_t *tmp = rpg->npcs;

    strcpy(npc->name, "default");
    strcpy(npc->meta, "");
    npc->asset = asset;
    set_shape(npc->asset->shape, (sfVector2f){0, 0});
    npc->should_display = should_display;
    npc->oninteract = oninteract;
    npc->next = NULL;
    npc->text = NULL;
    npc->font = NULL;
    if (tmp == NULL) {
        rpg->npcs = npc;
        return npc;
    }
    while (tmp->next)
        tmp = tmp->next;
    tmp->next = npc;
    return npc;
}

void destroy_npc(npc_t *npc)
{
    npc_t *tmp;

    while (npc != NULL) {
        tmp = npc;
        npc = npc->next;
        if (tmp->text != NULL)
            sfText_destroy(tmp->text);
        if (tmp->font != NULL)
            sfFont_destroy(tmp->font);
        free(tmp);
    }
}

void set_npc_pos(npc_t *npc, sfVector2f pos, sfVector2u size)
{
    sfSprite_setPosition(npc->asset->sprite, pos);
    sfRectangleShape_setPosition(npc->asset->shape, pos);
    npc->asset->pos = pos;
    sfRectangleShape_setSize(npc->asset->shape, (sfVector2f){size.x, size.y});
}

void set_npc_name(npc_t *npc, char *name, sfVector2f pos)
{
    npc->text = sfText_create();
    npc->font = sfFont_createFromFile("resources/fonts/font.ttf");
    sfText_setString(npc->text, name);
    sfText_setCharacterSize(npc->text, 20);
    sfText_setFont(npc->text, npc->font);
    sfText_setColor(npc->text, sfTransparent);
    sfText_setPosition(npc->text, (sfVector2f){pos.x, pos.y - 30});
}
