/*
** EPITECH PROJECT, 2023
** rpg
** File description:
** map.c
*/
#include "rpg.h"
#include "helper.h"

void init_map_collision(rpg_t *rpg, map_t *map)
{
    sfTexture *texture = load_texture("resources/images/bg_collision.png");
    sfTexture *texture2 = load_texture("resources/images/bg_house.png");

    rpg->map->image_copy = sfTexture_copyToImage(sfTexture_copy(texture));
    rpg->map->image_copy2 = sfTexture_copyToImage(sfTexture_copy(texture2));
    map->sprite2 = load_sprite(texture);
    map->sprite3 = load_sprite(texture2);
    map->texture2 = texture;
    map->texture3 = texture2;
    sfSprite_setPosition(map->sprite2, (sfVector2f){0, 0});
    sfSprite_setPosition(map->sprite3, (sfVector2f){0, 0});
}

void init_map_3d(rpg_t *rpg, map_t *map)
{
    sfTexture *texture3 = load_texture("resources/images/bg_3d.png");

    rpg->map->image_copy3 = sfTexture_copyToImage(sfTexture_copy(texture3));
    map->sprite4 = load_sprite(texture3);
    map->texture4 = texture3;
}

void init_map(rpg_t *rpg)
{
    sfTexture *texture = load_texture("resources/images/bg.png");
    map_t *map = malloc(sizeof(map_t));

    map->sprite = load_sprite(texture);
    map->texture = texture;
    map->size = sfTexture_getSize(texture);
    sfSprite_setPosition(map->sprite, (sfVector2f){0, 0});
    rpg->map = map;
    rpg->assets = NULL;
    rpg->scoreboard = NULL;
    rpg->npcs = NULL;
    init_waiting(rpg);
    init_npc(rpg);
    init_map_collision(rpg, map);
    init_map_3d(rpg, map);
}

void destroy_map(map_t *map)
{
    destroy_texture(map->texture);
    destroy_sprite(map->sprite);
    destroy_texture(map->texture2);
    destroy_sprite(map->sprite2);
    sfImage_destroy(map->image_copy);
    free(map);
}
