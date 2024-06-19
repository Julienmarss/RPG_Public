/*
** EPITECH PROJECT, 2023
** B-MUL-200-LIL-2-1-myrpg-martin.delebecque
** File description:
** music.c
*/

#include "rpg.h"

void start_music(rpg_t *rpg)
{
    rpg->music = sfMusic_createFromFile("resources/music.ogg");
    if (rpg->music == NULL) {
        return;
    }
    sfMusic_play(rpg->music);
    sfMusic_setLoop(rpg->music, sfTrue);
}

void stop_music(rpg_t *rpg)
{
    if (rpg->music != NULL) {
        sfMusic_stop(rpg->music);
    }
}

void keypressed_for_music(rpg_t *rpg, sfEvent event)
{
    if (event.key.code == sfKeyM) {
        if (sfMusic_getStatus(rpg->music) == sfPlaying) {
            stop_music(rpg);
        } else {
            start_music(rpg);
        }
    }
}
