/*
** EPITECH PROJECT, 2023
** rpg
** File description:
** player_move.c
*/
#include "rpg.h"
#include "helper.h"

static void change_lifebar_position(rpg_t *rpg)
{
    sfVector2f pos = get_top_position_view(rpg->view);

    pos.x += 70;
    pos.y += 100;
    sfRectangleShape_setPosition(rpg->player->lifebar, pos);
    sfRectangleShape_setPosition(rpg->player->healthbar, pos);
}

void change_sign_position(rpg_t *rpg)
{
    sfSprite *sign = rpg->player->sign;
    sfVector2f pos = get_top_position_view(rpg->view);

    sfSprite_setPosition(sign, (sfVector2f){pos.x + 30, pos.y + 20});
    pos.x += 70;
    pos.y += 60;
    sfText_setPosition(rpg->player->text, pos);
    pos.x += 90;
    sfText_setPosition(rpg->player->textlife, pos);
    pos.x += 120;
    pos.y -= 20;
    sfSprite_setPosition(rpg->player->xp_sprite, pos);
    pos.x += 20;
    pos.y += 50;
    sfText_setPosition(rpg->player->xp_text, pos);
    change_lifebar_position(rpg);
}

void change_sfview(rpg_t *rpg, sfVector2f pos)
{
    if (pos.y <= 510)
        pos.y = 510;
    if (pos.x >= 1770)
        pos.x = 1770;
    if (pos.x <= 965)
        pos.x = 965;
    if (pos.y >= 1525)
        pos.y = 1525;
    if (rpg->state == IN_FIGHT || rpg->state == IN_SMITH)
        return;
    sfView_setCenter(rpg->view, pos);
    change_close_position(rpg);
    change_sign_position(rpg);
    change_scoreboard_position(rpg);
    change_demo_position(rpg);
    rpg->player->center = pos;
}

static void trigger_player_moved(rpg_t *rpg)
{
    trigger_npc(rpg);
    trigger_assets(rpg);
}

void back_player(rpg_t *rpg)
{
    sfVector2f pos = get_top_position_view(rpg->view);

    pos.x += 40;
    pos.y += 40;
    sfSprite_setPosition(rpg->player->sprite, rpg->player->pos);
    sfText_setPosition(rpg->player->text, pos);
    sfRectangleShape_setPosition(rpg->player->shape, rpg->player->pos);
    sfRectangleShape_setSize(rpg->player->shape, (sfVector2f){50, 50});
    sfText_setString(rpg->player->text, rpg->player->name);
    sfText_setCharacterSize(rpg->player->text, 20);
    sfSprite_setScale(rpg->player->sprite, (sfVector2f){1, 1});
    sfText_setColor(rpg->player->text, sfWhite);
    change_sfview(rpg, rpg->player->pos);
}

static void update_player_position(rpg_t *rpg, sfVector2f newPos)
{
    player_t *player = rpg->player;
    sfImage *copy = rpg->map->image_copy3;
    sfColor pixelColor3 = sfImage_getPixel(copy, newPos.x, newPos.y);
    sfVector2f textPos = {newPos.x, newPos.y - 60};

    rpg->player->pos = newPos;
    sfSprite_setPosition(player->sprite, player->pos);
    sfRectangleShape_setPosition(player->shape, player->pos);
    trigger_player_moved(rpg);
    move_rect(&player->rect, 64, 569);
    sfSprite_setTextureRect(player->sprite, player->rect);
    change_sfview(rpg, player->pos);
    sfText_setPosition(player->text_hidden, textPos);
    player->direction = (sfVector2f){0, 0};
    if (pixelColor3.r == 137 && pixelColor3.g == 68 && pixelColor3.b == 40){
        rpg->player->hidden = 1;
    } else {
        rpg->player->hidden = 0;
    }
}

void move_player(rpg_t *rpg, int x, int y)
{
    player_t *player = rpg->player;
    sfVector2f newPos2 = player->pos;

    player->direction.x += x;
    player->direction.y += y;
    newPos2.x += player->direction.x * 5;
    newPos2.y += player->direction.y * 5;
    if (check_collision(rpg, newPos2)) {
        if (!check_surroundings(rpg, newPos2)){
            player->direction.x += x;
            player->direction.y += y;
        }
    } else {
        player->direction.x += x;
        player->direction.y += y;
    }
}

static int check_direction(rpg_t *rpg, sfVector2f newPos)
{
    player_t *player = rpg->player;
    sfVector2u mapSize = rpg->map->size;

    if (rpg->state != PLAYING && rpg->state != IN_QUEST)
        return 1;
    if (player->direction.x == 0 && player->direction.y == 0)
        return 1;
    if (newPos.x < 0 || newPos.x > mapSize.x
        || newPos.y < 0 || newPos.y > mapSize.y)
        return 1;
    return 0;
}

void move_player2(rpg_t *rpg, float deltaTime)
{
    sfVector2f newPos = rpg->player->pos;
    sfVector2f newPos2 = rpg->player->pos;
    player_t *player = rpg->player;
    float speed = player->speed * deltaTime;

    newPos.x += player->direction.x * speed;
    newPos.y += player->direction.y * speed;
    if (check_direction(rpg, newPos))
        return;
    newPos2.x += player->direction.x * 5;
    newPos2.y += player->direction.y * 5;
    if (check_collision(rpg, newPos2)) {
        if (!check_surroundings(rpg, newPos2))
            update_player_position(rpg, newPos);
    } else {
        update_player_position(rpg, newPos);
    }
    player->direction = (sfVector2f){0, 0};
}
