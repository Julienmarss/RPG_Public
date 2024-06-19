/*
** EPITECH PROJECT, 2023
** B-MUL-200-LIL-2-1-myrpg-martin.delebecque
** File description:
** display_menu.c
*/

#include "../../include/rpg.h"
#include "../../include/helper.h"

void display_graphics_settings(rpg_t *rpg)
{
    sfRenderWindow_clear(rpg->window, sfBlack);
    sfRenderWindow_drawSprite(rpg->window, rpg->graphicsBackground, NULL);
    display_assets(rpg);
    sfRenderWindow_display(rpg->window);
}

void display_new_menu(rpg_t *rpg)
{
    sfRenderWindow_clear(rpg->window, sfBlack);
    sfRenderWindow_drawSprite(rpg->window, rpg->menuBackground, NULL);
    display_assets(rpg);
    sfRenderWindow_display(rpg->window);
}

void display_settings_menu(rpg_t *rpg)
{
    sfRenderWindow_clear(rpg->window, sfBlack);
    sfRenderWindow_drawSprite(rpg->window, rpg->settingsBackground, NULL);
    display_assets(rpg);
    sfRenderWindow_display(rpg->window);
}
