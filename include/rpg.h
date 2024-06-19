/*
** EPITECH PROJECT, 2023
** rpg
** File description:
** rpg.h
*/

#ifndef RPG_H
    #define RPG_H
    #include <SFML/Window.h>
    #include <SFML/Graphics.h>
    #include <SFML/Audio.h>
    #include <stdio.h>
    #include <stdlib.h>
    #include <unistd.h>
    #define WIDTH 1920
    #define HEIGHT 1080
    #define DEFAULT_PLAYER_HP 100
    #define DEFAULT_PLAYER_HP_MAX 100
    #define DEFAULT_PLAYER_POS_X 2400
    #define DEFAULT_PLAYER_POS_Y 200
    #define DEFAULT_PLAYER_SPEED 50

typedef enum game_state_e {
    WAITING,
    PLAYING,
    IN_QUEST,
    PAUSED,
    SETTINGS,
    IN_MENU,
    SAVE_MENU,
    IN_FIGHT,
    GRAPHICS,
    VOLUME,
    IN_SMITH,
} game_state_t;

typedef enum player_skin_e {
    CLASSIC,
    AXE,
    SHIELD,
    AXESHIELD,
} player_skin_t;
struct rpg_s;

typedef struct save_s {
    char name[50];
    int hp;
    int xp;
    int posX;
    int posY;
    int axe;
    int shield;
} save_t;

typedef struct player_s {
    char *name;
    int hp;
    int hp_max;
    int speed;
    int xp;
    sfVector2f pos;
    sfVector2f center;
    sfIntRect rect;
    sfSprite *sprite;
    sfText *text;
    sfFont *font;
    sfRectangleShape *shape;
    sfSprite *sign;
    sfTexture *sign_texture;
    sfTexture *texture;
    sfText *xp_text;
    sfRectangleShape *healthbar;
    sfRectangleShape *lifebar;
    sfSprite *xp_sprite;
    sfTexture *xp_texture;
    sfText *textlife;
    sfText *text_hidden;
    player_skin_t skin;
    int max_attack;
    int min_attack;
    int max_defense;
    int min_defense;
    int axe;
    int shield;
    int hidden;
    sfVector2f direction;
    int in_quest;
} player_t;

typedef struct map_s {
    sfTexture *texture;
    sfTexture *texture2;
    sfTexture *texture3;
    sfTexture *texture4;
    sfSprite *sprite;
    sfSprite *sprite2;
    sfSprite *sprite3;
    sfSprite *sprite4;
    sfVector2u size;
    sfImage *image_copy;
    sfImage *image_copy2;
    sfImage *image_copy3;
} map_t;

typedef struct asset_s {
    char *uuid;
    sfTexture *texture;
    sfTexture *hover_texture;
    sfSprite *sprite;
    sfVector2f pos;
    sfVector2u size;
    sfRectangleShape *shape;
    sfText *text;
    sfFont *font;
    struct asset_s *next;
    void (*onclick)(struct rpg_s *game);
    int (*should_display)(struct rpg_s *game);
    void (*oninteract)(struct rpg_s *game, struct asset_s *asset);
} asset_t;

typedef struct boutton_info_s {
    char *image_path;
    char *hover_image_path;
    void (*callback)(struct rpg_s *);
    sfVector2f position_offset;
} boutton_info_t;


typedef struct npc_s {
    char name[50];
    char meta[50];
    void (*oninteract)(struct rpg_s *game, struct npc_s *npc);
    int (*should_display)(struct rpg_s *game);
    asset_t *asset;
    sfText *text;
    sfFont *font;
    struct npc_s *next;
} npc_t;

typedef struct scoreboard_s {
    sfText *text;
    sfFont *font;
    sfRectangleShape *shape;
    int seconds;
    int current_seconds;
} scoreboard_t;

typedef struct mob_s {
    int hp;
    int hp_max;
    sfVector2f pos;
    sfSprite *sprite;
    sfTexture *texture;
    sfRectangleShape *shape;
    sfText *text;
    sfFont *font;
    struct mob_s *next;
    char *name;
    int killed;
    char *uuid;
} mob_t;

typedef struct fight_s {
    mob_t *mob;
    sfSprite *background;
    sfRectangleShape *lifebar_mob;
    sfRectangleShape *healthbar_mob;
    sfTexture *background_texture;
    sfSprite *sign;
    sfTexture *sign_texture;
    sfText *textlife_mob;
    sfText *textinfo;
    sfSprite *player_sprite;
    sfTexture *player_texture;
} fight_t;

typedef struct smith_gui_s {
    int axe_requirement;
    int shield_requirement;
    sfSprite *bg_sprite;
    sfTexture *bg_texture;
    sfText *axe_text;
    sfFont *font;
    sfText *shield_text;
} smith_gui_t;

