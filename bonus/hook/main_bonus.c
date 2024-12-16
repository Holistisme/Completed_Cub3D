/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adesille <adesille@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 15:40:59 by aheitz            #+#    #+#             */
/*   Updated: 2024/12/15 12:09:52 by adesille         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* ************************************************************************** */

#include "cub3d_bonus.h"

static inline void		play_music(t_game *game);
static inline void		play_ingame_music(t_game *game);

/* ************************************************************************** */

void	main_hook(void *context)
{
	t_game	*game;

	game = (t_game *)context;
	if (game->restart)
	{
		display_main_menu(game);
		edit_settings(game);
		game->restart = false;
	}
	if (game->state == &raycast || game->state == &introduce
		|| game->state == &display_studio || game->state == &display_endgame)
		game->state(game);
	else if (game->settings->animation)
		change_setting(game, 0);
	else if (game->state == &display_main_menu || game->state == &pause_game)
		aim_menu(game);
	else if (game->state == &edit_settings && !game->settings->animation)
		display_data(game);
	play_ambience(game, SET);
	if (game->state == &raycast)
		play_ingame_music(game);
	if (!enemies_remaining(game) || game->player->life >= 150)
		display_endgame(game);
	play_music(game);
}

static inline void	play_music(t_game *game)
{
	static long	last;
	static long	duration;

	if (!game->music)
	{
		duration = 0;
		game->music = true;
	}
	else if (get_current_time() - last > duration)
	{
		if (game->state == &display_main_menu
			|| game->state == &edit_settings)
		{
			play_sound("main_music", UNDEFINED);
			last = get_current_time();
			duration = 129 * MILLISECOND;
		}
		else if (game->state == &pause_game)
		{
			play_sound("pause_music", UNDEFINED);
			last = get_current_time();
			duration = 279 * MILLISECOND;
		}
	}
}

extern inline void	play_ambience(t_game *game, t_action action)
{
	static long	start;

	if (game->player->life > 80)
		game->dark_mode = true;
	else
		game->dark_mode = false;
	if (game->state != &raycast)
		return ;
	if (action == UNSET)
		start = 0;
	else if (!start || get_current_time() - start >= 360 * MILLISECOND)
	{
		start = get_current_time();
		if (game->scene->environment == JERUSALEM)
			play_sound("jerusalem", UNDEFINED);
		else if (game->scene->environment == HELL)
			play_sound("hell", UNDEFINED);
		else if (game->scene->environment == HEAVEN)
			play_sound("heaven", UNDEFINED);
		else
			play_sound("ambience", UNDEFINED);
	}
}

static inline void	play_ingame_music(t_game *game)
{
	static long	start;
	static long	duration;

	if ((get_current_time() - start < duration) && game->music)
		return ;
	if (game->dark_mode || enemies_remaining(game) < 4)
	{
		start = get_current_time();
		if (game->dark_mode && enemies_remaining(game) < 4)
		{
			play_sound("on_edge", UNDEFINED);
			duration = ON_EDGE;
		}
		else if (game->dark_mode)
		{
			play_sound("dying", UNDEFINED);
			duration = DYING;
		}
		else
		{
			play_sound("winning", UNDEFINED);
			duration = WINNING;
		}
	}
}

inline size_t	enemies_remaining(t_game *game)
{
	t_index	index;
	size_t	enemies;

	index = 0;
	enemies = 12;
	while (index < 36)
	{
		if ((game->sprite[index].type == BAD_GUY1
				|| game->sprite[index].type == BAD_GUY2)
			&& game->sprite[index].dead)
			--enemies;
		++index;
	}
	return (enemies);
}
