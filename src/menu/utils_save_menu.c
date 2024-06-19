/*
** EPITECH PROJECT, 2023
** B-MUL-200-LIL-2-1-myrpg-martin.delebecque
** File description:
** utils_save_menu.c
*/

#include "../../include/rpg.h"
#include "../../include/helper.h"
#include <dirent.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int should_display_in_save_menu(rpg_t *rpg)
{
    return rpg->state == SAVE_MENU;
}

asset_t *create_button_asset(rpg_t *rpg, sfVector2f pos)
{
    asset_t *button;
    sfVector2u textureSize;
    sfVector2f scaledSize;
    sfVector2u windowSize;
    sfVector2f buttonPos;

    button = add_asset(rpg, "resources/images/button_save.png",
        should_display_in_save_menu, NULL);
    textureSize = sfTexture_getSize(button->texture);
    scaledSize = (sfVector2f){textureSize.x * 0.5f, textureSize.y * 0.5f};
    sfSprite_setScale(button->sprite, (sfVector2f){0.5f, 0.5f});
    windowSize = get_window_size(rpg->window);
    buttonPos = (sfVector2f){(windowSize.x - scaledSize.x) / 2.0f, pos.y};
    set_asset_pos(button, buttonPos, (sfVector2u){0, 0});
    return button;
}

sfText *create_text_asset(const char *save_name, sfFont **font)
{
    sfText *text;

    *font = sfFont_createFromFile("resources/fonts/font.ttf");
    if (!*font) {
        printf("Error loading font\n");
        return NULL;
    }
    text = sfText_create();
    if (!text) {
        printf("Error creating text\n");
        sfFont_destroy(*font);
        return NULL;
    }
    sfText_setString(text, save_name);
    sfText_setFont(text, *font);
    sfText_setCharacterSize(text, 24);
    sfText_setFillColor(text, sfRed);
    return text;
}

void position_text_on_button(sfText *text,
    sfVector2f buttonPos, sfVector2f scaledSize)
{
    sfFloatRect textRect = sfText_getLocalBounds(text);
    sfVector2f textPos = {buttonPos.x + (scaledSize.x / 2.0f) -
        (textRect.width / 2.0f),
        buttonPos.y + (scaledSize.y / 2.0f) - (textRect.height / 2.0f)};

    sfText_setPosition(text, textPos);
}

void init_save_button(rpg_t *rpg, sfVector2f pos,
    const char *save_name, void (*callback)(rpg_t *, const char *))
{
    asset_t *button;
    sfFont *font = NULL;
    sfText *text;
    sfVector2u textureSize;
    sfVector2f scaledSize;
    sfVector2u windowSize;
    sfVector2f buttonPos;

    (void)callback;
    button = create_button_asset(rpg, pos);
    text = create_text_asset(save_name, &font);
    if (!text)
        return;
    textureSize = sfTexture_getSize(button->texture);
    scaledSize = (sfVector2f){textureSize.x * 0.5f, textureSize.y * 0.5f};
    windowSize = get_window_size(rpg->window);
    buttonPos = (sfVector2f){(windowSize.x - scaledSize.x) / 2.0f, pos.y};
    position_text_on_button(text, buttonPos, scaledSize);
    button->text = text;
    button->font = font;
}
