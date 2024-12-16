/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap_utils_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adesille <adesille@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/16 11:31:56 by isb               #+#    #+#             */
/*   Updated: 2024/12/16 08:38:41 by adesille         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

uint32_t	which_object(t_game *game, uint32_t y, uint32_t x)
{
	char	c;

	if (y < game->scene->height && x < game->scene->width)
		c = game->scene->map[y][x];
	else
		return (DARK_GREY);
	if (c && c == '0')
		return (get_rgba((t_rgba){189, 158, 114, 255}));
	if (c && c == '1')
		return (WALL_COLOR);
	else
		return (DARK_GREY);
}

void	draw_pixel(t_game *game, uint32_t x, uint32_t y, uint32_t color)
{
	if (x > game->compass->width / 2 - game->compass->width / 3.5
		&& x < game->compass->width / 2 + game->compass->width / 3.5
		&& y > game->compass->height / 2 - game->compass->height / 3.5
		&& y < game->compass->height / 2 + game->compass->height / 3.5)
		mlx_put_pixel(game->minimap, x, y, color);
}
