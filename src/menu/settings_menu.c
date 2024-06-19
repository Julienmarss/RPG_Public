/*
** EPITECH PROJECT, 2023
** B-MUL-200-LIL-2-1-myrpg-martin.delebecque
** File description:
** settings_menu.c
*/

#include "../../include/rpg.h"
#include "../../include/helper.h"

int should_display_in_settings(rpg_t *rpg)
{
    return rpg->state == SETTINGS;
}

void init_settings_button(rpg_t *rpg, sfVector2f pos,
    const char *image_path, void (*callback)(rpg_t *))
{
    asset_t *button = add_asset(rpg,
        (char *)image_path, should_display_in_settings, callback);
    sfVector2u size = sfTexture_getSize(button->texture);

    sfSprite_setScale(button->sprite, (sfVector2f){0.5, 0.5});
    size.x *= 0.5;
    size.y *= 0.5;
    set_asset_pos(button, pos, size);
}

void on_back_to_menu(rpg_t *rpg)
{
    rpg->state = WAITING;
    display_settings_menu(rpg);
}

static void on_open_graphics(rpg_t *rpg)
{
    rpg->state = GRAPHICS;
    init_graphics_settings(rpg);
}

static void on_open_volume(rpg_t *rpg)
{
    rpg->state = VOLUME;
    init_volume_settings(rpg);
}

void draw_settings_buttons(rpg_t *rpg, sfSprite* settingsBackground)
{
    sfVector2f pos = get_window_center(rpg->window);

    pos.y -= 175;
    pos.x -= 175;
    init_settings_button(rpg, pos,
        "resources/images/sound_settings.png", on_open_volume);
    pos.y += 100;
    init_settings_button(rpg, pos,
        "resources/images/graph_settings.png", on_open_graphics);
    pos.y += 100;
    init_settings_button(rpg, pos,
        "resources/images/back.png", on_back_to_menu);
    rpg->settingsBackground = settingsBackground;
}

void init_settings_menu(rpg_t *rpg)
{
    sfTexture* settingsTexture = load_texture("resources/images/bg_set.png");
    sfSprite *settingsBackground;
    sfVector2u textureSize;
    sfVector2u windowSize;
    float scaleX;
    float scaleY;

    if (!settingsTexture) {
        printf("Error loading settings background texture.\n");
        return;
    }
    settingsBackground = sfSprite_create();
    sfSprite_setTexture(settingsBackground, settingsTexture, sfTrue);
    textureSize = sfTexture_getSize(settingsTexture);
    windowSize = get_window_size(rpg->window);
    scaleX = (float)windowSize.x / textureSize.x;
    scaleY = (float)windowSize.y / textureSize.y;
    sfSprite_setScale(settingsBackground, (sfVector2f){scaleX, scaleY});
    draw_settings_buttons(rpg, settingsBackground);
}
