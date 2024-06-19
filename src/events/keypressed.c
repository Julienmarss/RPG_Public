/*
** EPITECH PROJECT, 2023
** rpg
** File description:
** keypressed.c
*/
#include "rpg.h"

void keypressed(rpg_t *rpg, sfEvent event)
{
    int code = event.key.code;

    if (code == sfKeyEscape)
        back(rpg);
    if (code == sfKeyZ || code == sfKeyUp)
        move_player(rpg, 0, -1);
    if (code == sfKeyS || code == sfKeyDown)
        move_player(rpg, 0, 1);
    if (code == sfKeyQ || code == sfKeyLeft)
        move_player(rpg, -1, 0);
    if (code == sfKeyD || code == sfKeyRight)
        move_player(rpg, 1, 0);
    if (code == sfKeyW)
        save_in_file(rpg);
}
