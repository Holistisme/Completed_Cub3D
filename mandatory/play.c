/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   play.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aheitz <aheitz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/27 18:07:14 by aheitz            #+#    #+#             */
/*   Updated: 2024/12/16 10:20:30 by aheitz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/* ************************************************************************** */

void	play(t_game *game)
{
	set_memory((void **)&game->raycast, sizeof(t_raycast));
	game->frame = mlx_new_image(game->window, WIDTH_SIZE, HEIGHT_SIZE);
	if (!game->frame)
		terminate("The poor coder is not on the same level as the Creator!");
	if (mlx_image_to_window(game->window, game->frame, 0, 0) == -1)
		terminate("MLX makes you blind, but Jesus can make you see!");
	correct_position(game, game->player[POSITION][Y], game->player[POSITION][X],
		&game->player[POSITION]);
	mlx_key_hook(game->window, &key_hook, game);
	mlx_loop_hook(game->window, &raycast, game);
	mlx_loop(game->window);
	manage_mlx(NULL);
}

extern inline void	correct_position(t_game *game, int y, int x,
						t_double_vector *position)
{
	if (game->map[(int)((float)y + 0.5)][x] != '1'
		&& game->map[(int)((float)y + 0.5)][x] != 'D')
		(*position)[Y] = y + 0.5;
	else if (game->map[(int)((float)y + 0.5)][x] != 'D')
		(*position)[Y] = y - 0.5;
	else
		(*position)[Y] = y;
	if (game->map[y][(int)((float)x + 0.5)] != '1'
		&& game->map[y][(int)((float)x + 0.5)] != 'D')
		(*position)[X] = x + 0.5;
	else if (game->map[y][(int)((float)x + 0.5)] != 'D')
		(*position)[X] = x - 0.5;
	else
		(*position)[X] = x;
}

void	manage_mlx(mlx_t *context)
{
	static mlx_t	*mlx = NULL;

	if (context)
		mlx = context;
	else if (mlx)
	{
		mlx_terminate(mlx);
		mlx = NULL;
	}
}
