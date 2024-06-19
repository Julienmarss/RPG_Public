/*
** EPITECH PROJECT, 2023
** rpg
** File description:
** save_game.c
*/

#include "rpg.h"
#include <string.h>
#include <time.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>


static save_t save_game(rpg_t *rpg)
{
    player_t *player = rpg->player;
    save_t save;

    save.posX = player->pos.x;
    save.posY = player->pos.y;
    save.hp = player->hp;
    save.xp = player->xp;
    save.axe = player->axe;
    save.shield = player->shield;
    strcpy(save.name, player->name);
    return save;
}

void save_in_file(rpg_t *rpg)
{
    save_t save = save_game(rpg);
    struct stat st;
    FILE *file = NULL;
    time_t now = time(NULL);
    struct tm *t = localtime(&now);
    char name[100];

    if (stat("saves", &st) == -1) {
        mkdir("saves", 0700);
    }
    strftime(name, sizeof(name) - 1, "saves/%Y-%m-%d_%H-%M-%S.dat", t);
    file = fopen(name, "wb");
    if (file == NULL){
        printf("Error while saving the game\n");
        return;
    }
    fwrite(&save, sizeof(save_t), 1, file);
    fclose(file);
}

static void set_rpg_value(rpg_t *rpg, save_t *save)
{
    player_t *player = rpg->player;

    player->pos.x = save->posX;
    player->pos.y = save->posY;
    player->hp = save->hp;
    player->xp = save->xp;
    player->axe = save->axe;
    player->shield = save->shield;
    player->name = strdup(save->name);
    set_state(rpg, PLAYING);
    back_player(rpg);
    sfText_setString(rpg->player->text, rpg->player->name);
    sfText_setString(rpg->player->text_hidden, rpg->player->name);
    set_lifebar_percent(rpg, rpg->player->hp, 1, 100);
}

static int is_valid_edited_file(char *name)
{
    struct stat file_info;
    struct tm *mod_time;
    char mod_time_str[100];
    char *filename;

    if (stat(name, &file_info) == -1){
        printf("Error while loading the game\n");
        return (0);
    }
    filename = strrchr(name, '/');
    filename++;
    mod_time = localtime(&file_info.st_mtime);
    strftime(mod_time_str, 100, "%Y-%m-%d_%H-%M-%S.dat", mod_time);
    if (strcmp(mod_time_str, name + 6) != 0){
        printf("Error while loading the game\n");
        return (0);
    }
    return 1;
}

void load_from_file(rpg_t *rpg, char *name)
{
    FILE *file = fopen(name, "rb");
    save_t save;

    if (file == NULL){
        printf("Error while loading the game\n");
        return;
    }
    if (strlen(name) < 4 || strlen(name) > 30){
        printf("name is too short or too long\n");
        return;
    }
    if (is_valid_edited_file(name) == 0){
        printf("Error while loading the game\n");
        set_state(rpg, WAITING);
        back(rpg);
        return;
    }
    fread(&save, sizeof(save_t), 1, file);
    set_rpg_value(rpg, &save);
}
