/*
** EPITECH PROJECT, 2023
** rpg
** File description:
** init_scoreboard.c
*/

#include "rpg.h"
#include "helper.h"

static void init_scoreboard_text(scoreboard_t *scoreboard, sfColor color)
{
    scoreboard->text = sfText_create();
    scoreboard->font = sfFont_createFromFile("resources/fonts/font.ttf");
    scoreboard->shape = sfRectangleShape_create();
    sfText_setFont(scoreboard->text, scoreboard->font);
    sfText_setCharacterSize(scoreboard->text, 20);
    sfText_setPosition(scoreboard->text, (sfVector2f){10, 10});
    sfText_setColor(scoreboard->text, color);
    set_shape(scoreboard->shape, (sfVector2f){0, 0});
}

scoreboard_t *init_scoreboard(char *str, sfColor color, int seconds)
{
    scoreboard_t *scoreboard = malloc(sizeof(scoreboard_t));
    sfVector2f middle = {1920 / 2, 1080 / 3};
    sfVector2f shapeSize;
    sfFloatRect size;

    init_scoreboard_text(scoreboard, color);
    sfText_setPosition(scoreboard->text, middle);
    sfText_setString(scoreboard->text, str);
    size = sfText_getGlobalBounds(scoreboard->text);
    shapeSize = (sfVector2f){size.width, size.height * 1.50};
    sfRectangleShape_setPosition(scoreboard->shape, middle);
    sfRectangleShape_setSize(scoreboard->shape, shapeSize);
    scoreboard->seconds = seconds;
    scoreboard->current_seconds = 0;
    return scoreboard;
}

void destroy_scoreboard(rpg_t *rpg)
{
    if (rpg->scoreboard == NULL)
        return;
    sfText_destroy(rpg->scoreboard->text);
    sfFont_destroy(rpg->scoreboard->font);
    sfRectangleShape_destroy(rpg->scoreboard->shape);
    free(rpg->scoreboard);
    rpg->scoreboard = NULL;
}

void add_second_to_scoreboard(rpg_t *rpg)
{
    scoreboard_t *scoreboard = rpg->scoreboard;

    if (scoreboard == NULL)
        return;
    if (scoreboard->seconds == -1){
        return;
    }
    scoreboard->current_seconds++;
    if (scoreboard->current_seconds > scoreboard->seconds){
        destroy_scoreboard(rpg);
    }
}

void display_scoreboard(rpg_t *rpg)
{
    scoreboard_t *scoreboard = rpg->scoreboard;
    sfRenderWindow *window = rpg->window;

    if (scoreboard == NULL)
        return;
    if (scoreboard->text != NULL)
        sfRenderWindow_drawText(window, scoreboard->text, NULL);
    if (scoreboard->shape != NULL)
        sfRenderWindow_drawRectangleShape(window, scoreboard->shape, NULL);
}
