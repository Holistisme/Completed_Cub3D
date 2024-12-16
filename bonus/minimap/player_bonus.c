/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adesille <adesille@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 08:59:02 by isb               #+#    #+#             */
/*   Updated: 2024/12/16 08:40:33 by adesille         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

static int	is_wall(t_game *game, uint32_t x, uint32_t y)
{
	int	grid_x;
	int	grid_y;

	grid_x = (int)(x / game->scale->element_width);
	grid_y = (int)(y / game->scale->element_height);
	if (grid_x < 0 || grid_x >= (int)game->scene->width || grid_y < 0
		|| grid_y >= (int)game->scene->height)
		return (1);
	return (game->scene->map[grid_y][grid_x] == '1');
}

void	draw_player_direction_utils(t_game *game, double x_calc, double y_calc)
{
	double	x;
	double	y;
	int		xx;
	int		yy;
	int		i;

	i = -1;
	while (1)
	{
		x = game->scale->pos[X] + x_calc * ++i;
		y = game->scale->pos[Y] + y_calc * i;
		xx = game->compass->width / 2 + x_calc * i;
		yy = game->compass->height / 2 + y_calc * i;
		if (is_wall(game, x, y))
			break ;
		draw_pixel(game, xx, yy, WHITE);
	}
}

void	draw_player_direction(t_game *game, double factor)
{
	double	x_calc;
	double	y_calc;

	factor = game->scale->factor;
	draw_player_direction_utils(game, game->player->direction[X],
		game->player->direction[Y]);
	while (factor > 0.0)
	{
		y_calc = game->player->direction[X] * sin(factor)
			+ game->player->direction[Y] * cos(factor);
		x_calc = game->player->direction[X] * cos(factor)
			- game->player->direction[Y] * sin(factor);
		draw_player_direction_utils(game, x_calc, y_calc);
		factor -= 0.05;
	}
	factor = game->scale->factor;
	while (factor > 0.0)
	{
		y_calc = game->player->direction[X] * sin(-factor)
			+ game->player->direction[Y] * cos(-factor);
		x_calc = game->player->direction[X] * cos(-factor)
			- game->player->direction[Y] * sin(-factor);
		draw_player_direction_utils(game, x_calc, y_calc);
		factor -= 0.05;
	}
}
