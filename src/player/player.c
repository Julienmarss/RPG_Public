/*
** EPITECH PROJECT, 2023
** rpg
** File description:
** player.c
*/
#include "rpg.h"
#include <string.h>
#include "helper.h"

void destroy_player(player_t *player)
{
    destroy_sprite(player->sprite);
    destroy_font(player->font);
    sfText_destroy(player->text);
    destroy_sprite(player->sign);
    sfTexture_destroy(player->sign_texture);
    sfTexture_destroy(player->texture);
    sfRectangleShape_destroy(player->shape);
    sfText_destroy(player->xp_text);
    sfRectangleShape_destroy(player->healthbar);
    sfRectangleShape_destroy(player->lifebar);
    sfSprite_destroy(player->xp_sprite);
    sfTexture_destroy(player->xp_texture);
    sfText_destroy(player->textlife);
    sfText_destroy(player->text_hidden);
    free(player);
}

void display_player(rpg_t *rpg)
{
    if (rpg->player->hidden == 0 && rpg->state != IN_FIGHT){
        sfRenderWindow_drawSprite(rpg->window, rpg->player->sprite, NULL);
    }
    if (rpg->state != IN_FIGHT)
        sfRenderWindow_drawText(rpg->window, rpg->player->text_hidden, NULL);
    sfRenderWindow_drawSprite(rpg->window, rpg->player->sign, NULL);
    render_shape(rpg->window, rpg->player->lifebar);
    render_shape(rpg->window, rpg->player->healthbar);
    sfRenderWindow_drawText(rpg->window, rpg->player->text, NULL);
    sfRenderWindow_drawText(rpg->window, rpg->player->xp_text, NULL);
    sfRenderWindow_drawText(rpg->window, rpg->player->textlife, NULL);
    sfRenderWindow_drawSprite(rpg->window, rpg->player->xp_sprite, NULL);
}

static char *get_skin_filename(player_skin_t skin)
{
    switch (skin) {
        case CLASSIC:
            return "resources/images/player/classic.png";
        case AXE:
            return "resources/images/player/axe.png";
        case SHIELD:
            return "resources/images/player/shield.png";
        case AXESHIELD:
            return "resources/images/player/axeshield.png";
    }
    return "resources/images/player/classic.png";
}

void change_skin(player_t *player, player_skin_t skin)
{
    sfTexture_destroy(player->texture);
    player->texture = load_texture(get_skin_filename(skin));
    sfSprite_setTexture(player->sprite, player->texture, sfTrue);
}

void move_player3(rpg_t *rpg, int x, int y)
{
    sfVector2f newPos = rpg->player->pos;
    player_t *player = rpg->player;

    newPos.x += x;
    newPos.y += y;
    if (newPos.x < 0 || newPos.y < 0 || newPos.x > 1920 || newPos.y > 1080)
        return;
    rpg->player->pos = newPos;
    sfSprite_setPosition(player->sprite, player->pos);
    sfRectangleShape_setPosition(player->shape, player->pos);
    change_sfview(rpg, player->pos);
    player->direction = (sfVector2f){0, 0};
}
