/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update_animations_bonus.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adesille <adesille@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/05 12:47:10 by adesille          #+#    #+#             */
/*   Updated: 2024/12/16 10:28:17 by adesille         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

extern inline void	update_floating_items(t_game *game)
{
	static double	progress = 0.0;

	progress += 0.1;
	if (progress > 2 * PI)
		progress -= 2 * PI;
	game->i_vertical_offset = (int)(game->i_jump_height * sin(progress));
}

extern inline void	update_jump_enemy(t_game *game)
{
	double	progress;

	progress = (double)game->e_jump_frame / game->e_jump_duration;
	game->e_vertical_offset = (int)(game->e_jump_height * sin(progress * PI));
	game->e_jump_frame++;
	if (game->e_jump_frame >= game->e_jump_duration)
	{
		game->e_jump_frame = 0;
		game->e_vertical_offset = 0;
	}
}

extern inline void	betrayal_effect(t_game *game)
{
	play_sound("betrayal", 0);
	game->player->life += 25;
}
