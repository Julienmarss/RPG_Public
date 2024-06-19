/*
** EPITECH PROJECT, 2023
** rpg
** File description:
** free.c
*/
#include "rpg.h"

int free_all(rpg_t *rpg)
{
    sfClock_destroy(rpg->clock);
    destroy_map(rpg->map);
    destroy_player(rpg->player);
    destroy_npc(rpg->npcs);
    destroy_mobs(rpg->mobs);
    destroy_assets(rpg->assets);
    sfRenderWindow_destroy(rpg->window);
    sfView_destroy(rpg->view);
    destroy_smith_gui(rpg->smith_gui);
    if (rpg->music != NULL) {
        sfMusic_destroy(rpg->music);
    }
    free(rpg);
    return 0;
}
