/*
** EPITECH PROJECT, 2023
** rpg
** File description:
** helper.h
*/

#ifndef HELPER_H
    #define HELPER_H
    #include <SFML/Graphics.h>
    #include <SFML/System.h>
    #include <SFML/Audio.h>
    #include <stdlib.h>
    #include <sys/stat.h>
// src/helpers/move.c
void move_rect(sfIntRect *rect, int offset, int max_value);
sfIntRect set_rect(sfSprite *sprite, int width, int height);
// src/helpers/load.c
sfTexture* load_texture(const char *filename);
sfSprite* load_sprite(sfTexture *texture);
sfFont* load_font(const char *filename);
sfMusic* load_music(const char *filename);
// src/helpers/destroy.c
void destroy_texture(sfTexture *texture);
void destroy_sprite(sfSprite *sprite);
void destroy_font(sfFont *font);
void destroy_music(sfMusic *music);
// src/helpers/utilities.c
sfVector2f get_window_center(sfRenderWindow *window);
sfVector2f get_sprite_center(sfSprite *sprite);
sfVector2f get_sprite_position(sfSprite *sprite);
sfVector2u get_window_size(sfRenderWindow *window);
void set_shape(sfRectangleShape *shape, sfVector2f pos);
// src/helpers/render.c
void render_shape(sfRenderWindow *window, sfRectangleShape *shape);
// src/helpers/utilities2.c
sfVector2f get_top_position_view(sfView *view);
sfVector2f get_right_position_view(sfView *view);
#endif /* !HELPER_H */
