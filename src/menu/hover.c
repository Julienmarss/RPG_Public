/*
** EPITECH PROJECT, 2023
** B-MUL-200-LIL-2-1-myrpg-martin.delebecque
** File description:
** hover.c
*/

#include "rpg.h"
#include "helper.h"

int is_mouse_over_asset(asset_t *asset, sfVector2i mouse_pos)
{
    sfFloatRect bounds;

    if (asset->sprite == NULL)
        return 0;
    bounds = sfSprite_getGlobalBounds(asset->sprite);
    return sfFloatRect_contains(&bounds, mouse_pos.x, mouse_pos.y);
}

void update_asset_texture(asset_t *asset, sfVector2i mouse_pos)
{
    if (is_mouse_over_asset(asset, mouse_pos)) {
        if (asset->hover_texture) {
            sfSprite_setTexture(asset->sprite, asset->hover_texture, sfTrue);
        }
    } else {
        sfSprite_setTexture(asset->sprite, asset->texture, sfTrue);
    }
}

void handle_hover(rpg_t *rpg)
{
    sfVector2i mouse_pos = sfMouse_getPositionRenderWindow(rpg->window);
    asset_t *asset = rpg->assets;

    while (asset) {
        if (asset->should_display(rpg)) {
            update_asset_texture(asset, mouse_pos);
        }
        asset = asset->next;
    }
}
