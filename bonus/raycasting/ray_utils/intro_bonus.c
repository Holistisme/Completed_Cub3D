/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intro_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adesille <adesille@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/05 12:50:47 by adesille          #+#    #+#             */
/*   Updated: 2024/12/14 12:06:38 by adesille         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

void	delete_intro_images(t_game *game)
{
	int	i;

	i = -1;
	while (++i < 6)
		mlx_delete_image(game->window, game->start_screen[i]);
}

void	intro_texture_update(t_game *game, int *i, int *j)
{
	if (!game->screamer_start)
	{
		game->screamer_start = get_time();
		play_sound("murder-scream", 0);
	}
	else if (get_time() - game->screamer_start > 700)
	{
		game->screamer_start = get_time();
		play_sound("murder-scream", 0);
	}
	*i = rand() % (6 - 2 + 1) + 2;
	if (*i > 2 && *i < 6)
	{
		if (*j > 0)
			game->start_screen[*j]->enabled = FALSE;
		game->start_screen[*i]->enabled = TRUE;
		*j = *i;
	}
}

void	intro(t_game *game)
{
	static int	i = -1;
	static int	j = -1;

	if (game->intro && get_time() - game->raycast->start_time > 1500)
		game->start_screen[1]->enabled = FALSE;
	if (game->intro && get_time() - game->raycast->start_time > 2500)
		intro_texture_update(game, &i, &j);
	if (get_time() - game->raycast->start_time > 4000)
	{
		if (game->start_screen[j]->enabled == TRUE)
			game->start_screen[j]->enabled = FALSE;
		game->start_screen[0]->enabled = FALSE;
		game->intro = FALSE;
		delete_intro_images(game);
	}
}

void	display_end_screen(t_game *game)
{
	game->player->dead = TRUE;
	game->end_screen = set_texture(game->window,
			"./textures/brainless/achtung.png");
	mlx_resize_image(game->end_screen, game->resolution[WIDTH],
		game->resolution[HEIGHT]);
	display_image(game->window, game->end_screen, (t_vector){0, 0});
	game->end_screen->enabled = TRUE;
}
