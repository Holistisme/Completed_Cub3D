/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_sprites_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adesille <adesille@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/23 13:30:41 by adesille          #+#    #+#             */
/*   Updated: 2024/12/16 10:27:10 by adesille         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

static inline uint32_t	get_texture_pixel(mlx_image_t *texture, int x, int y)
{
	int	offset;

	if (x < 0 || x >= (int)texture->width || y < 0 || y >= (int)texture->height)
		return (0x00000000);
	offset = (y * texture->width + x) * 4;
	return (get_rgba((t_rgba){texture->pixels[offset], texture->pixels[offset
				+ 1], texture->pixels[offset + 2],
			texture->pixels[offset + 3]}));
}

inline uint32_t	damage_colorization(uint32_t color, float percent)
{
	uint8_t	alpha;
	uint8_t	red;
	uint8_t	green;
	uint8_t	blue;
	int		new_alpha;

	alpha = (color >> 24) & 0xFF;
	red = (color >> 16) & 0xFF;
	green = (color >> 8) & 0xFF;
	blue = color & 0xFF;
	new_alpha = alpha + (int)((255 - alpha) * percent / 150.0f);
	if (new_alpha > 255)
		new_alpha = 255;
	return ((new_alpha << 24) | (red << 16) | (green << 8) | blue);
}

static inline void	e_safe_put_pixel(t_game *game, t_sprite *ee,
	int32_t axis[2], int color)
{
	if (axis[X] >= game->resolution[WIDTH]
		|| axis[X] >= (int32_t)game->frame->width
		|| axis[Y] >= game->resolution[HEIGHT]
		|| axis[Y] >= (int32_t)game->frame->height)
		return ;
	if ((*ee).life && !(*ee).dead)
		color = damage_colorization(color, (*ee).life);
	mlx_put_pixel(game->frame, axis[X], axis[Y], color);
}

static inline void	draw_process(t_game *game, t_sprite_cast e, t_sprite *ee,
	int *once)
{
	uint32_t	color;

	if ((e.x > game->resolution[WIDTH] / 2 - 5 && e.x
			+ e.draw_end_x < game->resolution[WIDTH] / 2 + e.draw_end_x)
		&& game->shoot_animation && !*once && !(*ee).dead
		&& (*ee).type != ITEMS)
	{
		if ((*ee).type == GOOD_GUY)
			betrayal_effect(game);
		(*ee).life += 25;
		if ((*ee).life > 100)
			return (set_death(game, ee));
		*once += 42;
	}
	e.tex_x = (e.x - e.draw_start_x) * (*ee).texture->width
		/ e.sprite_width;
	e.tex_y = (e.y - e.draw_start_y) * ((*ee).texture->height)
		/ (e.sprite_height - (*ee).transform_deformation
			- (*ee).hit_deformation);
	color = get_texture_pixel((*ee).texture, e.tex_x, e.tex_y);
	if (color != 0x00000000)
		e_safe_put_pixel(game, ee, (int32_t[2]){e.x, e.y
			+ (*ee).transform_deformation
			+ (*ee).hit_deformation}, color);
	(*ee).is_alive = TRUE;
}

void	draw_sprites(t_game *game, t_sprite_cast e, t_sprite *ee)
{
	int			once;

	once = 0;
	while (++e.x < e.draw_end_x)
	{
		if (e.transform[Y] > 0 && e.x >= 0 && e.x < game->resolution[WIDTH]
			&& e.transform[Y] < game->zbuffer[e.x])
		{
			e.y = e.draw_start_y - 1;
			while (++e.y < e.draw_end_y)
			{
				if (e.y >= 0 && e.y < game->resolution[HEIGHT])
					draw_process(game, e, ee, &once);
			}
		}
	}
}
