/*
** EPITECH PROJECT, 2023
** rpg
** File description:
** npc.c
*/

#include <string.h>
#include "rpg.h"

static int player_has_already_killed_mob(rpg_t *rpg, char *uuid)
{
    mob_t *tmp = rpg->mobs;

    if (uuid == NULL)
        return 0;
    while (tmp != NULL) {
        if (tmp->killed == 1 && strcmp(tmp->uuid, uuid) == 0)
            return 1;
        tmp = tmp->next;
    }
    return 0;
}

static void on_mob_interactsub(rpg_t *rpg)
{
    char *text;

    text = "You have already killed this mob";
    rpg->scoreboard = init_scoreboard(text, sfYellow, 3);
    change_scoreboard_position(rpg);
}

void on_mob_interact(rpg_t *rpg, npc_t *npc)
{
    char *uuid = npc->asset->uuid;
    mob_t *mob;
    char *filename = "resources/images/fight.png";
    char *text;

    if (player_has_already_killed_mob(rpg, uuid) == 1) {
        on_mob_interactsub(rpg);
        return;
    }
    mob = init_mob(rpg, "wolf", uuid);
    if (strcmp(npc->asset->uuid, "resources/images/snake.png") == 0)
        filename = "resources/images/fight_sea.png";
    start_fight(rpg, mob, filename);
    if (strcmp(npc->asset->uuid, "resources/images/snake.png") == 0)
        text = "The sea snake you have captured! Kill him to continue";
    else
        text = "Click on the mob to attack him";
    rpg->scoreboard = init_scoreboard(text, sfYellow, 3);
    change_scoreboard_position(rpg);
}

void init_mob_npc(rpg_t *rpg)
{
    asset_t *asset = add_asset(rpg, "resources/images/wolf.png",
    &should_when_playing, NULL);
    asset_t *asset2 = add_asset(rpg, "resources/images/wolf2.png",
    &should_when_playing, NULL);
    asset_t *asset3 = add_asset(rpg, "resources/images/snake.png",
    &should_when_playing, NULL);
    npc_t *npc;

    npc = add_npc(rpg, asset, &should_when_playing, &on_mob_interact);
    set_npc_pos(npc, (sfVector2f){400, 400}, (sfVector2u){75, 75});
    sfSprite_setScale(npc->asset->sprite, (sfVector2f){0.5, 0.5});
    npc = add_npc(rpg, asset2, &should_when_playing, &on_mob_interact);
    set_npc_pos(npc, (sfVector2f){840, 1575}, (sfVector2u){75, 75});
    sfSprite_setScale(npc->asset->sprite, (sfVector2f){0.5, 0.5});
    npc = add_npc(rpg, asset3, &should_when_playing, &on_mob_interact);
    set_npc_pos(npc, (sfVector2f){1670, 700}, (sfVector2u){75, 75});
    sfSprite_setScale(npc->asset->sprite, (sfVector2f){0.5, 0.5});
}
