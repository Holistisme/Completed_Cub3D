/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adesille <adesille@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/25 10:27:30 by aheitz            #+#    #+#             */
/*   Updated: 2024/12/16 11:13:43 by adesille         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

static inline void	minimap_put_pixel(t_game *game, t_minimap mini)
{
	int	i;

	i = -1;
	if (mini.y > game->scale->map_height || mini.x > game->scale->map_width)
		mlx_put_pixel(game->minimap, mini.xx, mini.yy, DARK_GREY);
	else if ((!(mini.x % game->scale->element_width) || !(mini.y
				% game->scale->element_height)) && which_object(game, mini.y
			/ game->scale->element_height, mini.x
			/ game->scale->element_width) != DARK_GREY)
		mlx_put_pixel(game->minimap, mini.xx, mini.yy, GREY);
	else
	{
		mlx_put_pixel(game->minimap, mini.xx, mini.yy, which_object(game, mini.y
				/ game->scale->element_height, mini.x
				/ game->scale->element_width));
	}
	while (++i <= game->sprite_count)
		if ((game->sprite[i].type == BAD_GUY1
				|| game->sprite[i].type == BAD_GUY2) && (fabs((double)mini.y
					/ game->scale->element_height
					- game->sprite[i].position[Y]) < 0.1 && fabs((double)mini.x
					/ game->scale->element_width
					- game->sprite[i].position[X]) < 0.1))
			mlx_put_pixel(game->minimap, mini.xx, mini.yy, RED);
}

static inline void	init_minimap(t_game *game, t_minimap *mini)
{
	if (!game->minimap->enabled || !game->compass->enabled
		|| !game->helmet->enabled)
	{
		game->minimap->enabled = TRUE;
		game->compass->enabled = TRUE;
		game->helmet->enabled = TRUE;
	}
	game->scale->pos[X] = game->player->position[X]
		* game->scale->element_width;
	game->scale->pos[Y] = game->player->position[Y]
		* game->scale->element_height;
	(*mini).yy = game->compass->height / 2 - game->compass->height / 3.5;
	(*mini).y = game->scale->pos[Y] - game->compass->height / 3.5;
}

extern inline void	draw_minimap(void *param)
{
	t_minimap	mini;
	t_game		*game;

	mini.xx = 0;
	game = (t_game *)param;
	if (game->state != &raycast)
		return ;
	init_minimap(game, &mini);
	while (mini.yy < game->compass->height / 2 + game->compass->height / 3.5)
	{
		mini.xx = game->compass->width / 2 - game->compass->width / 3.5;
		mini.x = game->scale->pos[X] - game->compass->width / 3.5;
		while (mini.xx < game->compass->width / 2 + game->compass->width / 3.5)
		{
			minimap_put_pixel(game, mini);
			mini.xx++;
			mini.x++;
		}
		mini.yy++;
		mini.y++;
	}
	draw_player_direction(game, game->scale->factor);
}

extern inline void	normalize_data(t_game *game, size_t size_factor, int corner)
{
	game->player->angle = PI;
	game->scale->minimap_size = size_factor;
	game->scale->element_height = size_factor / game->scene->height;
	game->scale->element_width = size_factor / game->scene->height;
	game->scale->pos[X] = game->player->position[0] * game->scale->element_width
		+ game->scale->element_width / 2;
	game->scale->pos[Y] = game->player->position[1]
		* game->scale->element_height + game->scale->element_height / 2;
	game->scale->map_height = game->scene->height * game->scale->element_height;
	game->scale->map_width = game->scene->width * game->scale->element_height;
	game->scale->x_corner = 0;
	game->scale->y_corner = 0;
	if (corner == UP_RIGHT)
		game->scale->x_corner = game->resolution[WIDTH] - game->compass->width;
	else if (corner == DOWN_LEFT)
		game->scale->y_corner = game->resolution[HEIGHT]
			- game->compass->height;
	else if (corner == DOWN_RIGHT)
	{
		game->scale->x_corner = game->resolution[WIDTH] - game->compass->width;
		game->scale->y_corner = game->resolution[HEIGHT]
			- game->compass->height;
	}
}
