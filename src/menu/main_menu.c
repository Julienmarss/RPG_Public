/*
** EPITECH PROJECT, 2023
** B-MUL-200-LIL-2-1-myrpg-martin.delebecque
** File description:
** main_menu.c
*/

#include "../../include/rpg.h"
#include "../../include/helper.h"

void on_start_game(rpg_t *rpg)
{
    set_state(rpg, PLAYING);
    back_player(rpg);
    change_sfview(rpg, rpg->player->pos);
}

void on_save_game(rpg_t *rpg)
{
    rpg->state = SAVE_MENU;
    init_save_menu(rpg);
}

void on_open_settings(rpg_t *rpg)
{
    rpg->state = SETTINGS;
    init_settings_menu(rpg);
}

void init_menu_button(rpg_t *rpg, sfVector2f pos,
    char *image_path, void (*callback)(rpg_t *))
{
    char *path = image_path;
    asset_t *asset;
    sfVector2u size;

    asset = add_asset(rpg, path, &should_when_waiting, callback);
    sfSprite_setScale(asset->sprite, (sfVector2f){0.5, 0.5});
    size = sfTexture_getSize(asset->texture);
    pos.x -= size.x / 4;
    pos.y -= size.y / 4;
    size.x /= 2;
    size.y /= 2;
    set_asset_pos(asset, pos, size);
}

void init_main_menu(rpg_t *rpg)
{
    sfTexture* menuTexture = load_texture("resources/images/menu_bg.png");
    sfSprite* menuBackground = load_sprite(menuTexture);
    sfVector2u texSize = sfTexture_getSize(menuTexture);
    sfVector2u winSize = get_window_size(rpg->window);
    float scaleX = (float)winSize.x / texSize.x;
    float scaleY = (float)winSize.y / texSize.y;
    sfVector2f pos;

    sfSprite_setScale(menuBackground, (sfVector2f){scaleX, scaleY});
    sfSprite_setPosition(menuBackground, (sfVector2f){0, 0});
    pos = get_window_center(rpg->window);
    pos.y -= 50;
    init_menu_button(rpg, pos, "resources/images/play.png", on_start_game);
    pos.y += 100;
    init_menu_button(rpg, pos, "resources/images/save.png", on_save_game);
    pos.y += 100;
    init_menu_button(rpg, pos,
        "resources/images/settings.png", on_open_settings);
    init_close(rpg);
    rpg->menuBackground = menuBackground;
}
