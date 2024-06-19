/*
** EPITECH PROJECT, 2023
** rpg
** File description:
** clockmanager.c
*/
#include "rpg.h"
#include "helper.h"


void player_clockmanager(rpg_t *rpg)
{
    sfTime time = sfClock_getElapsedTime(rpg->clock_player);
    float seconds = sfTime_asSeconds(time);

    if (rpg->state != PLAYING)
        return;
    if (seconds >= 0.05f){
        sfClock_restart(rpg->clock_player);
        move_player2(rpg, seconds);
    }
}

void clockmanager(rpg_t *rpg)
{
    sfTime time = sfClock_getElapsedTime(rpg->clock);
    float seconds = sfTime_asSeconds(time);

    if ((time.microseconds / 100) >= 05)
        display(rpg);
    if (seconds >= 5.0f){
        add_second_to_scoreboard(rpg);
        if (rpg->state == PLAYING)
            rpg->demo_timer += 1;
        if (rpg->state == PLAYING)
            set_lifebar_percent(rpg, rpg->player->hp + 1, 1, 100);
        sfClock_restart(rpg->clock);
    }
    player_clockmanager(rpg);
    return;
}
