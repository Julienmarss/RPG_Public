/*
** EPITECH PROJECT, 2023
** rpg
** File description:
** mob.c
*/
#include "rpg.h"
#include "helper.h"
#include <string.h>

static void init_mob_shape(mob_t *mob, sfVector2f pos)
{
    sfVector2f size = {250, 250};

    mob->shape = sfRectangleShape_create();
    set_shape(mob->shape, pos);
    sfRectangleShape_setSize(mob->shape, size);
}

static void init_mob_text(mob_t *mob, sfVector2f pos, rpg_t *rpg)
{
    init_mob_shape(mob, pos);
    mob->font = sfFont_createFromFile("resources/fonts/font.ttf");
    mob->text = sfText_create();
    sfText_setFont(mob->text, mob->font);
    sfText_setCharacterSize(mob->text, 20);
    sfText_setString(mob->text, mob->name);
    mob->hp = mob->hp_max;
    add_mob(rpg, mob);
}

void add_mob(rpg_t *rpg, mob_t *mob)
{
    mob_t *tmp = rpg->mobs;

    if (tmp == NULL) {
        rpg->mobs = mob;
        return;
    }
    while (tmp->next)
        tmp = tmp->next;
    tmp->next = mob;
}

mob_t *init_mob(rpg_t *rpg, char *name, char *texture)
{
    mob_t *mob = malloc(sizeof(mob_t));
    sfVector2f pos = get_window_center(rpg->window);

    pos.x = 450 * 3;
    pos.y = 500;
    mob->name = name;
    mob->hp_max = 100;
    mob->killed = 0;
    mob->next = NULL;
    mob->sprite = sfSprite_create();
    mob->uuid = texture;
    mob->texture = sfTexture_createFromFile(texture, NULL);
    if (strcmp(texture, "resources/images/snake.png") == 0){
        mob->name = "sea snake";
        mob->hp_max = 75;
    }
    sfSprite_setTexture(mob->sprite, mob->texture, sfTrue);
    sfSprite_setPosition(mob->sprite, pos);
    init_mob_text(mob, pos, rpg);
    return mob;
}

void destroy_mob(mob_t *mob)
{
    sfSprite_destroy(mob->sprite);
    sfTexture_destroy(mob->texture);
    sfText_destroy(mob->text);
    sfFont_destroy(mob->font);
    sfRectangleShape_destroy(mob->shape);
    free(mob);
}

void destroy_mobs(mob_t *mob)
{
    mob_t *tmp = mob;

    while (mob != NULL) {
        tmp = mob;
        mob = mob->next;
        destroy_mob(tmp);
    }
}
