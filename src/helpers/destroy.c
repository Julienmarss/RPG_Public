/*
** EPITECH PROJECT, 2023
** rpg
** File description:
** File to destroy textures, sprites, fonts and music
*/
#include "helper.h"

void destroy_texture(sfTexture *texture)
{
    sfTexture_destroy(texture);
}

void destroy_sprite(sfSprite *sprite)
{
    sfSprite_destroy(sprite);
}

void destroy_font(sfFont *font)
{
    sfFont_destroy(font);
}

void destroy_music(sfMusic *music)
{
    sfMusic_destroy(music);
}
