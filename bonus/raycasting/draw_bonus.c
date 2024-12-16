/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adesille <adesille@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/28 14:46:55 by aheitz            #+#    #+#             */
/*   Updated: 2024/12/14 12:39:34 by adesille         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

/* ************************************************************************** */

static inline int			set_draw(t_game *game, const t_index index,
								const size_t wall_height);
static inline int			get_texture_pixel_x(const t_raycast *raycast,
								const t_double_vector ray,
								const t_double_vector player_position,
								const bool horizontal);
static inline mlx_image_t	*get_side_texture(t_game *game,
								const t_double_vector ray,
								const bool horizontal);

/* ************************************************************************** */

// 💬 Draws the wall on the screen.
void	draw(t_game *game, t_raycast *raycast, t_vector pixel,
		const bool is_horizontal)
{
	t_draw		draw;
	float		wall_pixel_y;
	const int	wall_height = game->raycast->height;

	raycast->texture = get_side_texture(game, raycast->ray, is_horizontal);
	draw[START] = set_draw(game, START, wall_height);
	draw[END] = set_draw(game, END, wall_height);
	if (game->raycast->draw_door)
		return (draw_door(game, raycast, draw, pixel), (void)0);
	draw_sky(game, pixel, draw);
	pixel[Y] = draw[START] + game->vertical_offset;
	wall_pixel_y = (draw[START]
			- (game->resolution[HEIGHT] / 2 - wall_height / 2))
		* (float)raycast->texture->height / wall_height;
	while (pixel[Y] < draw[END] + game->vertical_offset)
	{
		safe_put_pixel(game, (int32_t[2]){pixel[X], pixel[Y]++},
			get_pixel_color(raycast, wall_pixel_y, game->player->position,
				raycast->texture), FALSE);
		wall_pixel_y += (float)raycast->texture->height / wall_height;
	}
	draw_floor(game, pixel);
	pixel[Y] = 0;
}

// 💬 Defines the location of the wall to draw.
static inline int	set_draw(t_game *game,
						const t_index index, const size_t wall_height)
{
	int	draw;

	if (index == START)
	{
		draw = game->resolution[HEIGHT] / 2 - wall_height / 2;
		if (draw < 0)
			draw = 0;
	}
	else
	{
		draw = game->resolution[HEIGHT] / 2 + wall_height / 2;
		if (draw >= game->resolution[HEIGHT])
			draw = game->resolution[HEIGHT];
	}
	return (draw);
}

// 💬 Returns the color of the pixel to draw.
inline int	get_pixel_color(t_raycast *raycast, int texture_pixel_y,
		t_double_vector player_position, mlx_image_t *texture)
{
	int	tex_x;
	int	tex_y;
	int	tex_offset;

	if (raycast->draw_door)
		tex_x = get_texture_pixel_x(raycast, raycast->ray, player_position,
				raycast->door_cast[raycast->doors_to_draw].x_side);
	else
		tex_x = get_texture_pixel_x(raycast, raycast->ray, player_position,
				raycast->x_side);
	tex_y = texture_pixel_y % texture->height;
	tex_offset = (tex_y * texture->width + tex_x) * 4;
	return (get_rgba((t_rgba){texture->pixels[tex_offset],
			texture->pixels[tex_offset + 1], texture->pixels[tex_offset + 2],
			texture->pixels[tex_offset + 3]}));
}

// 💬 Returns the x position of the pixel in the texture.
static inline int	get_texture_pixel_x(const t_raycast *raycast,
		const t_double_vector ray, const t_double_vector player_position,
		const bool horizontal)
{
	int			texture_x;
	double		wall_x;
	uint32_t	texture_width;
	double		perpendicular_distance;

	if (raycast->draw_door)
		perpendicular_distance
			= raycast->door_cast[raycast->doors_to_draw].perpendicular_distance;
	else
		perpendicular_distance = raycast->perpendicular_distance;
	texture_width = raycast->texture->width;
	if (!horizontal)
		wall_x = player_position[Y] + perpendicular_distance * ray[Y];
	else
		wall_x = player_position[X] + perpendicular_distance * ray[X];
	wall_x -= floor(wall_x);
	texture_x = (int)(wall_x * texture_width);
	if ((!horizontal && ray[X] > 0) || (horizontal && ray[Y] < 0))
		texture_x = texture_width - texture_x - 1;
	return (texture_x);
}

// 💬 Returns the texture corresponding to the side of the wall.
static inline mlx_image_t	*get_side_texture(t_game *game,
		const t_double_vector ray, const bool horizontal)
{
	if (game->raycast->draw_door)
		return (game->door);
	if (game->set_uni_texture)
		return (game->uni_texture);
	if (horizontal)
	{
		if (ray[Y] <= 0)
			return (game->textures[NORTH_SIDE]);
		return (game->textures[SOUTH_SIDE]);
	}
	if (ray[X] <= 0)
		return (game->textures[WEST_SIDE]);
	return (game->textures[EAST_SIDE]);
}
