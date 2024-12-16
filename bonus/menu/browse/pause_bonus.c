/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pause_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aheitz <aheitz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/28 12:47:39 by aheitz            #+#    #+#             */
/*   Updated: 2024/12/13 11:39:38 by aheitz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

/* ************************************************************************** */

static inline void	resume_battle(t_game *game);
static inline void	pause_battle(t_game *game);

#define PAUSE_PNG	"./textures/menu/pause.png"

/* ************************************************************************** */

void	pause_game(t_game *game)
{
	if (game->state == &pause_game)
		resume_battle(game);
	else
		pause_battle(game);
}

static inline void	resume_battle(t_game *game)
{
	t_index	index;

	stop_sound();
	game->music = false;
	mlx_delete_image(game->window, game->menu->main);
	mlx_delete_image(game->window, game->menu->button);
	mlx_delete_image(game->window, game->menu->selected_button);
	if (game->menu->blocked_banner)
		mlx_delete_image(game->window, game->menu->blocked_banner);
	index = 0;
	while (index <= 4)
		mlx_delete_image(game->window, game->menu->texts[index++]);
	mlx_delete_image(game->window, game->menu->blur_frame);
	mlx_set_cursor_mode(game->window, MLX_MOUSE_HIDDEN);
	game->state = &raycast;
}

static inline void	pause_battle(t_game *game)
{
	const t_progress	elapsed_time = get_current_time()
		- game->legacies->ingame_start;

	load_images(game, &game->menu->blur_frame,
		game->resolution[WIDTH], game->resolution[HEIGHT]);
	blur_frame(game);
	display_image(game->window, game->menu->blur_frame, (t_vector){0});
	game->menu->main = set_image(game, PAUSE_PNG,
			(t_vector){game->resolution[WIDTH] / 3.1,
			game->resolution[HEIGHT] / 6}, true);
	update_achievement(game->legacies->achievement, PLAY, elapsed_time);
	open_menu(game);
	game->state = &pause_game;
	game->main_menu = game->state;
	mlx_set_mouse_pos(game->window, game->resolution[WIDTH] / 2,
		game->resolution[HEIGHT] / 1.1);
}
