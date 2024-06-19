/*
** EPITECH PROJECT, 2023
** rpg
** File description:
** scoreboard_position.c
*/
#include "rpg.h"
#include "helper.h"

void change_scoreboard_position(rpg_t *rpg)
{
    sfVector2f pos = get_top_position_view(rpg->view);

    if (rpg->scoreboard == NULL)
        return;
    pos.x += 70;
    pos.y += 140;
    sfRectangleShape_setPosition(rpg->scoreboard->shape, pos);
    pos.y += 10;
    sfText_setPosition(rpg->scoreboard->text, pos);
}
