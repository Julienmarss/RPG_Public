/*
** EPITECH PROJECT, 2023
** rpg
** File description:
** rpg.c
*/

#include "rpg.h"

char *random_playername(void)
{
    char *names[] = {"Harald", "Gunnar", "Bjorn", "Ragnar",
        "Ivar", "Sigurd", "Erik", "Olaf", "Leif", "Hakon"};

    return names[random_nbr(0, 9)];
}

rpg_t *make_game(void)
{
    rpg_t *rpg = malloc(sizeof(rpg_t));

    rpg->window = create_window();
    rpg->clock = sfClock_create();
    rpg->view = sfView_create();
    rpg->state = WAITING;
    rpg->oldstate = WAITING;
    rpg->clock_player = sfClock_create();
    start_music(rpg);
    rpg->mobs = NULL;
    rpg->demo_timer = 0;
    init_map(rpg);
    init_main_menu(rpg);
    init_player(rpg, random_playername());
    return rpg;
}

int back(rpg_t *rpg)
{
    if (rpg->state == IN_SMITH || rpg->oldstate == IN_SMITH){
        move_player3(rpg, 10, 10);
        back_player(rpg);
        set_state(rpg, PLAYING);
        change_sfview(rpg, rpg->player->pos);
        return WAITING;
    }
    set_state(rpg, WAITING);
    sfView_setCenter(rpg->view, (sfVector2f){1920 / 2, 510});
    sfRenderWindow_setView(rpg->window, rpg->view);
    change_close_position(rpg);
    return WAITING;
}
