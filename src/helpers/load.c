/*
** EPITECH PROJECT, 2023
** rpg
** File description:
** File to load textures, sprites, fonts and music
*/

#include "helper.h"

sfTexture* load_texture(const char *filename)
{
    sfTexture* texture;

    texture = sfTexture_createFromFile(filename, NULL);
    return texture;
}

sfSprite* load_sprite(sfTexture *texture)
{
    sfSprite *sprite;

    sprite = sfSprite_create();
    sfSprite_setTexture(sprite, texture, sfTrue);
    return sprite;
}

sfFont* load_font(const char *filename)
{
    sfFont* font;

    font = sfFont_createFromFile(filename);
    return font;
}

sfMusic* load_music(const char *filename)
{
    sfMusic* music;

    music = sfMusic_createFromFile(filename);
    return music;
}

sfSprite* set_position(sfSprite *sprite, int x, int y)
{
    sfVector2f scale = {x, y};

    sfSprite_setPosition(sprite, scale);
    return sprite;
}
