/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   delete_textures_bonus.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aheitz <aheitz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/08 11:51:17 by adesille          #+#    #+#             */
/*   Updated: 2024/12/12 16:01:21 by aheitz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

extern inline void	delete_crossbow_textures(t_game *game)
{
	mlx_delete_image(game->window, game->raycast->crossbow[0]);
	mlx_delete_image(game->window, game->raycast->crossbow[1]);
	mlx_delete_image(game->window, game->raycast->crossbow_aim[0]);
	mlx_delete_image(game->window, game->raycast->crossbow_aim[1]);
	mlx_delete_image(game->window, game->raycast->crossbow_reload[0]);
	mlx_delete_image(game->window, game->raycast->crossbow_reload[1]);
}

extern inline void	delete_gun_textures(t_game *game)
{
	int	i;

	i = -1;
	while (++i < 3)
		mlx_delete_image(game->window, game->raycast->gun[i]);
	mlx_delete_image(game->window, game->raycast->gun_aim[0]);
	mlx_delete_image(game->window, game->raycast->gun_aim[1]);
	i = -1;
	while (++i < 6)
		mlx_delete_image(game->window, game->raycast->gun_reload[i]);
}

extern inline void	delete_crusade_textures(t_game *game)
{
	int	i;

	i = -1;
	while (++i < 4)
		mlx_delete_image(game->window, game->raycast->crusader1[i]);
	i = -1;
	while (++i < 4)
		mlx_delete_image(game->window, game->raycast->crusader2[i]);
	i = -1;
	while (++i < 4)
		mlx_delete_image(game->window, game->raycast->crusader3[i]);
	mlx_delete_image(game->window, game->raycast->holy_item);
	mlx_delete_image(game->window, game->raycast->crusader_death);
}

extern inline void	delete_brainless_textures(t_game *game)
{
	int	i;

	i = -1;
	while (++i < 4)
		mlx_delete_image(game->window, game->raycast->good_guy[i]);
	mlx_delete_image(game->window, game->raycast->bad_guy[0]);
	mlx_delete_image(game->window, game->raycast->bad_guy[1]);
	mlx_delete_image(game->window, game->raycast->gaspar_item);
}

extern inline void	delete_brainless_intro(t_game *game)
{
	int	i;

	i = -1;
	while (++i < 6)
		mlx_delete_image(game->window, game->start_screen[i]);
}
