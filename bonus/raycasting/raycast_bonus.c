/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adesille <adesille@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 11:49:10 by adesille          #+#    #+#             */
/*   Updated: 2024/12/16 11:14:25 by adesille         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

void	draw_crosshair(t_game *game)
{
	int	x;
	int	y;

	x = game->resolution[WIDTH] / 2 - 20;
	y = game->resolution[HEIGHT] / 2 - 20;
	while (y < game->resolution[HEIGHT] / 2 + 20)
	{
		mlx_put_pixel(game->frame, x + 21, y, WHITE);
		mlx_put_pixel(game->frame, x + 20, y, WHITE);
		mlx_put_pixel(game->frame, x + 19, y, WHITE);
		y += 2;
	}
	while (x < game->resolution[WIDTH] / 2 + 20)
	{
		mlx_put_pixel(game->frame, x, y - 21, WHITE);
		mlx_put_pixel(game->frame, x, y - 20, WHITE);
		mlx_put_pixel(game->frame, x, y - 19, WHITE);
		x += 2;
	}
}

void	manage_animations_n_textures(t_game *game)
{
	if (!game->gun_cheat_code && !game->shoot_animation && !game->aiming
		&& !game->reload_animation)
		game->raycast->crossbow[0]->enabled = TRUE;
	else if (game->gun_cheat_code && !game->shoot_animation && !game->aiming
		&& !game->reload_animation)
		game->raycast->gun[0]->enabled = TRUE;
	set_game_textures(game);
	if (game->shoot_animation && !game->gun_cheat_code)
		crossbow_shoot_animation(game);
	if (game->reload_animation && !game->gun_cheat_code)
		crossbow_reload_animation(game);
	if (game->shoot_animation && game->gun_cheat_code)
		gun_shoot_animation(game);
	if (game->reload_animation && game->gun_cheat_code)
		gun_reload_animation(game);
	if (game->dark_mode)
		game->raycast->temperature_shift = rand() % (80 - 40 + 1) + 40;
	update_jump(game);
}

void	do_raycast(t_game *game, t_data_cast *d)
{
	int	i;

	calculate_ray_n_delta_dist(game, d);
	determine_step_n_side_dist(game, d);
	do_dda(game, d);
	calculate_wall_height(game, d, game->raycast);
	draw(game, game->raycast, game->raycast->pixel, game->raycast->x_side);
	if (game->raycast->door)
	{
		i = game->raycast->doors_to_draw;
		while (--i >= 0)
		{
			door_management(game, i);
			calculate_door_height(game, &game->raycast->door_cast[i]);
			game->raycast->doors_to_draw = i;
			draw(game, game->raycast, game->raycast->pixel,
				game->raycast->door_cast[i].x_side);
		}
		game->raycast->draw_door = FALSE;
		game->raycast->door = FALSE;
		game->raycast->doors_to_draw = 0;
	}
	game->raycast->pixel[X]++;
}

void	raycast(t_game *game)
{
	t_data_cast		d;
	static double	time = 0;

	if (!game->legacies->ingame_start)
		game->legacies->ingame_start = get_current_time();
	if (game->intro)
		return (intro(game));
	if (time > 0.0 && game->player->life != 150)
	{
		manage_animations_n_textures(game);
		d.i = 0;
		if (game->sky)
		{
			display_sky(game);
			display_floor(game);
		}
		game->raycast->pixel[X] = 0;
		while (game->raycast->pixel[X] < game->resolution[WIDTH])
			do_raycast(game, &d);
		cast_sprites(game);
		if (!game->aiming)
			draw_crosshair(game);
	}
	time += game->window->delta_time;
}
