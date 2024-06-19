/*
** EPITECH PROJECT, 2023
** rpg
** File description:
** assets.c
*/
#include "rpg.h"
#include "helper.h"

static void tampax(asset_t *asset)
{
    asset->hover_texture = NULL;
    asset->text = NULL;
    asset->font = NULL;
}

static asset_t *init_asset(char *file, int (*should_display)(rpg_t *rpg),
    void (*onclick)(rpg_t *rpg))
{
    asset_t *asset = malloc(sizeof(asset_t));

    if (file != NULL){
        asset->texture = load_texture(file);
        asset->sprite = load_sprite(asset->texture);
        asset->size = sfTexture_getSize(asset->texture);
    } else {
        asset->texture = NULL;
        asset->sprite = NULL;
    }
    asset->next = NULL;
    asset->should_display = should_display;
    asset->onclick = onclick;
    asset->oninteract = NULL;
    asset->uuid = file;
    tampax(asset);
    asset->shape = sfRectangleShape_create();
    set_shape(asset->shape, (sfVector2f){0, 0});
    return asset;
}

asset_t *add_asset(rpg_t *rpg, char *path,
    int (*should_display)(rpg_t *rpg),
    void (*onclick)(rpg_t *rpg))
{
    asset_t *new_asset = malloc(sizeof(asset_t));
    asset_t *tmp = rpg->assets;

    new_asset = init_asset(path, should_display, onclick);
    if (tmp == NULL) {
        rpg->assets = new_asset;
        return new_asset;
    }
    while (tmp->next)
        tmp = tmp->next;
    tmp->next = new_asset;
    return new_asset;
}

void destroy_assets(asset_t *assets)
{
    asset_t *tmp = assets;

    while (tmp) {
        if (tmp->texture != NULL) {
            destroy_texture(tmp->texture);
            destroy_sprite(tmp->sprite);
            sfRectangleShape_destroy(tmp->shape);
        }
        if (tmp->text != NULL){
            sfText_destroy(tmp->text);
        }
        assets = tmp->next;
        free(tmp);
        tmp = assets;
    }
    free(assets);
}

void set_asset_pos(asset_t *asset, sfVector2f pos, sfVector2u size)
{
    sfSprite_setPosition(asset->sprite, pos);
    sfRectangleShape_setPosition(asset->shape, pos);
    asset->pos = pos;
    if (size.x != 0 && size.y != 0)
        sfRectangleShape_setSize(asset->shape, (sfVector2f){size.x, size.y});
}

void set_asset_pos_save(asset_t *asset, sfVector2f pos, sfVector2u size)
{
    sfFloatRect textRect;
    sfVector2f textPos;

    sfSprite_setPosition(asset->sprite, pos);
    if (asset->text) {
        textRect = sfText_getLocalBounds(asset->text);
        textPos = (sfVector2f){pos.x + (size.x / 2.0f) -
        (textRect.width / 2.0f),
        pos.y + (size.y / 2.0f) - (textRect.height / 2.0f)};
        sfText_setPosition(asset->text, textPos);
    }
}
