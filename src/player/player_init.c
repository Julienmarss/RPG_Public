/*
** EPITECH PROJECT, 2023
** rpg
** File description:
** player_init.c
*/

#include "rpg.h"
#include "helper.h"
#include <string.h>

static void init_tag(player_t *player, rpg_t *rpg, char *username)
{
    sfVector2f pos = get_top_position_view(rpg->view);

    player->font = sfFont_createFromFile("resources/fonts/font.ttf");
    player->text = sfText_create();
    sfText_setString(player->text, username);
    sfText_setCharacterSize(player->text, 20);
    sfText_setFont(player->text, player->font);
    sfText_setColor(player->text, sfWhite);
    sfText_setPosition(player->text, (sfVector2f){pos.x + 50, pos.y + 30});
    player->name = username;
}

static void init_hitbox(player_t *player)
{
    sfVector2f pos = player->pos;

    player->shape = sfRectangleShape_create();
    sfRectangleShape_setOutlineColor(player->shape, sfGreen);
    sfRectangleShape_setOutlineThickness(player->shape, 2);
    sfRectangleShape_setFillColor(player->shape, sfTransparent);
    sfRectangleShape_setSize(player->shape, (sfVector2f){50, 50});
    sfRectangleShape_setOrigin(player->shape, (sfVector2f){0, 0});
    sfRectangleShape_setPosition(player->shape, pos);
    player->direction = (sfVector2f){0, 0};
}

static void init_healthbar(player_t *player)
{
    sfVector2f size = {200, 20};
    sfVector2f textPos = {player->pos.x, player->pos.y - 60};

    sfRectangleShape_setSize(player->healthbar, size);
    sfRectangleShape_setFillColor(player->healthbar, sfGreen);
    sfRectangleShape_setSize(player->lifebar, size);
    sfRectangleShape_setFillColor(player->lifebar, sfRed);
    player->text_hidden = sfText_create();
    sfText_setString(player->text_hidden, player->name);
    sfText_setFont(player->text_hidden, player->font);
    sfText_setCharacterSize(player->text_hidden, 20);
    sfText_setColor(player->text_hidden, sfWhite);
    sfText_setPosition(player->text_hidden, textPos);
    player->hidden = 0;
    player->in_quest = 0;
}

static void init_sign(player_t *player)
{
    sfTexture *texture = load_texture("resources/images/sign.png");
    sfSprite *sprite = load_sprite(texture);

    player->sign = sprite;
    player->sign_texture = texture;
    player->healthbar = sfRectangleShape_create();
    player->lifebar = sfRectangleShape_create();
    init_healthbar(player);
    sfSprite_setScale(sprite, (sfVector2f){0.7, 0.7});
    player->center = (sfVector2f){0, 0};
    player->rect = set_rect(player->sprite, 65, 65);
    sfSprite_setTextureRect(player->sprite, player->rect);
    player->textlife = sfText_create();
    sfText_setString(player->textlife, "100 / 100");
    sfText_setFont(player->textlife, player->font);
    sfText_setCharacterSize(player->textlife, 20);
    sfText_setColor(player->textlife, sfWhite);
}

static void init_xp(player_t *player)
{
    sfTexture *xp_texture = load_texture("resources/images/xp.png");
    sfSprite *xp_sprite = sfSprite_create();
    sfText *text = sfText_create();
    char str[10];

    sfSprite_setTexture(xp_sprite, xp_texture, sfTrue);
    player->xp_sprite = xp_sprite;
    player->xp_texture = xp_texture;
    sfSprite_setPosition(xp_sprite, (sfVector2f){0, 0});
    sfSprite_setScale(xp_sprite, (sfVector2f){0.2, 0.2});
    sprintf(str, "%d", player->xp);
    sfText_setString(text, str);
    sfText_setFont(text, player->font);
    sfText_setCharacterSize(text, 20);
    sfText_setColor(text, sfWhite);
    player->xp_text = text;
}

void init_player_pos(player_t *player)
{
    player->pos.x = DEFAULT_PLAYER_POS_X;
    player->pos.y = DEFAULT_PLAYER_POS_Y;
    player->speed = DEFAULT_PLAYER_SPEED;
    player->hp = DEFAULT_PLAYER_HP;
    player->hp_max = DEFAULT_PLAYER_HP_MAX;
    player->xp = 0;
    player->max_attack = 10;
    player->min_attack = 5;
    player->max_defense = 5;
    player->min_defense = 1;
    player->skin = CLASSIC;
    player->axe = 0;
    player->shield = 0;
}

void init_player(rpg_t *rpg, char *username)
{
    player_t *player = malloc(sizeof(player_t));
    sfTexture *texture = load_texture("resources/images/player/classic.png");
    sfVector2f pos = {0, 0};

    player->sprite = load_sprite(texture);
    player->texture = texture;
    init_player_pos(player);
    pos = player->pos;
    sfSprite_setPosition(player->sprite, pos);
    init_tag(player, rpg, username);
    init_hitbox(player);
    init_sign(player);
    init_xp(player);
    rpg->player = player;
    change_player_texture(rpg);
}
