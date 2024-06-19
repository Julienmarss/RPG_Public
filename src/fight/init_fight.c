/*
** EPITECH PROJECT, 2023
** rpg
** File description:
** init_fight.c
*/

#include "rpg.h"
#include "helper.h"

static void init_text(fight_t *fight, rpg_t *rpg)
{
    sfText *text = sfText_create();
    sfVector2f pos = {0, 0};
    char str[40];

    sfText_setFont(text, rpg->player->font);
    sfText_setCharacterSize(text, 20);
    sfText_setColor(text, sfWhite);
    sfText_setPosition(text, pos);
    sprintf(str, "%d / %d", fight->mob->hp, fight->mob->hp_max);
    sfText_setString(text, str);
    fight->textlife_mob = text;
}

static void create_bars(fight_t *fight, sfVector2f pos)
{
    sfRectangleShape_setPosition(fight->healthbar_mob, pos);
    sfRectangleShape_setPosition(fight->lifebar_mob, pos);
}

static void create_sign(fight_t *fight, rpg_t *rpg)
{
    char *filename = "resources/images/sign.png";
    sfVector2f pos = get_right_position_view(rpg->view);

    fight->sign = sfSprite_create();
    fight->sign_texture = sfTexture_createFromFile(filename, NULL);
    init_text(fight, rpg);
    pos.x -= 350;
    pos.y += 25;
    sfSprite_setTexture(fight->sign, fight->sign_texture, sfTrue);
    sfSprite_setScale(fight->sign, (sfVector2f){0.7, 0.7});
    sfSprite_setPosition(fight->sign, pos);
    pos.x += 45;
    pos.y += 40;
    sfText_setPosition(fight->mob->text, pos);
    pos.x += 150;
    sfText_setPosition(fight->textlife_mob, pos);
    pos.x -= 150;
    pos.y += 40;
    create_bars(fight, pos);
}

void init_fight(mob_t *mob, rpg_t *rpg, char *filename)
{
    fight_t *fight = malloc(sizeof(fight_t));
    sfTexture *texture = sfTexture_createFromFile(filename, NULL);
    sfSprite *sprite = sfSprite_create();

    sfSprite_setTexture(sprite, texture, sfTrue);
    sfSprite_setScale(sprite, (sfVector2f){1.1, 1.01});
    fight->mob = mob;
    fight->background = sprite;
    fight->background_texture = texture;
    create_lifebar(fight);
    create_healthbar(fight);
    create_sign(fight, rpg);
    rpg->fight = fight;
    set_lifebar_percent(rpg, mob->hp_max, 0, mob->hp_max);
}

static void set_player_fight(rpg_t *rpg)
{
    sfVector2f pos = get_window_center(rpg->window);
    char *filename = "resources/images/player/player_fight.png";

    pos.x = 600;
    pos.y = 500;
    rpg->fight->player_texture = load_texture(filename);
    rpg->fight->player_sprite = load_sprite(rpg->fight->player_texture);
    sfSprite_setPosition(rpg->fight->player_sprite, pos);
    sfSprite_setScale(rpg->fight->player_sprite, (sfVector2f){0.7, 0.7});
    sfText_setColor(rpg->player->text, sfWhite);
    if (rpg->player->axe) {
        rpg->player->max_attack += 10;
        rpg->player->min_attack += 5;
    }
    if (rpg->player->shield) {
        rpg->player->max_defense -= 3;
    }
}

void start_fight(rpg_t *rpg, mob_t *mob, char *filename)
{
    sfView_setCenter(rpg->view, (sfVector2f){1920 / 2, 510});
    sfRenderWindow_setView(rpg->window, rpg->view);
    change_close_position(rpg);
    change_sign_position(rpg);
    init_fight(mob, rpg, filename);
    set_player_fight(rpg);
    set_state(rpg, IN_FIGHT);
    sfText_setString(mob->text, mob->name);
}

void destroy_fight(fight_t *fight)
{
    sfSprite_destroy(fight->background);
    sfTexture_destroy(fight->background_texture);
    sfSprite_destroy(fight->sign);
    sfTexture_destroy(fight->sign_texture);
    sfRectangleShape_destroy(fight->lifebar_mob);
    sfRectangleShape_destroy(fight->healthbar_mob);
    sfText_destroy(fight->textlife_mob);
    free(fight);
}
