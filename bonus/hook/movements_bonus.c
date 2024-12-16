/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movements_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adesille <adesille@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/16 11:31:56 by isb               #+#    #+#             */
/*   Updated: 2024/12/16 11:13:12 by adesille         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

void	items_management_player(t_game *game)
{
	static int	collect = 0;
	int			j;

	update_achievement(game->legacies->achievement, WALK, +1);
	if (game->player->blue_cord_collected)
		return ;
	j = game->sprite_count - 1;
	while (j > game->sprite_count - game->items_count - 1)
	{
		if (valid_player_collision(game, j))
		{
			play_sound("drinking", 0);
			if (!(++collect % 3))
				play_sound("fucked-up", 0);
			game->sprite[j].position[X] = -1;
			game->sprite[j].position[Y] = -1;
			game->sprite[j].collectible_collected = TRUE;
			if (game->brainless_mode)
				game->player->blue_cord_collected = TRUE;
			if (game->player->life >= 15)
				return (game->player->life -= 15, (void)0);
		}
		j--;
	}
}

void	aiming_management(t_game *game, t_raycast *r, bool *aim,
		long *aim_start)
{
	*aim = TRUE;
	*aim_start = get_time();
	game->aiming = !game->aiming;
	if (!game->gun_cheat_code)
	{
		r->crossbow[0]->enabled = !r->crossbow[0]->enabled;
		r->crossbow_aim[0]->enabled = !r->crossbow_aim[0]->enabled;
	}
	else
	{
		r->gun[0]->enabled = !r->gun[0]->enabled;
		r->gun_aim[0]->enabled = !r->gun_aim[0]->enabled;
	}
}

void	weapon_management(t_game *game, t_raycast *r)
{
	static long	aim_start = 0;
	static bool	aim = FALSE;

	if (get_time() - aim_start > 300)
		aim = FALSE;
	if (mlx_is_mouse_down(game->window, MLX_MOUSE_BUTTON_RIGHT)
		&& !game->shoot_animation && !game->reload_animation && !aim)
		aiming_management(game, r, &aim, &aim_start);
	else if (mlx_is_mouse_down(game->window, MLX_MOUSE_BUTTON_LEFT)
		&& !game->shoot_animation && !game->reload_animation
		&& game->bullets < game->max_bullets)
	{
		game->shoot_animation = TRUE;
		game->bullets++;
		if (game->gun_cheat_code)
			play_sound("gun-shot", UNDEFINED);
		else
			play_sound("crossbow-shot", UNDEFINED);
	}
	else if (mlx_is_mouse_down(game->window, MLX_MOUSE_BUTTON_LEFT)
		&& !game->shoot_animation && !game->reload_animation
		&& game->bullets >= game->max_bullets)
		play_sound("empty-gun", UNDEFINED);
	else if (mlx_is_mouse_down(game->window, MLX_MOUSE_BUTTON_MIDDLE))
		game->open_door = TRUE;
}

void	movements_utils(t_game *game, t_raycast *r)
{
	if (mlx_is_key_down(game->window, A_KEY) && is_move_ok(game, A_KEY))
	{
		game->player->position[X] -= game->player->plane[0] * 0.15;
		game->player->position[Y] -= game->player->plane[1] * 0.15;
		items_management_player(game);
	}
	else if (mlx_is_key_down(game->window, D_KEY) && is_move_ok(game, D_KEY))
	{
		game->player->position[X] += game->player->plane[0] * 0.15;
		game->player->position[Y] += game->player->plane[1] * 0.15;
		items_management_player(game);
	}
	else
		weapon_management(game, r);
}

void	movements(void *param)
{
	t_game	*game;

	game = param;
	if (game->state != &raycast || get_time() - game->raycast->start_time < 300)
		return ;
	if (mlx_is_key_down(game->window, W_KEY) && is_move_ok(game, W_KEY))
	{
		game->player->position[X] += game->player->direction[0] * 0.15;
		game->player->position[Y] += game->player->direction[1] * 0.15;
		items_management_player(game);
	}
	else if (mlx_is_key_down(game->window, S_KEY) && is_move_ok(game, S_KEY))
	{
		game->player->position[X] -= game->player->direction[0] * 0.15;
		game->player->position[Y] -= game->player->direction[1] * 0.15;
		items_management_player(game);
	}
	else
		movements_utils(game, game->raycast);
}
