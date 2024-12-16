/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   end_game_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aheitz <aheitz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/14 13:05:54 by aheitz            #+#    #+#             */
/*   Updated: 2024/12/14 15:58:35 by aheitz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

/* ************************************************************************** */

#define VICTORY	"./textures/victory.png"
#define DEFEAT	"./textures/defeat.png"

/* ************************************************************************** */

void	display_endgame(t_game *game)
{
	static bool	displaying;
	static long	start;

	game->state = &display_endgame;
	if (!displaying)
	{
		start = get_current_time();
		if (!enemies_remaining(game))
			set_image(game, VICTORY, (t_vector){0}, true);
		else
			set_image(game, DEFEAT, (t_vector){0}, true);
		displaying = true;
	}
	if (get_current_time() - start >= 7 * MILLISECOND)
	{
		stop_sound();
		manage_mlx(NULL);
		set_memory(NULL, 0);
		exit(EXIT_SUCCESS);
	}
}
