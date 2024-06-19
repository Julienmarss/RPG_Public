/*
** EPITECH PROJECT, 2023
** rpg
** File description:
** get_asset.c
*/

#include "rpg.h"
#include "helper.h"

asset_t *get_asset_from_onclick(rpg_t *rpg, void (*onclick)(rpg_t *rpg))
{
    asset_t *tmp = rpg->assets;

    while (tmp) {
        if (tmp->onclick == onclick)
            return tmp;
        tmp = tmp->next;
    }
    return tmp;
}

asset_t *get_asset_from_oninteract(rpg_t *rpg,
    void (*oninteract)(rpg_t *rpg, asset_t *asset))
{
    asset_t *tmp = rpg->assets;

    while (tmp) {
        if (tmp->oninteract == oninteract)
            return tmp;
        tmp = tmp->next;
    }
    return tmp;
}

int remove_asset(rpg_t *rpg, asset_t *asset)
{
    asset_t *tmp = rpg->assets;
    asset_t *prev = NULL;

    while (tmp) {
        if (tmp == asset) {
            prev->next = tmp->next;
            destroy_texture(tmp->texture);
            destroy_sprite(tmp->sprite);
            sfRectangleShape_destroy(tmp->shape);
            free(tmp);
            return 1;
        }
        prev = tmp;
        tmp = tmp->next;
    }
    return 0;
}
