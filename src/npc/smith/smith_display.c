/*
** EPITECH PROJECT, 2023
** rpg
** File description:
** smith_display.c
*/

#include "rpg.h"
#include "helper.h"

int should_in_gui_smith_axe(rpg_t *rpg)
{
    return rpg->state == IN_SMITH;
}

int should_in_gui_smith_shield(rpg_t *rpg)
{
    return rpg->state == IN_SMITH;
}
