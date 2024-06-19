/*
** EPITECH PROJECT, 2023
** B-MUL-200-LIL-2-1-myrpg-martin.delebecque
** File description:
** volume_menu.c
*/

#include "../../include/rpg.h"
#include "../../include/helper.h"

void on_back_to_settings_sound(rpg_t *rpg)
{
    rpg->state = SETTINGS;
    display_settings_menu(rpg);
}

static void on_on_sound(rpg_t *rpg)
{
    if (rpg->music != NULL) {
        sfMusic_setVolume(rpg->music, 100);
    }
}

static void on_off_sound(rpg_t *rpg)
{
    if (rpg->music != NULL) {
        sfMusic_setVolume(rpg->music, 0);
    }
}

int should_display_in_volume(rpg_t *rpg)
{
    return rpg->state == VOLUME;
}

void init_volume_button(rpg_t *rpg,
    boutton_info_t button_info, sfVector2f base_pos)
{
    asset_t *button = add_asset(rpg, button_info.image_path,
        should_display_in_volume, button_info.callback);
    sfVector2u size;
    sfVector2f pos = {base_pos.x + button_info.position_offset.x,
        base_pos.y + button_info.position_offset.y};

    button->hover_texture = load_texture(button_info.hover_image_path);
    size = sfTexture_getSize(button->texture);
    sfSprite_setScale(button->sprite, (sfVector2f){0.5, 0.5});
    size.x *= 0.5;
    size.y *= 0.5;
    set_asset_pos(button, pos, size);
}

void draw_volume_buttons(rpg_t *rpg, sfSprite* graphicsBackground)
{
    sfVector2f base_pos = get_window_center(rpg->window);
    boutton_info_t buttons[] = {
        {"resources/images/on.png", "resources/images/on_hover.png",
            on_on_sound, {0, 0}},
        {"resources/images/off.png", "resources/images/off_over.png",
            on_off_sound, {0, 125}},
        {"resources/images/back.png", "resources/images/back_over.png",
            on_back_to_settings_sound, {0, 250}},
    };

    base_pos.y -= 200;
    base_pos.x -= 175;
    for (int i = 0; i < 3; ++i) {
        init_volume_button(rpg, buttons[i], base_pos);
    }
    rpg->graphicsBackground = graphicsBackground;
}

void init_volume_settings(rpg_t *rpg)
{
    sfTexture* volumeTexture = load_texture("resources/images/bg_set.png");
    sfSprite* volumeBackground;
    sfVector2u textureSize;
    sfVector2u windowSize;
    float scaleX;
    float scaleY;

    volumeBackground = sfSprite_create();
    sfSprite_setTexture(volumeBackground, volumeTexture, sfTrue);
    textureSize = sfTexture_getSize(volumeTexture);
    windowSize = get_window_size(rpg->window);
    scaleX = (float)windowSize.x / textureSize.x;
    scaleY = (float)windowSize.y / textureSize.y;
    sfSprite_setScale(volumeBackground, (sfVector2f){scaleX, scaleY});
    draw_volume_buttons(rpg, volumeBackground);
}
