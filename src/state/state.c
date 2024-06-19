/*
** EPITECH PROJECT, 2023
** rpg
** File description:
** state.c
*/
#include "rpg.h"

int set_state(rpg_t *rpg, int state)
{
    rpg->oldstate = rpg->state;
    rpg->state = state;
    return state;
}
