/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aheitz <aheitz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/28 14:46:55 by aheitz            #+#    #+#             */
/*   Updated: 2024/12/11 15:47:54 by aheitz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/* ************************************************************************** */

static inline int			get_pixel_color(t_game *game,
								const mlx_image_t *texture);
static inline int			get_texture_pixel_x(t_game *game,
								const mlx_image_t *texture);
static inline mlx_image_t	*get_side_texture(t_game *game);

/* ************************************************************************** */

extern inline void	draw(t_game *game)
{
	mlx_image_t	*texture;

	texture = get_side_texture(game);
	game->raycast.pixel[Y] = 0;
	while (game->raycast.pixel[Y] < game->raycast.draw[START])
		mlx_put_pixel(game->frame, game->raycast.pixel[X],
			game->raycast.pixel[Y]++, game->ceiling);
	game->raycast.pixel[Y] = game->raycast.draw[START];
	game->raycast.wall_y = (game->raycast.draw[START]
			- (HEIGHT_SIZE / 2 - game->raycast.height / 2))
		* (double)texture->height / game->raycast.height;
	while (game->raycast.pixel[Y] < game->raycast.draw[END])
	{
		mlx_put_pixel(game->frame, game->raycast.pixel[X],
			game->raycast.pixel[Y]++, get_pixel_color(game, texture));
		game->raycast.wall_y += (double)texture->height / game->raycast.height;
	}
	while (game->raycast.pixel[Y] < HEIGHT_SIZE)
		mlx_put_pixel(game->frame, game->raycast.pixel[X],
			game->raycast.pixel[Y]++, game->floor);
}

static inline int	get_pixel_color(t_game *game, const mlx_image_t *texture)
{
	t_texture_pixel	texture_pixel;

	texture_pixel[X] = get_texture_pixel_x(game, texture);
	texture_pixel[Y] = (int)game->raycast.wall_y % texture->height;
	texture_pixel[OFFSET]
		= (texture_pixel[Y] * texture->width + texture_pixel[X]) * 4;
	if (texture_pixel[X] < 0 || texture_pixel[X]
		>= (int)texture->width || texture_pixel[Y] < 0
		|| texture_pixel[Y] >= (int)texture->height)
		return (0);
	return (get_rgba((t_rgba){texture->pixels[texture_pixel[OFFSET]],
			texture->pixels[texture_pixel[OFFSET] + 1],
			texture->pixels[texture_pixel[OFFSET] + 2],
			texture->pixels[texture_pixel[OFFSET] + 3]}));
}

static inline int	get_texture_pixel_x(t_game *game,
						const mlx_image_t *texture)
{
	int				texture_x;
	double			wall_x;
	const uint32_t	texture_width = texture->width;
	const double	perpendicular_distance
		= game->raycast.perpendicular_distance;

	if (!game->raycast.x_side)
		wall_x = game->player[POSITION][Y]
			+ perpendicular_distance * game->raycast.ray[Y];
	else
		wall_x = game->player[POSITION][X]
			+ perpendicular_distance * game->raycast.ray[X];
	wall_x -= floor(wall_x);
	texture_x = (int)(wall_x * texture_width);
	if ((!game->raycast.x_side && game->raycast.ray[X] > 0)
		|| (game->raycast.x_side && game->raycast.ray[Y] < 0))
		texture_x = texture_width - texture_x - 1;
	return (texture_x);
}

static inline mlx_image_t	*get_side_texture(t_game *game)
{
	if (game->raycast.x_side)
	{
		if (game->raycast.ray[Y] <= 0)
			return (game->texture[NORTH_SIDE]);
		return (game->texture[SOUTH_SIDE]);
	}
	if (game->raycast.ray[X] <= 0)
		return (game->texture[WEST_SIDE]);
	return (game->texture[EAST_SIDE]);
}

unsigned int	get_rgba(const t_rgba rgba)
{
	return ((rgba[R] << 24) | (rgba[G] << 16) | (rgba[B] << 8) | rgba[A]);
}
