/*
** EPITECH PROJECT, 2023
** rpg
** File description:
** apple_npc.c
*/
#include "rpg.h"
#include <string.h>
#include <stdlib.h>

#include <stdio.h>

static int get_apple_count(rpg_t *rpg)
{
    npc_t *tmp = rpg->npcs;
    int count = 0;

    while (tmp) {
        if (tmp->oninteract == &oninteract_npc_apple)
            count = atoi(tmp->meta);
        tmp = tmp->next;
    }
    return count;
}

static void remove_apple_npc(rpg_t *rpg)
{
    asset_t *apple = get_asset_from_oninteract(rpg, &oninteract_apple);

    if (apple == NULL)
        return;
    remove_asset(rpg, apple);
}

static void finish_apple_npc(rpg_t *rpg)
{
    char text[50];
    int r = random_nbr(5, 10);

    sprintf(text, "You have finished quest and got %d xp", r);
    rpg->scoreboard = init_scoreboard(text, sfWhite, 1);
    remove_apple_npc(rpg);
    add_xp(rpg->player, r);
}

void oninteract_npc_apple(rpg_t *rpg, npc_t *npc)
{
    char *text = "You must have 10 apple (0/10)";

    if (rpg->player->in_quest == 1)
        return;
    if (rpg->player->hp == rpg->player->hp_max){
        text = "You have full hp. You must lose life to start this quest";
        rpg->scoreboard = init_scoreboard(text, sfRed, 1);
        change_scoreboard_position(rpg);
        return;
    }
    rpg->scoreboard = init_scoreboard(text, sfWhite, -1);
    rpg->player->in_quest = 1;
    strcpy(npc->meta, "0");
    set_random_apple(rpg, npc, NULL);
}

void init_apple_npc(rpg_t *rpg)
{
    asset_t *npc_apple = add_asset(rpg, "resources/images/pnj1.png",
        &should_when_playing, NULL);
    sfVector2u size;
    sfVector2f pos = {1440, 50};
    npc_t *npc;

    sfSprite_setScale(npc_apple->sprite, (sfVector2f){0.2, 0.2});
    size = sfTexture_getSize(npc_apple->texture);
    size.x *= 0.2;
    size.y *= 0.2;
    npc = add_npc(rpg, npc_apple,
        &should_when_playing, &oninteract_npc_apple);
    set_npc_name(npc, "Steve Job", pos);
    set_asset_pos(npc_apple, pos, size);
}

void oninteract_apple(rpg_t *rpg, asset_t *asset)
{
    int count = get_apple_count(rpg);
    npc_t *npc = get_npc_by_oninteract(oninteract_npc_apple, rpg);
    char *text = malloc(sizeof(char) * 50);

    count++;
    destroy_scoreboard(rpg);
    if (count == 10) {
        set_state(rpg, PLAYING);
        finish_apple_npc(rpg);
    } else {
        sprintf(text, "You must have 10 apple (%d/10)", count);
        rpg->scoreboard = init_scoreboard(text, sfWhite, -1);
        strcpy(npc->meta, my_itoa(count));
        rpg->player->in_quest = 1;
        set_random_apple(rpg, npc, asset);
        set_lifebar_percent(rpg, rpg->player->hp + 5, 1, 100);
    }
    change_scoreboard_position(rpg);
    (void)asset;
}

static sfVector2f get_random_pos(rpg_t *rpg)
{
    sfVector2f pos;
    sfImage *image = rpg->map->image_copy;

    while (1) {
        pos.x = random_nbr(200, 1700);
        pos.y = random_nbr(200, 700);
        if (sfImage_getPixel(image, pos.x, pos.y).a == 0)
            break;
    }
    return pos;
}

void set_random_apple(rpg_t *rpg, npc_t *npc, asset_t *asset)
{
    sfVector2f pos = get_random_pos(rpg);
    sfVector2u size;

    (void) npc;
    if (asset == NULL) {
        asset = add_asset(rpg, "resources/images/apple.png",
            &should_when_playing, NULL);
    }
    sfSprite_setScale(asset->sprite, (sfVector2f){0.2, 0.2});
    size = sfTexture_getSize(asset->texture);
    size.x *= 0.2;
    size.y *= 0.2;
    set_asset_pos(asset, pos, size);
    asset->oninteract = &oninteract_apple;
}
