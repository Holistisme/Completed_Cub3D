/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colors_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adesille <adesille@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/21 11:19:08 by isb               #+#    #+#             */
/*   Updated: 2024/12/13 09:53:31 by adesille         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

inline uint32_t	disco_mode_bro(uint32_t color, float percent)
{
	uint8_t	rgba[4];
	int		new_rgba[4];

	rgba[A] = (color >> 24) & 0xFF;
	rgba[R] = (color >> 16) & 0xFF;
	rgba[G] = (color >> 8) & 0xFF;
	rgba[B] = color & 0xFF;
	if (percent < 50)
		new_rgba[R] = rgba[R] + (int)((255 - rgba[R]) * percent / 100.0f);
	else
		new_rgba[R] = rgba[R] + (int)((rgba[R]) * percent / 100.0f);
	new_rgba[G] = rgba[G] - (int)(rgba[G] * percent / 100.0f);
	new_rgba[B] = rgba[B] - (int)(rgba[B] * percent / 100.0f);
	new_rgba[A] = rgba[A];
	if (percent > 0)
	{
		new_rgba[A] = rgba[A] + (int)((255 - rgba[A]) * percent / 150.0f);
		if (new_rgba[A] > 255)
			new_rgba[A] = 255;
	}
	return ((new_rgba[A] << 24) | (new_rgba[R] << 16) | (new_rgba[G] << 8)
		| new_rgba[B]);
}

void	safe_put_pixel(t_game *game, int32_t pos[2], int color, bool is_door)
{
	if (pos[X] >= game->resolution[WIDTH]
		|| pos[X] >= (int32_t)game->frame->width
		|| pos[Y] >= game->resolution[HEIGHT]
		|| pos[Y] >= (int32_t)game->frame->height)
		return ;
	if (color == 0x00000000 && is_door)
		return ;
	if (color == 0x00000000)
		color = game->scene->ceiling;
	if (game->dark_mode)
		color = disco_mode_bro(color, game->raycast->temperature_shift);
	if (game->player->life)
		color = damage_colorization(color, game->player->life);
	mlx_put_pixel(game->frame, pos[X], pos[Y], color);
}
