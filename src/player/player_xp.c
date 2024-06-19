/*
** EPITECH PROJECT, 2023
** rpg
** File description:
** player_xp.c
*/
#include "rpg.h"

static void update_xp(player_t *player)
{
    char str[10];

    sprintf(str, "%d", player->xp);
    sfText_setString(player->xp_text, str);
}

void add_xp(player_t *player, int amount)
{
    player->xp += amount;
    if (player->xp < 0)
        player->xp = 0;
    if (player->xp > 9999)
        player->xp = 9999;
    update_xp(player);
}

void remove_xp(player_t *player, int amount)
{
    player->xp -= amount;
    if (player->xp < 0)
        player->xp = 0;
    update_xp(player);
}

void set_xp(player_t *player, int amount)
{
    player->xp = amount;
    if (player->xp < 0)
        player->xp = 0;
    update_xp(player);
}

void xp_click(rpg_t *rpg)
{
    (void)rpg;
}
