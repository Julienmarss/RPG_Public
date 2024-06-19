/*
** EPITECH PROJECT, 2023
** rpg
** File description:
** resize.c
*/
#include "rpg.h"

int resize(sfRenderWindow *window, sfEvent event, rpg_t *rpg)
{
    sfSizeEvent size = event.size;
    sfFloatRect visibleArea = {0, 0, size.width, size.height};

    if (rpg->view)
        sfView_destroy(rpg->view);
    rpg->view = sfView_createFromRect(visibleArea);
    sfRenderWindow_setView(window, rpg->view);
    return 0;
}
