/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   zoom_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adesille <adesille@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/16 11:31:56 by isb               #+#    #+#             */
/*   Updated: 2024/12/16 09:01:03 by adesille         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

static float	zoom_scale(keys_t key)
{
	if (key == MLX_KEY_KP_SUBTRACT || key == MLX_KEY_MINUS)
		return (0.9);
	return (1.1);
}

void	manage_compass_zoom(t_game *game, keys_t key)
{
	if (game->scale->compass_width * zoom_scale(key) > game->resolution[WIDTH]
		|| game->scale->compass_heigth
		* zoom_scale(key) > game->resolution[HEIGHT]
		|| game->scale->compass_width * zoom_scale(key) < 50
		|| game->scale->compass_heigth * zoom_scale(key) < 50)
		return ;
	mlx_delete_image(game->window, game->compass);
	mlx_delete_image(game->window, game->minimap);
	mlx_delete_image(game->window, game->helmet);
	game->scale->compass_width *= zoom_scale(key);
	game->scale->compass_heigth *= zoom_scale(key);
	game->minimap = mlx_new_image(game->window, game->resolution[WIDTH],
			game->resolution[HEIGHT]);
	mlx_image_to_window(game->window, game->minimap, 0, 0);
	game->compass = set_image2(game, "./textures/compass2.png",
			(t_vector){game->scale->compass_width, game->scale->compass_heigth},
			TRUE);
	game->helmet = set_image2(game, "./textures/helmet.png", (t_vector){30, 30},
			TRUE);
	change_corner(game, which_corner(game->scale->corner));
}

void	manage_zoom(t_game *game, keys_t key)
{
	if ((((game->scale->minimap_size * zoom_scale(key)) / game->scene->height)
			* game->scene->width) < game->resolution[WIDTH])
	{
		if (game->scale->minimap_size * zoom_scale(key) > 30)
			game->scale->minimap_size *= zoom_scale(key);
		normalize_data(game, game->scale->minimap_size, game->scale->corner);
		mlx_delete_image(game->window, game->minimap);
		mlx_delete_image(game->window, game->helmet);
		mlx_delete_image(game->window, game->compass);
		game->minimap = mlx_new_image(game->window, game->resolution[WIDTH],
				game->resolution[HEIGHT]);
		display_image(game->window, game->minimap, (t_vector){0, 0});
		game->compass = set_image2(game, "./textures/compass2.png",
				(t_vector){game->scale->compass_width,
				game->scale->compass_heigth}, TRUE);
		game->helmet = set_image2(game, "./textures/helmet.png", (t_vector){30,
				30}, TRUE);
		change_corner(game, which_corner(game->scale->corner));
	}
}
