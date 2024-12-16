/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aheitz <aheitz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 10:41:53 by aheitz            #+#    #+#             */
/*   Updated: 2024/12/16 11:13:21 by adesille         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

/* ************************************************************************** */

static inline void	enter_game(t_game *game);
static inline void	browse_main_menu(t_game *game);

#define MAIN_PNG	"./textures/menu/main.png"

/* ************************************************************************** */

void	display_main_menu(t_game *game)
{
	static bool	sprite_init;

	if (!sprite_init)
	{
		init_sprites(game, -1);
		draw_doors(game);
		sprite_init = true;
	}
	if (game->state != &display_main_menu)
		browse_main_menu(game);
	else
		enter_game(game);
}

static inline void	enter_game(t_game *game)
{
	t_index	index;

	stop_sound();
	mlx_delete_image(game->window, game->menu->main);
	mlx_delete_image(game->window, game->menu->button);
	mlx_delete_image(game->window, game->menu->selected_button);
	if (game->menu->blocked_banner)
		mlx_delete_image(game->window, game->menu->blocked_banner);
	index = 0;
	while (index < 5)
		mlx_delete_image(game->window, game->menu->texts[index++]);
	mlx_set_cursor_mode(game->window, MLX_MOUSE_HIDDEN);
	if (game->sky)
	{
		unset_supertextures(game);
		set_supertextures(game);
	}
	correct_position(game, game->player->position[Y], game->player->position[X],
		&game->player->position);
	if (game->settings->difficulty == 1)
		play_sound("Haha-Loser", 0);
	game->raycast->start_time = get_time();
	game->state = &raycast;
}

static inline void	browse_main_menu(t_game *game)
{
	game->state = &display_main_menu;
	game->main_menu = game->state;
	game->menu->main = set_image(game, MAIN_PNG, (t_vector){0}, true);
	open_menu(game);
	mlx_set_mouse_pos(game->window, game->resolution[WIDTH] / 2,
		game->resolution[HEIGHT] / 1.3);
}
