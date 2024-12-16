/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_textures_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adesille <adesille@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/23 13:35:30 by adesille          #+#    #+#             */
/*   Updated: 2024/12/16 11:00:33 by adesille         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

extern inline mlx_image_t	*set_image2(t_game *game, const t_path file,
		t_vector size, const bool displayed)
{
	mlx_image_t	*image;

	image = set_texture(game->window, file);
	mlx_resize_image(image, size[X], size[Y]);
	image->enabled = displayed;
	display_image(game->window, image, (t_vector){0, 0});
	return (image);
}

static inline void	load_wall_textures(t_game *game)
{
	game->textures[0] = set_texture(game->window, game->scene->textures->north);
	game->textures[1] = set_texture(game->window, game->scene->textures->south);
	game->textures[2] = set_texture(game->window, game->scene->textures->west);
	game->textures[3] = set_texture(game->window, game->scene->textures->east);
	game->uni_texture = set_texture(game->window, "textures/castle.png");
}

static inline void	load_doors_textures(t_game *game)
{
	game->doors[0] = set_texture(game->window, "textures/door_0.png");
	game->doors[1] = set_texture(game->window, "textures/door_1.png");
	game->doors[2] = set_texture(game->window, "textures/door_2.png");
	game->doors[3] = set_texture(game->window, "textures/door_3.png");
	game->doors[4] = set_texture(game->window, "textures/door_4.png");
	game->doors[5] = set_texture(game->window, "textures/door_5.png");
	game->doors[6] = set_texture(game->window, "textures/door_6.png");
	game->doors[7] = set_texture(game->window, "textures/door_7.png");
	game->doors[8] = set_texture(game->window, "textures/door_8.png");
}

static inline void	load_bleeding_texture(t_game *game)
{
	game->raycast->bleeding = set_texture(game->window,
			"textures/crusade/bleeding.png");
	mlx_resize_image(game->raycast->bleeding, game->resolution[WIDTH],
		game->resolution[WIDTH]);
	display_image(game->window, game->raycast->bleeding, (t_vector){0, 0});
	game->raycast->bleeding->enabled = FALSE;
}

// 💬 Loads the textures from the scene and sets them to the game.
extern inline void	load_textures(t_game *game)
{
	load_wall_textures(game);
	load_doors_textures(game);
	load_bleeding_texture(game);
	if (game->brainless_mode)
		load_brainless_textures(game);
	else
		load_crusade_textures(game);
	load_crossbow_textures(game);
	game->scale->compass_heigth = game->resolution[WIDTH] / 5;
	game->scale->compass_width = game->resolution[WIDTH] / 5;
	game->compass = set_image2(game, "./textures/compass2.png",
			(t_vector){game->resolution[WIDTH] / 5, game->resolution[WIDTH]
			/ 5}, FALSE);
	game->helmet = set_image2(game, "./textures/helmet.png", (t_vector){30, 30},
			FALSE);
	change_corner(game, which_corner(game->scale->corner));
}
