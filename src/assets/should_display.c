/*
** EPITECH PROJECT, 2023
** rpg
** File description:
** should.c
*/
#include "rpg.h"

int should_always_display(rpg_t *rpg)
{
    (void)rpg;
    return 1;
}

int should_when_playing(rpg_t *rpg)
{
    return rpg->state == PLAYING || rpg->state == IN_QUEST;
}

int should_when_waiting(rpg_t *rpg)
{
    return rpg->state == WAITING;
}

int should_when_not_waiting(rpg_t *rpg)
{
    return rpg->state != WAITING;
}

int should_in_gui_smith(rpg_t *rpg)
{
    if (rpg->state == IN_FIGHT){
        if (rpg->player->axe == 1)
            return 1;
    }
    return rpg->state == IN_SMITH;
}
