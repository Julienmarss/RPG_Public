/*
** EPITECH PROJECT, 2023
** B-MUL-200-LIL-2-1-myrpg-martin.delebecque
** File description:
** display_menu.c
*/

#include "rpg.h"
#include "helper.h"

void display_volume_settings(rpg_t *rpg)
{
    sfRenderWindow_clear(rpg->window, sfBlack);
    sfRenderWindow_drawSprite(rpg->window, rpg->graphicsBackground, NULL);
    display_assets(rpg);
    sfRenderWindow_display(rpg->window);
}

static void display_in_quest(rpg_t *rpg)
{
    sfRenderWindow_setView(rpg->window, rpg->view);
    sfRenderWindow_drawSprite(rpg->window, rpg->map->sprite, NULL);
    display_assets(rpg);
    display_npcs(rpg);
}

static void display_settings(rpg_t *rpg)
{
    if (!rpg->settingsBackground) {
        return;
    }
    sfRenderWindow_drawSprite(rpg->window, rpg->settingsBackground, NULL);
    display_assets(rpg);
}

static void display_save_menu(rpg_t *rpg)
{
    if (!rpg->saveBackground) {
        return;
    }
    sfRenderWindow_drawSprite(rpg->window, rpg->saveBackground, NULL);
    display_assets(rpg);
}

static void display_waiting(rpg_t *rpg)
{
    sfRenderWindow_drawSprite(rpg->window, rpg->menuBackground, NULL);
    display_assets(rpg);
}

static void display_autre(rpg_t *rpg)
{
    if (rpg->state == IN_FIGHT)
        display_fight(rpg);
    if (rpg->scoreboard && rpg->state != WAITING)
        display_scoreboard(rpg);
    if (rpg->state == SAVE_MENU){
        display_save_menu(rpg);
    }
    if (rpg->state == IN_SMITH)
        display_smith(rpg);
    display_assets(rpg);
    display_npcs(rpg);
}

static void display_switch(int state, rpg_t *rpg)
{
    switch (state) {
        case WAITING:
            display_waiting(rpg);
            break;
        case PLAYING:
            display_playing(rpg);
            break;
        case SETTINGS:
            display_settings(rpg);
            break;
        case GRAPHICS:
            display_graphics_settings(rpg);
            break;
        case VOLUME:
            display_volume_settings(rpg);
            break;
        case IN_QUEST:
            display_in_quest(rpg);
        break;
    }
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

void draw_assets(rpg_t *rpg)
{
    asset_t *tmp = rpg->assets;

    while (tmp) {
        if (tmp->should_display(rpg)) {
            display_asset(rpg, tmp);
        }
        tmp = tmp->next;
    }
}

void display(rpg_t *rpg)
{
    sfRenderWindow_clear(rpg->window, sfBlack);
    display_switch(rpg->state, rpg);
    display_autre(rpg);
    if (rpg->state == PLAYING || rpg->state == IN_QUEST ||
        rpg->state == IN_SMITH)
        display_player(rpg);
    sfRenderWindow_display(rpg->window);
}
