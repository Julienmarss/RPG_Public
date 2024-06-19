/*
** EPITECH PROJECT, 2023
** rpg
** File description:
** demo.c
*/
#include "rpg.h"
#include "helper.h"
#include <string.h>

static void demo_click(rpg_t *rpg)
{
    (void) rpg;
}

static void demo_click2(rpg_t *rpg)
{
    (void) rpg;
}

static int should_demo_display(rpg_t *rpg)
{
    if (rpg->demo_timer >= 5) {
        return 0;
    }
    return should_when_playing(rpg);
}

sfText *create_demo_text(sfFont *font)
{
    sfText *text;
    sfVector2f textPos;

    text = sfText_create();
    if (!text) {
        printf("Error creating text\n");
        return NULL;
    }
    sfText_setString(text, "toggle the music\n\t\twith M\n\n  Save the game\n\
    \twith W");
    sfText_setFont(text, font);
    sfText_setCharacterSize(text, 11);
    sfText_setFillColor(text, sfWhite);
    textPos = (sfVector2f){2580, 170};
    sfText_setPosition(text, textPos);
    return text;
}

void process_demo(rpg_t *rpg)
{
    sfFont *font = load_font("resources/fonts/viking.ttf");
    sfText *text = create_demo_text(font);
    asset_t *textAsset = NULL;

    if (!text) {
        return;
    }
    textAsset = add_asset(rpg, NULL,
        should_demo_display, &demo_click2);
    textAsset->text = text;
    textAsset->font = font;
}

void change_demo_position(rpg_t *rpg)
{
    asset_t *asset = get_asset_from_onclick(rpg, &demo_click);
    asset_t *asset2 = get_asset_from_onclick(rpg, &demo_click2);
    sfVector2f pos = get_right_position_view(rpg->view);

    pos.x -= 150;
    sfSprite_setPosition(asset->sprite, pos);
    pos.y += 170;
    sfText_setPosition(asset2->text, pos);
}

void init_demo(rpg_t *rpg)
{
    char *path = "resources/images/demo.png";
    asset_t *asset = add_asset(rpg, path, &should_demo_display, &demo_click);
    sfVector2u size = sfTexture_getSize(asset->texture);

    sfSprite_setScale(asset->sprite, (sfVector2f){0.5, 0.5});
    set_asset_pos(asset, (sfVector2f){2580, 0}, size);
    process_demo(rpg);
}
