/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_colors_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adesille <adesille@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/06 18:19:09 by aheitz            #+#    #+#             */
/*   Updated: 2024/12/16 11:13:53 by adesille         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

/* ************************************************************************** */

extern inline void	draw_sky(t_game *game, t_vector pixel, t_vector draw)
{
	const float	percent = (game->player->life * 100) / 150;
	uint32_t	color;

	if (game->dark_mode)
		color = disco_mode_bro(game->scene->ceiling,
				game->raycast->temperature_shift);
	else
		color = damage_colorization(game->scene->ceiling, percent);
	if (!game->sky)
		while (pixel[Y] < draw[START] + game->vertical_offset)
			safe_put_pixel(game, (int32_t[2]){pixel[X], pixel[Y]++}, color,
				FALSE);
}

extern inline void	draw_floor(t_game *game, t_vector pixel)
{
	const float	percent = (game->player->life * 100) / 150;
	uint32_t	color;

	if (game->dark_mode)
		color = disco_mode_bro(game->scene->floor,
				game->raycast->temperature_shift);
	else
		color = damage_colorization(game->scene->floor, percent);
	if (!game->sky)
		while (pixel[Y] < game->resolution[HEIGHT] + game->vertical_offset)
			safe_put_pixel(game, (int32_t[2]){pixel[X], pixel[Y]++}, color,
				FALSE);
}
