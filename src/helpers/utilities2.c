/*
** EPITECH PROJECT, 2023
** rpg
** File description:
** utilities2.c
*/

#include "rpg.h"
#include "time.h"

sfVector2f get_top_position_view(sfView *view)
{
    sfVector2f center = sfView_getCenter(view);
    sfVector2f size = sfView_getSize(view);
    sfVector2f vector = {center.x - size.x / 2, center.y - size.y / 2};

    return vector;
}

sfVector2f get_right_position_view(sfView *view)
{
    sfVector2f center = sfView_getCenter(view);
    sfVector2f size = sfView_getSize(view);
    sfVector2f vector = {center.x + size.x / 2, center.y - size.y / 2};

    return vector;
}

int random_nbr(int min, int max)
{
    int random_number;

    srand((unsigned int)time(NULL));
    random_number = rand() % (max - min + 1) + min;
    return random_number;
}
