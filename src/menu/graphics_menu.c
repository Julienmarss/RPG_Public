/*
** EPITECH PROJECT, 2023
** B-MUL-200-LIL-2-1-myrpg-martin.delebecque
** File description:
** graphics_menu.c
*/

#include "../../include/rpg.h"
#include "../../include/helper.h"

static void on_resolution_change_30(rpg_t *rpg)
{
    if (rpg && rpg->window)
    sfRenderWindow_setFramerateLimit(rpg->window, 30);
    printf("Resolution changed to 30 fps\n");
}

static void on_resolution_change_60(rpg_t *rpg)
{
    if (rpg && rpg->window)
    sfRenderWindow_setFramerateLimit(rpg->window, 60);
    printf("Resolution changed to 60 fps\n");
}

void on_back_to_settings(rpg_t *rpg)
{
    rpg->state = SETTINGS;
    display_settings_menu(rpg);
}

int should_display_in_graphics(rpg_t *rpg)
{
    return rpg->state == GRAPHICS;
}

void init_graphics_boutton(rpg_t *rpg, sfVector2f pos,
    const char *image_path, void (*callback)(rpg_t *))
{
    asset_t *button = add_asset(rpg,
        (char *)image_path, should_display_in_graphics, callback);
    sfVector2u size = sfTexture_getSize(button->texture);

    sfSprite_setScale(button->sprite, (sfVector2f){0.5, 0.5});
    size.x *= 0.5;
    size.y *= 0.5;
    set_asset_pos(button, pos, size);
}

void draw_button(rpg_t *rpg, sfSprite* graphicsBackground)
{
    sfVector2f pos = get_window_center(rpg->window);

    pos.y -= 200;
    pos.x -= 175;
    init_graphics_boutton(rpg, pos,
        "resources/images/30_fps.png", on_resolution_change_30);
    pos.y += 125;
    init_graphics_boutton(rpg, pos,
        "resources/images/60_fps.png", on_resolution_change_60);
    pos.y += 125;
    init_graphics_boutton(rpg, pos,
        "resources/images/back.png", on_back_to_settings);
    rpg->graphicsBackground = graphicsBackground;
}

void init_graphics_settings(rpg_t *rpg)
{
    sfTexture* graphicsTexture = load_texture("resources/images/bg_set.png");
    sfSprite* graphicsBackground;
    sfVector2u textureSize;
    sfVector2u windowSize;
    float scaleX;
    float scaleY;

    if (!graphicsTexture) {
        printf("Error loading graphics settings texture.\n");
        return;
    }
    graphicsBackground = sfSprite_create();
    sfSprite_setTexture(graphicsBackground, graphicsTexture, sfTrue);
    textureSize = sfTexture_getSize(graphicsTexture);
    windowSize = get_window_size(rpg->window);
    scaleX = (float)windowSize.x / textureSize.x;
    scaleY = (float)windowSize.y / textureSize.y;
    sfSprite_setScale(graphicsBackground, (sfVector2f){scaleX, scaleY});
    draw_button(rpg, graphicsBackground);
}
