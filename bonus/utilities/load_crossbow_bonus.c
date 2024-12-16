/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_crossbow_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adesille <adesille@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/06 11:01:27 by adesille          #+#    #+#             */
/*   Updated: 2024/12/16 11:07:32 by adesille         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

static inline void	load_crossbow_aim(t_game *game)
{
	int	i;

	i = -1;
	game->raycast->crossbow_aim[0] = set_texture(game->window,
			"textures/crusade/Crossbow_4.png");
	game->raycast->crossbow_aim[1] = set_texture(game->window,
			"textures/crusade/Crossbow_5.png");
	game->raycast->crossbow_aim[2] = set_texture(game->window,
			"textures/crusade/Crossbow_5.png");
	while (++i < 3)
		mlx_resize_image(game->raycast->crossbow_aim[i], game->resolution[WIDTH]
			/ 2, game->resolution[WIDTH] / 3.5);
	i = -1;
	while (++i < 3)
		display_image(game->window, game->raycast->crossbow_aim[i],
			(t_vector){game->resolution[WIDTH] / 2
			- game->raycast->crossbow_aim[0]->width / 2,
			game->resolution[HEIGHT] - game->resolution[WIDTH] / 3.9});
}

static inline void	load_crossbow_textures_utils(t_game *game)
{
	mlx_resize_image(game->raycast->crossbow_reload[0], game->resolution[WIDTH]
		/ 2, game->resolution[WIDTH] / 4);
	mlx_resize_image(game->raycast->crossbow_reload[1], game->resolution[WIDTH]
		/ 2, game->resolution[WIDTH] / 4);
	display_image(game->window, game->raycast->crossbow_reload[0],
		(t_vector){game->resolution[WIDTH] - game->resolution[WIDTH] / 2,
		game->resolution[HEIGHT] - game->resolution[WIDTH] / 4.5});
	display_image(game->window, game->raycast->crossbow_reload[1],
		(t_vector){game->resolution[WIDTH] - game->resolution[WIDTH] / 2,
		game->resolution[HEIGHT] - game->resolution[WIDTH] / 4.5});
	load_crossbow_aim(game);
}

extern inline void	load_crossbow_textures(t_game *game)
{
	int	i;

	i = -1;
	game->raycast->crossbow[0] = set_texture(game->window,
			"textures/crusade/Crossbow_0.png");
	game->raycast->crossbow[1] = set_texture(game->window,
			"textures/crusade/Crossbow_1.png");
	game->raycast->crossbow[2] = set_texture(game->window,
			"textures/crusade/Crossbow_1.png");
	while (++i < 3)
		mlx_resize_image(game->raycast->crossbow[i], game->resolution[WIDTH]
			/ 2, game->resolution[WIDTH] / 4);
	i = -1;
	while (++i < 3)
		display_image(game->window, game->raycast->crossbow[i],
			(t_vector){game->resolution[WIDTH] - game->resolution[WIDTH] / 2,
			game->resolution[HEIGHT] - game->resolution[WIDTH] / 4.5});
	game->raycast->crossbow_reload[0] = set_texture(game->window,
			"textures/crusade/Crossbow_2.png");
	game->raycast->crossbow_reload[1] = set_texture(game->window,
			"textures/crusade/Crossbow_3.png");
	load_crossbow_textures_utils(game);
}