typedef struct rpg_s {
    sfRenderWindow *window;
    map_t *map;
    map_t *map_collision;
    sfView *view;
    player_t *player;
    npc_t *npcs;
    sfClock *clock;
    game_state_t oldstate;
    game_state_t state;
    asset_t *assets;
    scoreboard_t *scoreboard;
    fight_t *fight;
    sfSprite *graphicsBackground;
    sfSprite *settingsBackground;
    sfSprite *menuBackground;
    sfSprite *saveBackground;
    asset_t *menuButtons;
    sfMusic *music;
    mob_t *mobs;
    smith_gui_t *smith_gui;
    sfClock *clock_player;
    int demo_timer;
} rpg_t;
// src/rpg.c
int back(rpg_t *rpg);
rpg_t *make_game(void);
void destroy_game(rpg_t *game);
// src/player/player_init.c
void init_player(rpg_t *rpg, char *name);
// src/player/player_move.c
void move_player(rpg_t *rpg, int x, int y);
void move_player2(rpg_t *rpg, float deltaTime);
void back_player(rpg_t *rpg);
void change_sign_position(rpg_t *rpg);
// src/player.c
void destroy_player(player_t *player);
void change_sfview(rpg_t *rpg, sfVector2f pos);
void display_player(rpg_t *rpg);
// src/npc/smith.c
void init_smith_npc(rpg_t *rpg);
void destroy_smith_gui(smith_gui_t *gui);
// src/map.c
void init_map(rpg_t *game);
void destroy_map(map_t *map);
// src/events/eventmanager.c
int eventmanager(rpg_t *game);
// src/events/keypressed.c
void keypressed(rpg_t *game, sfEvent event);
// src/events/click.c
void click(rpg_t *rpg, sfEvent event);
// src/events/resize.c
int resize(sfRenderWindow *window, sfEvent event, rpg_t *rpg);
// src/free.c
int free_all(rpg_t *rpg);
// src/display.c
void display(rpg_t *game);
void display_fight(rpg_t *rpg);
// src/window.c
sfRenderWindow *create_window(void);
// src/assets/assets.c
asset_t *add_asset(rpg_t *rpg, char *path,
    int (*should)(struct rpg_s *game),
    void (*onclick)(struct rpg_s *game)
);
void destroy_assets(asset_t *assets);
void set_asset_pos(asset_t *asset, sfVector2f pos, sfVector2u size);
asset_t *get_asset_from_onclick(rpg_t *rpg, void (*onclick)(rpg_t *rpg));
int remove_asset(rpg_t *rpg, asset_t *asset);
asset_t *get_asset_from_oninteract(rpg_t *rpg,
    void (*oninteract)(rpg_t *rpg, asset_t *asset));
// src/assets/should_display.c
int should_always_display(rpg_t *game);
int should_when_playing(rpg_t *game);
int should_when_waiting(rpg_t *game);
void move_player3(rpg_t *rpg, int x, int y);
int should_when_not_waiting(rpg_t *game);
// src/waiting/waiting.c
void on_start_button(rpg_t *rpg);
void init_waiting(rpg_t *rpg);
// src/buttons/close.c
void init_close(rpg_t *rpg);
void close_game(rpg_t *rpg);
void change_close_position(rpg_t *rpg);
// src/npc/npc.c
void init_npc(rpg_t *rpg);
npc_t *add_npc(rpg_t *rpg, asset_t *asset,
    int (*should_display)(rpg_t *rpg),
    void (*oninteract)(rpg_t *rpg, npc_t *npc));
