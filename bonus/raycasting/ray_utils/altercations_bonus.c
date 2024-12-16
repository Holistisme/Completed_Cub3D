/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   altercations_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adesille <adesille@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/05 12:38:02 by adesille          #+#    #+#             */
/*   Updated: 2024/12/16 10:03:07 by adesille         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

extern inline void	set_death(t_game *game, t_sprite *sprite)
{
	(*sprite).collision_buffer = FALSE;
	(*sprite).hit_deformation = 0;
	(*sprite).hit = FALSE;
	(*sprite).dead = TRUE;
	(*sprite).texture = game->raycast->crusader_death;
	(*sprite).death_time = get_time();
	play_sound(select_death_sound(rand() % 10), 0);
}

static inline void	player_damage(t_game *game)
{
	if (!game->raycast->bleeding_start_time)
		game->raycast->bleeding_start_time = get_time();
	if (get_time() - game->raycast->bleeding_start_time < 50)
	{
		game->raycast->bleeding->enabled = TRUE;
		if (game->settings->difficulty == 3)
			game->player->life += 200;
		else if (game->settings->difficulty == 2)
			game->player->life += rand() % (10 - 1 + 1) + 1;
		else
			game->player->life++;
		if (game->player->life > 80)
			game->dark_mode = TRUE;
	}
	else
		game->raycast->bleeding->enabled = FALSE;
	if (get_time() - game->raycast->bleeding_start_time > 350)
		game->raycast->bleeding_start_time = 0;
}

static inline void	sprites_damage(t_game *game, int i, int j)
{
	game->sprite[j].hit = TRUE;
	if (game->settings->difficulty == 3)
		game->sprite[j].life += 200;
	else if (game->settings->difficulty == 2)
		game->sprite[j].life += rand() % (10 - 1 + 1) + 1;
	else if (game->settings->difficulty == 1)
		game->sprite[j].life += (rand() % (10 - 1 + 1) + 1) / 2;
	if (game->sprite[j].life > 100 && game->sprite[j].life < 120)
		set_death(game, &game->sprite[i]);
}

static inline void	set_collision(t_game *game, int i)
{
	int	j;

	if ((!game->sprite[i].collision_buffer || get_time()
			- game->sprite[i].start_sound > 700)
		&& game->sprite[i].type == GOOD_GUY && game->brainless_mode)
	{
		game->sprite[i].start_sound = get_time();
		play_sound("zgeg2ouf", 0);
	}
	game->sprite[i].collision_buffer = TRUE;
	if (game->sprite[i].type == GOOD_GUY)
		j = set_closest_bad_guy_position(game, i, &(t_double_vector){0, 0});
	else if (game->sprite[i].hit)
		j = set_closest_good_guy_position(game, i, &(t_double_vector){0, 0});
	else
		j = -1;
	if (j != -1)
		sprites_damage(game, i, j);
	else
		player_damage(game);
}

extern inline void	collision_buffer_management(t_game *game, int i,
		t_double_vector position)
{
	if (fabs(game->sprite[i].position[Y] - position[Y]) < 0.25
		&& fabs(game->sprite[i].position[X] - position[X]) < 0.25)
		set_collision(game, i);
	else
	{
		if (position[X] == game->player->position[X]
			&& position[Y] == game->player->position[Y])
			game->raycast->bleeding->enabled = FALSE;
		game->sprite[i].collision_buffer = FALSE;
		game->sprite[i].start_sound = 0;
		game->sprite[i].hit = FALSE;
	}
}
