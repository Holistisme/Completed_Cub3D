/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   door_animations_bonus.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adesille <adesille@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/05 13:20:10 by adesille          #+#    #+#             */
/*   Updated: 2024/12/16 11:26:43 by adesille         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

extern inline int	return_door_index(t_game *game, t_vector pos)
{
	int	j;

	j = -1;
	while (++j <= game->doors_count)
	{
		if (game->doors_cast.pos[j][X] == pos[X]
			&& game->doors_cast.pos[j][Y] == pos[Y])
			break ;
	}
	if (j <= game->doors_count)
		return (j);
	return (-1);
}

static inline void	close_door_animation(t_game *game, int j)
{
	static int	i = 8;
	static int	k = 0;

	if (!game->doors_cast.play_audio[j])
	{
		game->doors_cast.play_audio[j] = TRUE;
		play_sound("closing-door", 0);
	}
	if ((++k + 1) % 500)
		return (game->door = game->doors[i], (void)0);
	else
		game->door = game->doors[--i];
	if (!i)
	{
		game->doors_cast.is_open[j] = FALSE;
		game->doors_cast.is_close[j] = TRUE;
		game->doors_cast.play_audio[j] = FALSE;
		i = 8;
		k = 0;
		game->open_door = FALSE;
	}
}

static inline void	open_door_animation(t_game *game, int j)
{
	static int	i = 0;
	static int	k = 0;

	if (!game->doors_cast.play_audio[j])
	{
		game->doors_cast.play_audio[j] = TRUE;
		play_sound("opening-door", 0);
	}
	if ((++k + 1) % 500)
		return (game->door = game->doors[i], (void)0);
	else
		game->door = game->doors[++i];
	if (i == 8)
	{
		game->doors_cast.is_open[j] = TRUE;
		game->doors_cast.is_close[j] = FALSE;
		game->doors_cast.play_audio[j] = FALSE;
		i = 0;
		k = 0;
		game->open_door = FALSE;
	}
}

extern inline void	door_management(t_game *game, int i)
{
	int	j;

	game->door = NULL;
	j = return_door_index(game, (t_vector){game->raycast->door_cast[i].grid[X],
			game->raycast->door_cast[i].grid[Y]});
	if (fabs((double)game->doors_cast.pos[j][X]
		- game->player->position[X]) < 3
		&& fabs((double)game->doors_cast.pos[j][Y]
		- game->player->position[Y]) < 3 && game->open_door)
	{
		if (game->doors_cast.is_close[j])
			open_door_animation(game, j);
		else
			close_door_animation(game, j);
		return ;
	}
	if (game->doors_cast.is_open[j])
		return (game->door = game->doors[8], (void)0);
	if (game->doors_cast.is_close[j])
		return (game->door = game->doors[0], (void)0);
}
