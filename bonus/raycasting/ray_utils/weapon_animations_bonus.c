/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   weapon_animations_bonus.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adesille <adesille@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/29 10:45:19 by adesille          #+#    #+#             */
/*   Updated: 2024/12/15 11:51:36 by adesille         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

extern inline void	gun_shoot_animation(t_game *game)
{
	static int	i = 0;
	static int	j = -1;

	if (game->aiming)
		game->raycast->gun_aim[++j]->enabled = FALSE;
	else
		game->raycast->gun[++j]->enabled = FALSE;
	if (i == 3)
	{
		i = 0;
		j = -1;
		if (game->aiming)
			game->raycast->gun_aim[0]->enabled = TRUE;
		else
			game->raycast->gun[0]->enabled = TRUE;
		game->shoot_animation = FALSE;
		return ;
	}
	if (game->aiming)
		game->raycast->gun_aim[++i]->enabled = TRUE;
	else
		game->raycast->gun[++i]->enabled = TRUE;
}

static inline void	reinit_reload_animation(t_game *game, int *i)
{
	*i = -1;
	if (game->aiming)
		game->raycast->gun_aim[0]->enabled = TRUE;
	else
		game->raycast->gun[0]->enabled = TRUE;
	game->reload_animation = FALSE;
}

extern inline void	gun_reload_animation(t_game *game)
{
	static int	i = -1;
	static int	j = 0;

	if (++i < 5)
	{
		game->raycast->gun_reload[j]->enabled = FALSE;
		if (!i && game->aiming)
			game->raycast->gun_aim[0]->enabled = FALSE;
		else if (!i)
			game->raycast->gun[0]->enabled = FALSE;
		if (i == 4)
			reinit_reload_animation(game, &i);
		else if (i == 2 && j)
		{
			game->raycast->gun_reload[--i - 1]->enabled = TRUE;
			j = 0;
		}
		else
		{
			game->raycast->gun_reload[i]->enabled = TRUE;
			j = i;
		}
	}
}

extern inline void	crossbow_shoot_animation(t_game *game)
{
	static int	i = 0;
	static int	j = -1;

	if (game->aiming)
		game->raycast->crossbow_aim[++j]->enabled = FALSE;
	else
		game->raycast->crossbow[++j]->enabled = FALSE;
	if (i == 2)
	{
		i = 0;
		j = -1;
		if (game->aiming)
			game->raycast->crossbow_aim[0]->enabled = TRUE;
		else
			game->raycast->crossbow[0]->enabled = TRUE;
		game->shoot_animation = FALSE;
		return ;
	}
	if (game->aiming)
		game->raycast->crossbow_aim[++i]->enabled = TRUE;
	else
		game->raycast->crossbow[++i]->enabled = TRUE;
}

extern inline void	crossbow_reload_animation(t_game *game)
{
	static int	i = -1;
	static int	j = 0;

	if (++i < 3)
	{
		game->raycast->crossbow_reload[j]->enabled = FALSE;
		if (!i && game->aiming)
			game->raycast->crossbow_aim[0]->enabled = FALSE;
		else if (!i)
			game->raycast->crossbow[0]->enabled = FALSE;
		if (i == 2)
		{
			if (game->aiming)
				game->raycast->crossbow_aim[0]->enabled = TRUE;
			else
				game->raycast->crossbow[0]->enabled = TRUE;
			return (game->reload_animation = FALSE, i = -1, (void)0);
		}
		else if (i == 1 && j)
			return (game->raycast->crossbow_reload[--i]->enabled = TRUE,
				j = 0, (void)0);
		else
			return (game->raycast->crossbow_reload[i]->enabled = TRUE, j = i,
				(void)0);
	}
}
