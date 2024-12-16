/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   subtitle_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aheitz <aheitz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/03 09:57:11 by aheitz            #+#    #+#             */
/*   Updated: 2024/12/12 16:04:51 by aheitz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

/* ************************************************************************** */

static inline void	write_letter(t_game *game, const char c, t_position vector,
						t_position *previous);

/* ************************************************************************** */

// 💬 Writes a character on the window at the specified position.
extern inline void	write_subtitle(t_game *game, const char c)
{
	if (!game || game->state != &introduce)
		return ;
	if (!*game->intro_vector)
	{
		game->intro_vector[X] = game->parchment->instances->x
			+ game->parchment->width * 0.06;
		game->intro_vector[Y] = game->parchment->instances->y
			+ game->parchment->height * 0.17;
	}
	if (!*game->intro_prev)
	{
		game->intro_prev[X] = game->intro_vector[X];
		game->intro_prev[Y] = game->intro_vector[Y];
	}
	write_letter(game, c, game->intro_vector, &game->intro_prev);
}

static inline void	write_letter(t_game *game, const char c, t_position vector,
						t_position *previous)
{
	if (!c || c == NEWLINE)
	{
		(*previous)[X] = vector[X];
		if (!c)
			(*previous)[Y] = vector[Y];
		else
			(*previous)[Y] += 16 * game->speed;
	}
	else if (c == SPACE)
		(*previous)[X] += 8 * game->speed;
	else
		(*previous)[X] += write_on_windows(game, c,
				(t_vector){(*previous)[X], (*previous)[Y]});
}
