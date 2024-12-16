/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_utils_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adesille <adesille@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/06 11:59:11 by adesille          #+#    #+#             */
/*   Updated: 2024/12/15 13:01:46 by adesille         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

static inline int	check_ydoor_validity(t_game *game, int x, int y)
{
	int	yy;

	yy = y;
	while (++yy < y + 4)
	{
		if (game->scene->map[yy][x] != '0')
			return (0);
	}
	yy = y;
	while (--yy > y - 4)
	{
		if (yy >= 0 && game->scene->map[yy][x] != '0')
			return (0);
	}
	return (1);
}

static inline int	check_doors_validity(t_game *game, int x, int y, int token)
{
	int	xx;

	if (y == (int)game->player->position[Y]
		&& x == (int)game->player->position[X])
		return (0);
	if (token == XX)
	{
		xx = x;
		while (++xx < x + 4)
		{
			if (game->scene->map[y][xx] != '0')
				return (0);
		}
		xx = x;
		while (--xx > x - 4)
		{
			if (xx >= 0 && game->scene->map[y][xx] != '0')
				return (0);
		}
	}
	else if (token == YY)
		return (check_ydoor_validity(game, x, y));
	return (1);
}

static inline void	init_doors_data(t_game *game, int y, int x, int *i)
{
	game->scene->map[y][x] = 'D';
	game->doors_cast.pos[++*i][X] = x;
	game->doors_cast.pos[*i][Y] = y;
	game->doors_cast.is_open[*i] = FALSE;
	game->doors_cast.is_close[*i] = TRUE;
}

static inline bool	valid_door_position(t_game *game, int y, int x, int token)
{
	if (token == XX && (y && game->scene->map[y - 1][x] == '1'
		&& (game->scene->map[y][x] == '0' || game->scene->map[y][x] == 'D')
			&& game->scene->map[y + 1][x] == '1'))
		return (TRUE);
	if ((x && game->scene->map[y][x - 1] == '1'
		&& (game->scene->map[y][x] == '0' || game->scene->map[y][x] == 'D')
			&& game->scene->map[y][x + 1] == '1'))
		return (TRUE);
	return (FALSE);
}

extern inline void	draw_doors(t_game *game)
{
	int	x;
	int	y;
	int	i;

	y = -1;
	i = -1;
	while (game->scene->map[++y])
	{
		x = -1;
		while (game->scene->map[y][++x])
		{
			if (valid_door_position(game, y, x, XX))
			{
				if (check_doors_validity(game, x, y, XX))
					init_doors_data(game, y, x, &i);
			}
			else if (valid_door_position(game, y, x, YY))
			{
				if (check_doors_validity(game, x, y, YY))
					init_doors_data(game, y, x, &i);
			}
		}
	}
	game->doors_count = i;
}
