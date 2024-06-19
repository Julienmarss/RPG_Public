/*
** EPITECH PROJECT, 2023
** B-MUL-200-LIL-2-1-myrpg-martin.delebecque
** File description:
** check_asset.c
*/
#include "rpg.h"
#include "helper.h"

int is_asset(const char **assets)
{
    FILE* file;

    for (int i = 0; assets[i] != NULL; i++) {
        file = fopen(assets[i], "r");
        if (file) {
            fclose(file);
        } else {
            printf("Error: %s not found\n", assets[i]);
            return 84;
        }
    }
    return 0;
}

static int check_background(void)
{
    const char *background[] = {
        "resources/images/bg.png",
        "resources/images/bg_collision.png",
        "resources/images/bg_house.png",
        "resources/images/bg_3d.png",
        "resources/images/bg_set.png",
        "resources/images/fight_sea.png",
        "resources/images/fight.png",
        "resources/images/menu_bg.png",
        "resources/images/smith_bg.png",
        NULL
    };

    if (is_asset(background) != 0) {
        return 84;
    } else {
        return 0;
    }
}

static int check_settings(void)
{
    const char *settings[] = {
        "resources/images/30_fps.png",
        "resources/images/60_fps.png",
        "resources/images/graph_settings.png",
        "resources/images/sound_settings.png",
        "resources/images/off.png",
        "resources/images/on.png",
        "resources/images/save.png",
        "resources/images/settings.png",
        NULL,
    };

    if (is_asset(settings) != 0) {
        return 84;
    } else {
        return 0;
    }
}

static int check_mobs(void)
{
    const char *mobs[] = {
        "resources/images/mob1.png",
        "resources/images/pnj1.png",
        "resources/images/smith.png",
        "resources/images/snake.png",
        "resources/images/wolf.png",
        "resources/images/wolf2.png",
        NULL
    };

    if (is_asset(mobs) != 0) {
        return 84;
    } else {
        return 0;
    }
}

static int check_images(void)
{
    const char *images[] = {
        "resources/images/close.png",
        "resources/images/apple.png",
        "resources/images/logo.png",
        "resources/images/back.png",
        "resources/images/xp.png",
        "resources/images/start.png",
        "resources/images/play.png",
        "resources/images/shield.png",
        "resources/images/sign.png",
        NULL
    };

    if (is_asset(images) != 0) {
        return 84;
    } else {
        return 0;
    }
}

static int check_music(void)
{
    const char *music[] = {
        "resources/music.ogg",
        "resources/fonts/font.ttf",
        NULL
    };

    if (is_asset(music) != 0) {
        return 84;
    } else {
        return 0;
    }
}

int check_assets(void)
{
    if (check_images() != 0) {
        return 84;
    }
    if (check_music() != 0) {
        return 84;
    }
    if (check_mobs() != 0) {
        return 84;
    }
    if (check_settings() != 0) {
        return 84;
    }
    if (check_background() != 0) {
        return 84;
    }
    return 0;
}
