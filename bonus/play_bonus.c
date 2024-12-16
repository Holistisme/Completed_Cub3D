/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   play_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adesille <adesille@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/27 18:07:14 by aheitz            #+#    #+#             */
/*   Updated: 2024/12/15 10:57:53 by adesille         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

// 💬 Initializes the game window and starts the main game loop.
void	play(t_game *game)
{
	initialize_mlx(game);
	hook_init(game);
	if (!game->restart)
	{
		set_achievements(game->legacies->achievement);
		get_achievements(game->legacies->achievement);
		set_introduction_message(game);
	}
	mlx_set_cursor_mode(game->window, MLX_MOUSE_HIDDEN);
	hook_init(game);
	mlx_loop(game->window);
	manage_mlx(NULL);
}
