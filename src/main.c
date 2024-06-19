/*
** EPITECH PROJECT, 2023
** rpg
** File description:
** main.c
*/

#include "rpg.h"
#include <string.h>

int check_tty(char **env)
{
    for (int i = 0; env[i] != NULL; i++)
        if (strncmp(env[i], "DISPLAY", 7) == 0)
            return 0;
    return 1;
}

int main(int ac, char **av, char **env)
{
    rpg_t *rpg;
    sfRenderWindow* window;

    (void) ac;
    (void) av;
    if (check_assets() != 0 || check_tty(env) != 0)
        return 84;
    rpg = make_game();
    window = rpg->window;
    while (sfRenderWindow_isOpen(window)) {
        eventmanager(rpg);
        clockmanager(rpg);
    }
    free_all(rpg);
    return 0;
}
