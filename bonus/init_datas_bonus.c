/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_datas_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adesille <adesille@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/14 12:13:01 by adesille          #+#    #+#             */
/*   Updated: 2024/12/15 10:40:08 by adesille         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

static inline void	init_struct_variables_utils(t_game *game)
{
	int	x;
	int	y;

	x = game->player->position[X];
	y = game->player->position[Y];
	game->i_jump_frame = 0;
	game->scale->minimap_size = game->resolution[WIDTH] / 5;
	game->scale->factor = PI / 3 - 0.2;
	game->player->life = 0;
	game->scene->map[y][x] = '0';
	game->transformation = FALSE;
	game->intro = FALSE;
	game->player->blue_cord_collected = 0;
	game->player->dead = FALSE;
	game->shoot_animation = FALSE;
	game->aiming = FALSE;
	game->gun_cheat_code = FALSE;
	game->bullets = 0;
	game->max_bullets = 5;
	game->screamer_start = 0;
}

extern inline void	init_struct_variables(t_game *game)
{
	game->crusader_mode = TRUE;
	game->scale->corner = UP_LEFT;
	game->jump_height = game->resolution[WIDTH] / 20;
	game->jump_duration = game->resolution[WIDTH] / 200;
	game->e_jump_duration = game->resolution[WIDTH] / 166;
	game->e_jump_height = game->resolution[WIDTH] / 20;
	game->i_jump_duration = game->resolution[WIDTH] / 100;
	game->i_jump_height = game->resolution[WIDTH] / 80;
	init_struct_variables_utils(game);
}

extern inline void	set_values_to_0(t_game *game, int i)
{
	game->sprite[i].is_alive = TRUE;
	game->sprite[i].collision_buffer = FALSE;
	game->sprite[i].start_sound = 0;
	game->sprite[i].y_wall = 0;
	game->sprite[i].x_wall = 0;
	game->sprite[i].direction[X] = 0.0;
	game->sprite[i].direction[Y] = 0.0;
	game->sprite[i].items_collected = 0;
	game->sprite[i].transformation = FALSE;
	game->sprite[i].transformed = FALSE;
	game->sprite[i].transform_deformation = 0;
	game->sprite[i].hit = FALSE;
	game->sprite[i].collectible_collected = FALSE;
	game->sprite[i].eject_direction[X] = 0.0;
	game->sprite[i].eject_direction[Y] = 0.0;
	game->sprite[i].items_given = FALSE;
	game->sprite[i].dead = FALSE;
	game->sprite[i].in_crosshair = FALSE;
	game->sprite[i].life = 0;
	game->sprite[i].speed = 0.0;
	game->sprite[i].hit_deformation = 0;
}
