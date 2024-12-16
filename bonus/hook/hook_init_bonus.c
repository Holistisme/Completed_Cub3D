/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hook_init_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aheitz <aheitz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/07 11:05:16 by adesille          #+#    #+#             */
/*   Updated: 2024/12/12 16:44:03 by aheitz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

void	hook_init(t_game *game)
{
	mlx_key_hook(game->window, &key_hook, game);
	mlx_loop_hook(game->window, movements, game);
	mlx_loop_hook(game->window, draw_minimap, game);
	mlx_cursor_hook(game->window, rotate, game);
	mlx_mouse_hook(game->window, mouse_hook, game);
	mlx_scroll_hook(game->window, scroll_hook, game);
	mlx_loop_hook(game->window, main_hook, game);
}
