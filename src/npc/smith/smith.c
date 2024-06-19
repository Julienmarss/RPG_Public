/*
** EPITECH PROJECT, 2023
** rpg
** File description:
** smith.c
*/
#include "rpg.h"
#include "helper.h"

void init_axe_asset(rpg_t *rpg)
{
    char *filename = "resources/images/axe.png";
    asset_t *asset = add_asset(rpg, filename, &should_in_gui_smith_axe,
        &smith_purchase_axe);
    sfVector2f pos = {600, 350};
    sfVector2u size;
    smith_gui_t *gui = rpg->smith_gui;
    char text[50];

    gui->axe_requirement = 5;
    sfSprite_setScale(asset->sprite, (sfVector2f){0.5, 0.5});
    size = sfTexture_getSize(asset->texture);
    gui->axe_text = sfText_create();
    sprintf(text, "Axe : %d xp required\n", gui->axe_requirement);
    sfText_setString(gui->axe_text, text);
    sfText_setFont(gui->axe_text, rpg->smith_gui->font);
    sfText_setCharacterSize(gui->axe_text, 25);
    sfText_setPosition(gui->axe_text, (sfVector2f){600, 250});
    size.x *= 0.5;
    size.y *= 0.5;
    set_asset_pos(asset, pos, size);
}

static void init_shield_asset(rpg_t *rpg)
{
    char *filename = "resources/images/shield.png";
    asset_t *asset = add_asset(rpg, filename, &should_in_gui_smith_shield,
        &smith_purchase_shield);
    sfVector2f pos = {1000, 350};
    sfVector2u size;
    smith_gui_t *gui = rpg->smith_gui;
    char text[50];

    gui->shield_requirement = 10;
    sfSprite_setScale(asset->sprite, (sfVector2f){0.5, 0.5});
    size = sfTexture_getSize(asset->texture);
    size.x *= 0.5;
    size.y *= 0.5;
    gui->shield_text = sfText_create();
    sprintf(text, "Shield : %d xp required\n", gui->shield_requirement);
    sfText_setString(gui->shield_text, text);
    sfText_setFont(gui->shield_text, rpg->smith_gui->font);
    sfText_setCharacterSize(gui->shield_text, 25);
    sfText_setPosition(gui->shield_text, (sfVector2f){1000, 250});
    set_asset_pos(asset, pos, size);
}

static void init_smith(rpg_t *rpg)
{
    smith_gui_t *gui = malloc(sizeof(smith_gui_t));
    char *filename = "resources/images/smith_bg.png";
    sfTexture *texture = sfTexture_createFromFile(filename, NULL);

    gui->bg_texture = texture;
    gui->bg_sprite = sfSprite_create();
    sfSprite_setTexture(gui->bg_sprite, texture, sfTrue);
    sfSprite_setPosition(gui->bg_sprite, (sfVector2f){0, 0});
    rpg->smith_gui = gui;
    rpg->smith_gui->font = sfFont_createFromFile("resources/fonts/font.ttf");
    init_axe_asset(rpg);
    init_shield_asset(rpg);
}

static void trigger_smith_npc(rpg_t *rpg, npc_t *npc)
{
    asset_t *shield = get_asset_from_onclick(rpg, &smith_purchase_shield);
    asset_t *axe = get_asset_from_onclick(rpg, &smith_purchase_axe);

    sfView_setCenter(rpg->view, (sfVector2f){1920 / 2, 510});
    sfRenderWindow_setView(rpg->window, rpg->view);
    change_close_position(rpg);
    change_sign_position(rpg);
    set_state(rpg, IN_SMITH);
    (void) npc;
    set_asset_pos(shield, (sfVector2f){1000, 350}, (sfVector2u){0, 0});
    set_asset_pos(axe, (sfVector2f){600, 350}, (sfVector2u){0, 0});
    sfSprite_setScale(axe->sprite, (sfVector2f){0.5, 0.5});
    sfSprite_setScale(shield->sprite, (sfVector2f){0.5, 0.5});
}

void init_smith_npc(rpg_t *rpg)
{
    char *filename = "resources/images/smith.png";
    asset_t *asset = add_asset(rpg, filename, &should_when_playing, NULL);
    npc_t *npc;
    sfVector2f pos = {1735, 1450};
    sfVector2u size;

    sfSprite_setScale(asset->sprite, (sfVector2f){0.3, 0.3});
    size = sfTexture_getSize(asset->texture);
    size.x *= 0.2;
    size.y *= 0.2;
    npc = add_npc(rpg, asset, &should_when_playing, &trigger_smith_npc);
    set_npc_pos(npc, pos, (sfVector2u){75, 75});
    init_smith(rpg);
}

void display_smith(rpg_t *rpg)
{
    sfRenderWindow_clear(rpg->window, sfBlack);
    sfRenderWindow_drawSprite(rpg->window, rpg->smith_gui->bg_sprite, NULL);
    sfRenderWindow_drawText(rpg->window, rpg->smith_gui->axe_text, NULL);
    sfRenderWindow_drawText(rpg->window, rpg->smith_gui->shield_text, NULL);
}

void destroy_smith_gui(smith_gui_t *gui)
{
    sfTexture_destroy(gui->bg_texture);
    sfSprite_destroy(gui->bg_sprite);
    sfText_destroy(gui->axe_text);
    sfFont_destroy(gui->font);
    free(gui);
}

void change_player_texture(rpg_t *rpg)
{
    player_t *player = rpg->player;
    char *filename = "resources/images/player/classic.png";

    if (player->axe == 1)
        filename = "resources/images/player/axe.png";
    if (player->shield == 1)
        filename = "resources/images/player/shield.png";
    if (player->axe == 1 && player->shield == 1)
        filename = "resources/images/player/axeshield.png";
    sfTexture_destroy(player->texture);
    player->texture = sfTexture_createFromFile(filename, NULL);
    sfSprite_setTexture(player->sprite, player->texture, sfTrue);
    player->rect = set_rect(player->sprite, 65, 65);
    sfSprite_setTextureRect(player->sprite, player->rect);
}
