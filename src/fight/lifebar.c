/*
** EPITECH PROJECT, 2023
** rpg
** File description:
** lifebar.c
*/

#include "rpg.h"
#include <string.h>
#include "helper.h"

static void create_libar(sfRectangleShape *lifebar,
    sfVector2f size, sfColor color)
{
    sfRectangleShape_setSize(lifebar, size);
    sfRectangleShape_setFillColor(lifebar, color);
}

void create_healthbar(fight_t *fight)
{
    sfVector2f size = {200, 20};

    fight->healthbar_mob = sfRectangleShape_create();
    create_libar(fight->healthbar_mob, size, sfGreen);
}

void create_lifebar(fight_t *fight)
{
    sfVector2f size = {200, 20};

    fight->lifebar_mob = sfRectangleShape_create();
    create_libar(fight->lifebar_mob, size, sfRed);
}

void set_lifebar_percent(rpg_t *rpg, int percent, int player, int max_hp)
{
    sfVector2f size = {200, 20};
    char str[10];

    if (percent >= max_hp)
        percent = max_hp;
    size.x = (size.x * percent) / max_hp;
    if (player == 1)
        sfRectangleShape_setSize(rpg->player->healthbar, size);
    else
        sfRectangleShape_setSize(rpg->fight->healthbar_mob, size);
    if (player == 0){
        rpg->fight->mob->hp = percent;
        sprintf(str, "%d / %d", rpg->fight->mob->hp, rpg->fight->mob->hp_max);
        sfText_setString(rpg->fight->textlife_mob, str);
    } else {
        sprintf(str, "%d / %d", percent, 100);
        rpg->player->hp = percent;
        sfText_setString(rpg->player->textlife, str);
    }
}
