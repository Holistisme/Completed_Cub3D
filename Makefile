# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: aheitz <aheitz@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/09/18 11:29:29 by aheitz            #+#    #+#              #
#    Updated: 2024/12/16 11:29:27 by aheitz           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		= cub3D
MAKEFLAGS	+= --no-print-directory
CFLAGS		+= -Wall -Wextra -Wunreachable-code -g3 -MP -MD -Ofast -march=native -mtune=native

INCLUDE		= -I ./mandatory/includes -I ./bonus/includes -I $(LIBDIR)/include/MLX42

LIBDIR		= ./MLX42
LIBMLX		= $(LIBDIR)/build/libmlx42.a
MLX			= $(LIBDIR)/build/libmlx42.a -ldl -lglfw -pthread -lm

HIDE_CURSOR		= \033[?25l
SHOW_CURSOR		= \033[?25h
CYAN			= \033[36m
RESET			= \033[0m
CARRIAGE_RETURN	= \r

MANDATORY	= ./mandatory
RAYCASTING	= $(MANDATORY)/raycasting
SCENE		= $(MANDATORY)/scene
UTILITIES	= $(MANDATORY)/utilities

BONUS				= ./bonus
BONUS_DATA			= $(BONUS)/data
BONUS_HOOK			= $(BONUS)/hook
BONUS_INTRODUCTION	= $(BONUS)/introduction
BONUS_MENU			= $(BONUS)/menu
BONUS_BROWSE		= $(BONUS_MENU)/browse
BONUS_LEGACIES		= $(BONUS_MENU)/legacies
BONUS_RELOADING		= $(BONUS_MENU)/reloading
BONUS_SETTINGS		= $(BONUS_MENU)/settings
BONUS_MINIMAP		= $(BONUS)/minimap
BONUS_RAYCASTING	= $(BONUS)/raycasting
BONUS_RAY_UTILS		= $(BONUS)/raycasting/ray_utils
BONUS_SCENE			= $(BONUS)/scene
BONUS_SUPERTEXTURES	= $(BONUS)/supertextures
BONUS_UTILITIES		= $(BONUS)/utilities

BUILD = build

HEADERS =	./mandatory/includes/cub3d.h		\
			./mandatory/includes/defines.h		\
			./mandatory/includes/functions.h	\
			./mandatory/includes/typedefs.h		\
			./bonus/includes/defines_bonus.h	\
			./bonus/includes/defines_bonus.h	\
			./bonus/includes/functions_bonus.h	\
			./bonus/includes/typedefs_bonus.h	\

SOURCES	=	$(MANDATORY)/main.c		\
			$(MANDATORY)/hooks.c	\
			$(MANDATORY)/memory.c	\
			$(MANDATORY)/play.c		\
									\
			$(RAYCASTING)/draw.c	\
			$(RAYCASTING)/raycast.c	\
									\
			$(SCENE)/map.c			\
			$(SCENE)/read.c			\
			$(SCENE)/set.c			\
			$(SCENE)/textures.c		\
									\
			$(UTILITIES)/spaces.c	\
			$(UTILITIES)/strings.c	\
			$(UTILITIES)/write.c	\

BONUS_SOURCES	=	$(BONUS)/main_bonus.c							\
					$(BONUS)/file_bonus.c							\
					$(BONUS)/initialize_mlx_bonus.c					\
					$(BONUS)/memory_bonus.c							\
					$(BONUS)/play_bonus.c							\
					$(BONUS)/sound_bonus.c							\
					$(BONUS)/terminate_bonus.c						\
					$(BONUS)/time_bonus.c							\
					$(BONUS)/initialization_bonus.c					\
					$(BONUS)/init_utils_bonus.c						\
					$(BONUS)/init_datas_bonus.c						\
																	\
					$(BONUS_DATA)/key_bonus.c						\
					$(BONUS_DATA)/manage_binaries_bonus.c			\
																	\
					$(BONUS_HOOK)/hook_init_bonus.c					\
					$(BONUS_HOOK)/end_game_bonus.c					\
					$(BONUS_HOOK)/key_bonus.c						\
					$(BONUS_HOOK)/main_bonus.c						\
					$(BONUS_HOOK)/menu_aiming_bonus.c				\
					$(BONUS_HOOK)/mouse_bonus.c						\
					$(BONUS_HOOK)/movements_bonus.c					\
					$(BONUS_HOOK)/rotate_bonus.c					\
					$(BONUS_HOOK)/scroll_bonus.c					\
					$(BONUS_HOOK)/hook_utils_bonus.c				\
					$(BONUS_HOOK)/manage_animations_bonus.c			\
					$(BONUS_HOOK)/zoom_bonus.c						\
					$(BONUS_HOOK)/movements_utils_bonus.c			\
					$(BONUS_HOOK)/change_corner_bonus.c				\
																	\
					$(BONUS_INTRODUCTION)/audiovisual_bonus.c		\
					$(BONUS_INTRODUCTION)/fade_bonus.c				\
					$(BONUS_INTRODUCTION)/hook_bonus.c				\
					$(BONUS_INTRODUCTION)/studio_bonus.c			\
					$(BONUS_INTRODUCTION)/subtitle_bonus.c			\
																	\
					$(BONUS_BROWSE)/blur_bonus.c					\
					$(BONUS_BROWSE)/button_bonus.c					\
					$(BONUS_BROWSE)/main_bonus.c					\
					$(BONUS_BROWSE)/menu_bonus.c					\
					$(BONUS_BROWSE)/pause_bonus.c					\
																	\
					$(BONUS_LEGACIES)/achievements_bonus.c			\
					$(BONUS_LEGACIES)/gauge_bonus.c					\
					$(BONUS_LEGACIES)/main_bonus.c					\
					$(BONUS_LEGACIES)/save_bonus.c					\
																	\
					$(BONUS_RELOADING)/deserialize_scene_bonus.c	\
					$(BONUS_RELOADING)/main_bonus.c					\
					$(BONUS_RELOADING)/serialize_scene_bonus.c		\
					$(BONUS_RELOADING)/sprite_bonus.c				\
																	\
					$(BONUS_SETTINGS)/animation_bonus.c				\
					$(BONUS_SETTINGS)/handle_bonus.c				\
					$(BONUS_SETTINGS)/main_bonus.c					\
					$(BONUS_SETTINGS)/save_bonus.c					\
					$(BONUS_SETTINGS)/set_bonus.c					\
																	\
					$(BONUS_MINIMAP)/minimap_utils_bonus.c			\
					$(BONUS_MINIMAP)/minimap_bonus.c				\
					$(BONUS_MINIMAP)/player_bonus.c					\
																	\
					$(BONUS_RAYCASTING)/draw_colors_bonus.c			\
					$(BONUS_RAYCASTING)/raycast_bonus.c				\
					$(BONUS_RAYCASTING)/draw_bonus.c				\
					$(BONUS_RAYCASTING)/ray_calculations_bonus.c	\
					$(BONUS_RAYCASTING)/sprites_bonus.c				\
					$(BONUS_RAYCASTING)/sprites_animations_bonus.c	\
					$(BONUS_RAYCASTING)/draw_sprites_bonus.c		\
					$(BONUS_RAYCASTING)/colors_bonus.c				\
					$(BONUS_RAYCASTING)/doors_bonus.c				\
					$(BONUS_RAYCASTING)/door_animations_bonus.c		\
																	\
					$(BONUS_RAY_UTILS)/movements_bonus.c			\
					$(BONUS_RAY_UTILS)/movements_utils_bonus.c		\
					$(BONUS_RAY_UTILS)/altercations_bonus.c			\
					$(BONUS_RAY_UTILS)/intro_bonus.c				\
					$(BONUS_RAY_UTILS)/return_x_pos_bonus.c			\
					$(BONUS_RAY_UTILS)/update_sprites_bonus.c		\
					$(BONUS_RAY_UTILS)/update_animations_bonus.c	\
					$(BONUS_RAY_UTILS)/change_texture_bonus.c		\
					$(BONUS_RAY_UTILS)/weapon_animations_bonus.c	\
																	\
					$(BONUS_SCENE)/map_bonus.c						\
					$(BONUS_SCENE)/read_bonus.c						\
					$(BONUS_SCENE)/set_bonus.c						\
					$(BONUS_SCENE)/textures_bonus.c					\
																	\
					$(BONUS_SUPERTEXTURES)/set_bonus.c				\
					$(BONUS_SUPERTEXTURES)/display_bonus.c			\
																	\
					$(BONUS_UTILITIES)/mlx_images_bonus.c			\
					$(BONUS_UTILITIES)/rgba_bonus.c					\
					$(BONUS_UTILITIES)/spaces_bonus.c				\
					$(BONUS_UTILITIES)/string_handling_bonus.c		\
					$(BONUS_UTILITIES)/string_scanning_bonus.c		\
					$(BONUS_UTILITIES)/mlx_textures_bonus.c			\
					$(BONUS_UTILITIES)/load_crossbow_bonus.c		\
					$(BONUS_UTILITIES)/load_gun_bonus.c				\
					$(BONUS_UTILITIES)/load_brainless_bonus.c		\
					$(BONUS_UTILITIES)/load_crusaders_bonus.c		\
					$(BONUS_UTILITIES)/delete_textures_bonus.c		\
					$(BONUS_UTILITIES)/write_bonus.c				\

MANDATORY_OBJECTS	= $(patsubst %.c,$(BUILD)/%.o,$(SOURCES))
OBJECTS				= $(patsubst %.c,$(BUILD)/%.o,$(BONUS_SOURCES))
DEPFILES			= $(patsubst %.c,$(BUILD)/%.o.d,$(BONUS_SOURCES))

OBJS_MANDATORY_SUBDIRECTORIES =	$(BUILD)/$(MANDATORY)				\
								$(BUILD)/$(MANDATORY_RAYCASTING)	\
								$(BUILD)/$(MANDATORY_SCENE)			\
								$(BUILD)/$(MANDATORY_UTILITIES)		\

OBJECTS_SUBDIRECTORIES =	$(OBJECTS)/$(BONUS)					\
							$(OBJECTS)/$(BONUS_DATA)			\
							$(OBJECTS)/$(BONUS_HOOK)			\
							$(OBJECTS)/$(BONUS_INTRODUCTION)	\
							$(OBJECTS)/$(BONUS_MENU)			\
							$(OBJECTS)/$(BONUS_BROWSE)			\
							$(OBJECTS)/$(BONUS_LEGACIES)		\
							$(OBJECTS)/$(BONUS_RELOADING)		\
							$(OBJECTS)/$(BONUS_SETTINGS)		\
							$(OBJECTS)/$(BONUS_MINIMAP)			\
							$(OBJECTS)/$(BONUS_SCENE)			\
							$(OBJECTS)/$(BONUS_SUPERTEXTURES)	\
							$(OBJECTS)/$(BONUS_RAYCASTING)		\
							$(OBJECTS)/$(BONUS_RAY_UTILS)		\
							$(OBJECTS)/$(BONUS_UTILITIES)

all: INSTRUCTION=1
all: set_instruction $(LIBMLX) $(NAME)
	@rm -f "./.instruction.log"
	@make display_project

bonus: INSTRUCTION=2
bonus: set_instruction $(LIBMLX) $(OBJECTS)
	@$(CC) $(CFLAGS) $(OBJECTS) $(MLX) $(INCLUDE) -o $(NAME)
	@rm -f "./.instruction.log"
	@make display_project

clean: INSTRUCTION=3
clean: set_instruction
	@find $(BUILD) -type f 2>/dev/null | while read -r FILE; do				\
		rm -f "$$FILE";														\
		COMPILED_FILES=$$(find $(BUILD) -type f -name "*.o" | wc -l);		\
		bash ./.scripts/.progress.sh $(TOTAL_FILES) $$COMPILED_FILES;		\
	done
	@rm -f "./.instruction.log"
	@rm -rf $(BUILD)
	@if [ -d $(LIBDIR)/build ]; then										\
		find $(LIBDIR)/build -type f ! -name "libmlx42.a" -exec rm -f {} +;	\
		find $(LIBDIR)/build -type d -empty -delete;						\
	fi

disco:
	@bash ./.scripts/.disco.sh

display_project:
	@bash ./.scripts/.cub3d.sh
	@bash ./.scripts/.frame.sh
	@bash ./.scripts/.warnings.sh

fclean: clean
	@rm -f $(NAME)
	@rm -f $(LIBMLX)
	@rm -rf $(DEPFILES)

re:
	@make fclean
	@make set_instruction
	@make all

set_instruction:
	@echo $(INSTRUCTION) > "./.instruction.log"

$(BUILD)/%.o: %.c $(HEADERS)
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAGS) -c -o $@ $< $(INCLUDE) 2>>"./.warnings.log" || exit 1
	@bash ./.scripts/.progress.sh

$(LIBMLX):
	@git submodule update --init --recursive
	@printf "$(HIDE_CURSOR)"
	@bash -c '																				\
		making() {																			\
			local pid=$$!;																	\
			local sequence="\|/-\\";														\
			while [ -d /proc/$$pid ]; do													\
				local previous=$${sequence#?};												\
				printf "[%c] Building $(CYAN)MLX$(RESET)..." "$${sequence%"$previous"}";	\
				sequence=$$previous"$${sequence%"$previous"}";								\
				sleep 0.1;																	\
				printf "$(CARRIAGE_RETURN)";												\
			done;																			\
		};																					\
		(cmake $(LIBDIR) -B $(LIBDIR)/build > /dev/null && make -C $(LIBDIR)/build -j4 > /dev/null) & making;'
	@printf "$(SHOW_CURSOR)"

$(NAME): $(MANDATORY_OBJECTS)
	@$(CC) $(CFLAGS) $(MANDATORY_OBJECTS) $(MLX) $(INCLUDE) -o $(NAME)
	
-include $(DEPFILES)

.PHONY: all bonus clean display_project disco fclean re set_instruction

git:
	@git add .
	@git commit -m "$(shell date +"%Y-%m-%d %H:%M:%S")'s commit"
	@git push

valgrind: all
	@printf "$(HIDE_CURSOR)"
	@printf "$(ERASE_LINE)$(NEWLINE)$(BLUE)[🔍] choose your map :$(NEWLINE)1 = jerusalem$(NEWLINE)2 = test$(NEWLINE)> $(RESET) ";																			\
	read -r args;																																						\
	sleep $$(echo "2 * $(SLEEP_FACTOR)" | bc);																															\
	valgrind --leak-check=full --show-leak-kinds=all --suppressions=.valgrind.supp --track-origins=yes ./$(NAME) $$args;												\
	printf "$(BLUE)[🔍] Valgrind has finished running!$(RESET)$(NEWLINE)";																								\
	sleep $$(echo "1 * $(SLEEP_FACTOR)" | bc);																															\
	printf "Leaks summary cane$(GREEN)only$(RESET) tolerate $(RED)317,955$(RESET) bytes suppressed in $(RED)3,107$(RESET) blocks with $(PURPLE)MLX$(RESET)!$(NEWLINE)";	\
	printf "$(SHOW_CURSOR)"

x:	
	@make
	./cub3D maps/jerusalem.cub