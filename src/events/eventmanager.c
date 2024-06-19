/*
** EPITECH PROJECT, 2023
** rpg
** File description:
** eventmanager.c
*/

#include "rpg.h"

int eventmanager(rpg_t *rpg)
{
    sfEvent event;

    while (sfRenderWindow_pollEvent(rpg->window, &event)) {
        if (event.type == sfEvtClosed)
            sfRenderWindow_close(rpg->window);
        if (event.type == sfEvtKeyPressed) {
            keypressed(rpg, event);
            keypressed_for_music(rpg, event);
        }
        if (event.type == sfEvtMouseButtonPressed)
            click(rpg, event);
        if (event.type == sfEvtResized)
            resize(rpg->window, event, rpg);
        if (event.type == sfEvtMouseMoved) {
            move(rpg, event);
            handle_hover(rpg);
        }
    }
    return 0;
}
