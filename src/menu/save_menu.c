/*
** EPITECH PROJECT, 2023
** B-MUL-200-LIL-2-1-myrpg-martin.delebecque
** File description:
** save_menu.c
*/

#include "../../include/rpg.h"
#include "../../include/helper.h"
#include <dirent.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <dirent.h>

static void on_save_click(rpg_t *rpg, asset_t *asset)
{
    const char *string = sfText_getString(asset->text);
    char *save = "saves/";
    char *filename = malloc(strlen(string) + strlen(save) + 1);

    sprintf(filename, "%s%s", save, string);
    load_from_file(rpg, filename);
}

static sfVector2f get_initial_text_position(sfRenderWindow *window)
{
    sfVector2u windowSize = get_window_size(window);
    sfVector2f pos = {windowSize.x / 2, (windowSize.y / 2) - 350};

    return pos;
}

static DIR *open_save_directory(const char *path)
{
    DIR *dir = opendir(path);

    if (!dir) {
        return NULL;
    }
    return dir;
}

sfText *create_save_text(const char *save_name,
    sfFont *font, sfVector2f pos, int index)
{
    sfText *text;
    sfFloatRect textRect;
    sfVector2f textPos;

    if (index >= 10)
        return NULL;
    text = sfText_create();
    if (!text) {
        printf("Error creating text\n");
        return NULL;
    }
    sfText_setString(text, save_name);
    sfText_setFont(text, font);
    sfText_setCharacterSize(text, 24);
    sfText_setFillColor(text, sfWhite);
    textRect = sfText_getLocalBounds(text);
    textPos = (sfVector2f){pos.x - (textRect.width / 2), pos.y + index * 50};
    sfText_setPosition(text, textPos);
    return text;
}

void process_directory_entry(rpg_t *rpg, struct dirent *entry,
    sfVector2f pos, int index)
{
    sfFont *font = load_font("resources/fonts/font.ttf");
    sfText *text = create_save_text(entry->d_name, font, pos, index);
    asset_t *textAsset = NULL;

    if (!text) {
        return;
    }
    textAsset = add_asset(rpg, NULL,
        should_display_in_save_menu, NULL);
    textAsset->text = text;
    textAsset->font = font;
    textAsset->oninteract = &on_save_click;
}

static int is_valid_file(struct dirent *entry)
{
    char *extension;

    if (entry->d_type != DT_REG)
        return 0;
    if (strcmp(entry->d_name, ".") == 0)
        return 0;
    if (strcmp(entry->d_name, "..") == 0)
        return 0;
    extension = strrchr(entry->d_name, '.');
    if (!extension)
        return 0;
    if (strcmp(extension, ".dat") != 0)
        return 0;
    return 1;
}

void draw_save_buttons(rpg_t *rpg, sfSprite* saveBackground)
{
    sfVector2f pos = get_initial_text_position(rpg->window);
    DIR *dir = open_save_directory("saves");
    struct dirent *entry;
    int i = 0;

    if (!dir || dir == NULL) {
        rpg->saveBackground = saveBackground;
        return;
    }
    entry = readdir(dir);
    while (entry != NULL) {
        if (is_valid_file(entry)) {
            process_directory_entry(rpg, entry, pos, i);
            i++;
        }
        entry = readdir(dir);
    }
    closedir(dir);
    rpg->saveBackground = saveBackground;
}

void init_save_menu(rpg_t *rpg)
{
    sfTexture* saveTexture = load_texture("resources/images/bg_save.png");
    sfSprite *saveBackground;
    sfVector2u textureSize;
    sfVector2u windowSize;
    float scaleX;
    float scaleY;

    if (!saveTexture) {
        printf("Error loading save menu background texture.\n");
        return;
    }
    saveBackground = sfSprite_create();
    sfSprite_setTexture(saveBackground, saveTexture, sfTrue);
    textureSize = sfTexture_getSize(saveTexture);
    windowSize = get_window_size(rpg->window);
    scaleX = (float)windowSize.x / textureSize.x;
    scaleY = (float)windowSize.y / textureSize.y;
    sfSprite_setScale(saveBackground, (sfVector2f){scaleX, scaleY});
    draw_save_buttons(rpg, saveBackground);
}
