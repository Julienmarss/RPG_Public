/*
** EPITECH PROJECT, 2023
** rpg
** File description:
** smith_purchase.c
*/
#include "rpg.h"
#include "helper.h"

void smith_purchase_axe(rpg_t *rpg)
{
    player_t *player = rpg->player;
    smith_gui_t *gui = rpg->smith_gui;

    if (player->axe == 1) {
        sfText_setString(gui->axe_text, "Axe already purchased\n");
        sfText_setColor(gui->shield_text, sfRed);
        return;
    }
    if (player->xp >= gui->axe_requirement) {
        player->xp -= gui->axe_requirement;
        player->axe = 1;
        sfText_setString(gui->axe_text, "Axe purchased\n");
        sfText_setColor(gui->axe_text, sfGreen);
        change_player_texture(rpg);
    } else {
        sfText_setString(gui->axe_text, "Not enough xp\n");
        sfText_setColor(gui->axe_text, sfRed);
    }
}

void smith_purchase_shield(rpg_t *rpg)
{
    player_t *player = rpg->player;
    smith_gui_t *gui = rpg->smith_gui;

    if (player->shield == 1) {
        sfText_setString(gui->shield_text, "Shield already purchased\n");
        sfText_setColor(gui->shield_text, sfRed);
        return;
    }
    if (player->xp >= gui->shield_requirement) {
        player->xp -= gui->shield_requirement;
        player->shield = 1;
        sfText_setString(gui->shield_text, "Shield purchased\n");
        sfText_setColor(gui->shield_text, sfGreen);
        change_player_texture(rpg);
    } else {
        sfText_setString(gui->shield_text, "Not enough xp\n");
        sfText_setColor(gui->shield_text, sfRed);
    }
}
