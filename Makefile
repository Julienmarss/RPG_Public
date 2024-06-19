##
## EPITECH PROJECT, 2023
## rpg
## File description:
## Makefile
##

SOURCE	=	./src/main.c					\
			./src/display.c 				\
			./src/helpers/load.c 			\
			./src/assets/buttons/close.c 	\
			./src/assets/trigger.c 			\
			./src/helpers/move.c 			\
			./src/helpers/render.c 			\
			./src/events/click.c 			\
			./src/helpers/utilities.c 		\
			./src/helpers/utilities2.c 		\
			./src/helpers/destroy.c 		\
			./src/free/free.c 				\
			./src/player/player.c 			\
			./src/save/save_game.c 			\
			./src/player/player_init.c		\
			./src/player/player_move.c		\
			./src/player/player_xp.c		\
			./src/events/eventmanager.c 	\
			./src/events/resize.c 			\
			./src/events/keypressed.c 		\
			./src/rpg/window.c				\
			./src/assets/should_display.c	\
			./src/rpg/map.c					\
			./src/waiting/waiting.c			\
			./src/assets/assets.c			\
			./src/assets/get_asset.c		\
			./src/rpg/rpg.c					\
			./src/npc/apple_npc.c			\
			./src/npc/smith/smith.c			\
			./src/npc/smith/smith_display.c	\
			./src/npc/smith/smith_purchase.c\
			./src/npc/npc_utils.c			\
			./src/events/move.c				\
			./src/clock/clockmanager.c		\
			./src/helpers/atoa.c			\
			./src/scoreboard/scoreboard.c	\
			./src/scoreboard/scoreboard_position.c	\
			./src/npc/npc.c					\
			./src/fight/init_fight.c		\
			./src/fight/mob/mob.c			\
			./src/fight/lifebar.c			\
			./src/fight/fight.c				\
			./src/fight/npc.c				\
			./src/npc/trigger.c				\
			./src/state/state.c				\
			./src/menu/display_menu.c		\
			./src/menu/graphics_menu.c		\
			./src/menu/main_menu.c			\
			./src/menu/settings_menu.c		\
			./src/menu/sound_menu.c			\
			./src/check_assets.c			\
			./src/collision.c 				\
			./src/menu/save_menu.c          \
			./src/menu/utils_save_menu.c    \
			./src/menu/display_sprite.c     \
			./src/music.c 					\
			./src/demo/demo.c 				\
			./src/menu/hover.c 				\

OBJS	=	$(SOURCE:.c=.o)

OUT		=	my_rpg

CC		=	gcc

CFLAGS	+=	-W -Wall -Wextra -I ./include

NAME	=	libmy.a

CSFML_FLAG = -lcsfml-graphics -lcsfml-system -lcsfml-audio -lcsfml-window;

all: $(OUT)

$(OUT): $(OBJS)
	@ $(CC) $(OBJS) -o $(OUT) $(CSFML_FLAG)
	@ echo -e "\033[1;32m$(OUT) successfully created!\033[0m"

clean:
	@ $(RM) $(OBJS) *~ *# *.o *.gc* src/*.gc* src/*.o *.out
	@ echo -e "\033[1;31mAll cleaned!\033[0m"

fclean: clean
	@ rm -f *.gcno
	@ rm -f *.gcda
	@ rm -f libmy.a
	@ $(RM) $(OUT)
	@ echo -e "\033[1;31m$(OUT) (executable) is removed!\033[0m"

re: fclean all

valgrind:
	@ $(CC) $(SOURCE) -o $(OUT) $(CFLAGS) -g3  $(CSFML_FLAG)
	@ echo -e "\033[1;34mRunning valgrind on $(OUT)...\033[0m"
	@ valgrind ./$(OUT)

test:
	@ $(CC) test.c -o $(OUT) $(CFLAGS) -g3  $(CSFML_FLAG)
	@ echo -e "\033[1;34mRunning test version on $(OUT)...\033[0m"
	./$(OUT)
gdb:
	@ $(CC) $(SOURCE) -o $(OUT) $(LFLAGS) $(LDFLAGS) $(CFLAGS) -g3
	@ echo -e "\033[1;34mDebugging $(OUT)...\033[0m"
	@ gdb ./$(OUT)

refresh: re
	@ ./$(OUT)
	@ echo "exit\n"
	@ ./$(OUT)

tests_run:
	@ gcc -o my_tests $(SOURCE) $(SOURCE_TEST) -lcriterion --coverage $(CFLAGS)
	./my_tests

test_print: $(OBJS)
	@ $(CC) $(SOURCE) -o $(OUT) $(LFLAGS) $(LDFLAGS) $(CFLAGS)
	make clean
	@ echo -e "\033[1;34mRunning $(OUT)...\033[0m"

csfml: $(OBJS)
	@ $(CC) main.c $(OBJS) -o $(OUT)
	ar cr $(NAME) $(OBJS)
	@ echo -e "\033[1;32m$(OUT) successfully created!\033[0m"

mango:
	make fclean
	mango
