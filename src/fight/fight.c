/*
** EPITECH PROJECT, 2023
** rpg
** File description:
** fight.c
*/
#include "rpg.h"
#include "helper.h"
#include <time.h>
#include <string.h>
#include <stdlib.h>

static int is_clicked_on_mob(rpg_t *rpg, sfVector2i mouse)
{
    mob_t *mob = rpg->fight->mob;
    sfFloatRect bounds = sfRectangleShape_getGlobalBounds(mob->shape);

    if (sfFloatRect_contains(&bounds, mouse.x, mouse.y))
        return 1;
    return 0;
}

static void finish_fight(rpg_t *rpg, int gift)
{
    char text[40];
    int r = random_nbr(1, 10);

    if (gift == 1) {
        add_xp(rpg->player, r);
        sprintf(text, "You won the fight and got %d xp", r);
        rpg->fight->mob->killed = 1;
    } else {
        strcpy(text, "You lost the fight");
    }
    move_player3(rpg, 10, 0);
    set_state(rpg, PLAYING);
    back_player(rpg);
    destroy_fight(rpg->fight);
    rpg->scoreboard = init_scoreboard(text, sfWhite, 1);
    change_scoreboard_position(rpg);
    return;
}

void fight(rpg_t *rpg, sfVector2i mouse)
{
    player_t *player = rpg->player;
    mob_t *mob = rpg->fight->mob;
    int r = random_nbr(player->min_attack, player->max_attack);

    if (is_clicked_on_mob(rpg, mouse) == 0 || rpg->state != IN_FIGHT)
        return;
    set_lifebar_percent(rpg, mob->hp - r, 0, mob->hp_max);
    if (mob->hp <= 0) {
        finish_fight(rpg, 1);
        return;
    }
    r = random_nbr(player->min_defense, player->max_defense);
    set_lifebar_percent(rpg, player->hp - r, 1, 100);
    if (player->hp <= 0) {
        finish_fight(rpg, 0);
        return;
    }
}

void display_fight(rpg_t *rpg)
{
    sfRenderWindow_clear(rpg->window, sfBlack);
    sfRenderWindow_drawSprite(rpg->window, rpg->fight->background, NULL);
    sfRenderWindow_drawSprite(rpg->window, rpg->fight->mob->sprite, NULL);
    sfRenderWindow_drawSprite(rpg->window, rpg->fight->sign, NULL);
    render_shape(rpg->window, rpg->fight->lifebar_mob);
    render_shape(rpg->window, rpg->fight->healthbar_mob);
    sfRenderWindow_drawText(rpg->window, rpg->fight->mob->text, NULL);
    sfRenderWindow_drawText(rpg->window, rpg->fight->textlife_mob, NULL);
    sfRenderWindow_drawSprite(rpg->window, rpg->fight->player_sprite, NULL);
    display_player(rpg);
}
