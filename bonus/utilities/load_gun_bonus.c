/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_gun_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adesille <adesille@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/06 11:03:44 by adesille          #+#    #+#             */
/*   Updated: 2024/12/15 12:12:39 by adesille         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

static inline void	load_gun_textures_utils(t_game *game)
{
	int	i;

	i = -1;
	game->raycast->gun_reload[0] = set_texture(game->window,
			"textures/crusade/Reload_0.png");
	game->raycast->gun_reload[1] = set_texture(game->window,
			"textures/crusade/Reload_1.png");
	game->raycast->gun_reload[2] = set_texture(game->window,
			"textures/crusade/Reload_3.png");
	game->raycast->gun_reload[3] = set_texture(game->window,
			"textures/crusade/Reload_4.png");
	game->raycast->gun_reload[4] = set_texture(game->window,
			"textures/crusade/Reload_5.png");
	i = -1;
	while (++i < 5)
		mlx_resize_image(game->raycast->gun_reload[i], game->resolution[WIDTH]
			/ 2, game->resolution[WIDTH] / 2);
	i = -1;
	while (++i < 5)
		display_image(game->window, game->raycast->gun_reload[i],
			(t_vector){game->resolution[WIDTH] - game->resolution[WIDTH] / 3,
			game->resolution[HEIGHT] - game->resolution[WIDTH] / 3});
	i = -1;
	while (++i < 5)
		game->raycast->gun_reload[i]->enabled = FALSE;
}

static inline void	load_gun_aim_textures(t_game *game)
{
	int	i;

	i = -1;
	game->raycast->gun_aim[0] = set_texture(game->window,
			"textures/crusade/Gun_aim_0.png");
	game->raycast->gun_aim[1] = set_texture(game->window,
			"textures/crusade/Gun_aim_1.png");
	game->raycast->gun_aim[2] = set_texture(game->window,
			"textures/crusade/Gun_aim_1.png");
	while (++i < 3)
		mlx_resize_image(game->raycast->gun_aim[i], game->resolution[WIDTH] / 2,
			game->resolution[WIDTH] / 2);
	i = -1;
	while (++i < 3)
		display_image(game->window, game->raycast->gun_aim[i],
			(t_vector){game->resolution[WIDTH] / 2
			- game->raycast->gun_aim[0]->width / 2, game->resolution[HEIGHT]
			- game->raycast->gun_aim[0]->height / 1.6});
}

extern inline void	load_gun_textures(t_game *game)
{
	int	i;

	i = -1;
	game->raycast->gun[0] = set_texture(game->window,
			"textures/crusade/Gun_0.png");
	game->raycast->gun[1] = set_texture(game->window,
			"textures/crusade/Gun_1.png");
	game->raycast->gun[2] = set_texture(game->window,
			"textures/crusade/Gun_2.png");
	i = -1;
	while (++i < 3)
		mlx_resize_image(game->raycast->gun[i], game->resolution[WIDTH] / 2,
			game->resolution[WIDTH] / 2);
	i = -1;
	while (++i < 3)
		display_image(game->window, game->raycast->gun[i],
			(t_vector){game->resolution[WIDTH] - game->resolution[WIDTH] / 3,
			game->resolution[HEIGHT] - game->resolution[WIDTH] / 3});
	load_gun_textures_utils(game);
	load_gun_aim_textures(game);
}