void destroy_npc(npc_t *npc);
void set_npc_pos(npc_t *npc, sfVector2f pos, sfVector2u size);
void set_npc_name(npc_t *npc, char *name, sfVector2f pos);
// src/npc/trigger.c
void trigger_npc(rpg_t *rpg);
// src/npc/apple_npc.c
void init_apple_npc(rpg_t *rpg);
void oninteract_npc_apple(rpg_t *rpg, npc_t *npc);
void set_random_apple(rpg_t *rpg, npc_t *npc, asset_t *asset);
void oninteract_apple(rpg_t *rpg, asset_t *asset);
// src/npc/smith.c
void init_smith_npc(rpg_t *rpg);
void display_smith(rpg_t *rpg);
int should_in_gui_smith_axe(rpg_t *rpg);
int should_in_gui_smith_shield(rpg_t *rpg);
void smith_purchase_axe(rpg_t *rpg);
void smith_purchase_shield(rpg_t *rpg);
void change_player_texture(rpg_t *rpg);
// src/events/move.c
int move(rpg_t *rpg, sfEvent event);
// src/scoreboard/init_scoreboard.c
scoreboard_t *init_scoreboard(char *str, sfColor color, int seconds);
void destroy_scoreboard(rpg_t *rpg);
void add_second_to_scoreboard(rpg_t *rpg);
void display_scoreboard(rpg_t *rpg);
void change_scoreboard_position(rpg_t *rpg);
// src/clock/clockmanager.c
void clockmanager(rpg_t *rpg);
// src/helpers/move.c
int in_bounds(asset_t *asset, sfVector2f mouse);
// src/assets/trigger.c
void trigger_assets(rpg_t *rpg);
// src/npc/npc_utils.c
npc_t *get_npc_by_asset(asset_t *asset, rpg_t *rpg);
npc_t *get_npc_by_oninteract(void (*oninteract)(rpg_t *, npc_t *), rpg_t *rpg);
// src/helpers/atoa.c
char *my_itoa(int nb);
// src/fight/init_fight.c
void init_fight(mob_t *mob, rpg_t *rpg, char *filename);
void start_fight(rpg_t *rpg, mob_t *mob, char *filename);
void destroy_fight(fight_t *fight);
//src/demo/demo.c
void change_demo_position(rpg_t *rpg);
void init_demo(rpg_t *rpg);
//src/fight/mob/mob.c
void add_mob(rpg_t *rpg, mob_t *mob);
// src/fight/npc.c
void init_mob_npc(rpg_t *rpg);
void on_mob_interact(rpg_t *rpg, npc_t *npc);
// src/fight/fight.c
void fight(rpg_t *rpg, sfVector2i mouse);
// src/fight/lifebar.c
void create_lifebar(fight_t *fight);
void create_healthbar(fight_t *fight);
void set_lifebar_percent(rpg_t *rpg, int percent, int player, int max_hp);
// src/fight/mob/mob.c
void destroy_mob(mob_t *mob);
void destroy_mobs(mob_t *mobs);
mob_t *init_mob(rpg_t *rpg, char *name, char *texture);
// src/state/state.c
int set_state(rpg_t *rpg, int state);
//src/menu
void on_open_settings(rpg_t *rpg);
void init_settings_menu(rpg_t *rpg);
void init_main_menu(rpg_t *rpg);
void display_new_menu(rpg_t *rpg);
void display_settings_menu(rpg_t *rpg);
void on_start_game(rpg_t *rpg);
void on_save_game(rpg_t *rpg);
void on_volume_change(rpg_t *rpg);
void on_resolution_change(rpg_t *rpg);
void init_graphics_settings(rpg_t *rpg);
void on_back_to_settings(rpg_t *rpg);
int should_display_in_volume(rpg_t *rpg);
void init_volume_boutton(rpg_t *rpg, sfVector2f pos,
    const char *image_path, void (*callback)(rpg_t *));
void init_volume_settings(rpg_t *rpg);
int should_display_in_graphics(rpg_t *rpg);
void init_graphics_boutton(rpg_t *rpg, sfVector2f pos,
    const char *image_path, void (*callback)(rpg_t *));
int should_display_in_settings(rpg_t *rpg);
void init_settings_button(rpg_t *rpg, sfVector2f pos,
    const char *image_path, void (*callback)(rpg_t *));
void on_back_to_menu(rpg_t *rpg);
//src/display
void display_playing(rpg_t *rpg);
void display_assets(rpg_t *rpg);
void display_npc(rpg_t *rpg, npc_t *npc);
void display_npcs(rpg_t *rpg);
//src/check_assets.c
int check_assets(void);
//src/rpg/map.c
void init_map_collision(rpg_t *rpg, map_t *map);
//src/collision.c
int check_collision(rpg_t *rpg, sfVector2f pos);
int check_surroundings(rpg_t *rpg, sfVector2f pos);
//music.c
void start_music(rpg_t *rpg);
void stop_music(rpg_t *rpg);
void keypressed_for_music(rpg_t *rpg, sfEvent event);
// src/player/player_xp.c
void set_xp(player_t *player, int xp);
void add_xp(player_t *player, int xp);
void remove_xp(player_t *player, int xp);
void xp_click(rpg_t *rpg);
// src/helpers/utilities2.c
int random_nbr(int min, int max);
// src/save/save_game.c
void save_in_file(rpg_t *rpg);
void load_from_file(rpg_t *rpg, char *filename);
void draw_volume_buttons(rpg_t *rpg, sfSprite* graphicsBackground);
void init_volume_button(rpg_t *rpg,
    boutton_info_t button_info, sfVector2f base_pos);
void handle_hover(rpg_t *rpg);
void init_save_menu(rpg_t *rpg);
void set_asset_pos_save(asset_t *asset, sfVector2f pos, sfVector2u size);
int should_display_in_save_menu(rpg_t *rpg);
void display_graphics_settings(rpg_t *rpg);
#endif /* !RPG_H */
