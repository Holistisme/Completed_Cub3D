/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_images_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adesille <adesille@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/07 16:44:01 by aheitz            #+#    #+#             */
/*   Updated: 2024/12/16 09:05:18 by adesille         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

// 💬 Loads the images for mlx and check the value
void	load_images(t_game *game, mlx_image_t **img, int width, int height)
{
	*img = mlx_new_image(game->window, width, height);
	if (!*img)
		terminate("In your hands, even sacred tools wither!");
}

// 💬 Loads the texture from the file and sets it to the image.
mlx_image_t	*set_texture(mlx_t *window, const t_path file)
{
	mlx_image_t		*image;
	mlx_texture_t	*texture;

	texture = mlx_load_png(file);
	if (!texture)
		terminate("The Devil prevented the loading of a texture!");
	image = mlx_texture_to_image(window, texture);
	if (!image)
		terminate("The Devil prevented the loading of an image!");
	mlx_delete_texture(texture);
	image->enabled = false;
	return (image);
}

mlx_image_t	*set_image(t_game *game, const t_path file, t_vector position,
		const bool displayed)
{
	mlx_image_t	*image;

	image = set_texture(game->window, file);
	mlx_resize_image(image, image->width * game->resize, image->height
		* game->resize);
	image->enabled = displayed;
	display_image(game->window, image, position);
	return (image);
}

// 💬 Displays image on window and checks if function doesn't return an error.
void	display_image(mlx_t *window, mlx_image_t *image,
		const t_vector position)
{
	if (mlx_image_to_window(window, image, position[X], position[Y]) == FAILURE)
		terminate("MLX makes you blind, but Jesus can make you see!");
}

extern inline void	set_image_visibility(mlx_instance_t *image, bool reveal)
{
	if (image->enabled != reveal)
		image->enabled = reveal;
}
