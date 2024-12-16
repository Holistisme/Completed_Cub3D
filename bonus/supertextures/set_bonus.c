/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_bonus.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aheitz <aheitz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/04 15:29:42 by aheitz            #+#    #+#             */
/*   Updated: 2024/12/12 16:02:24 by aheitz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

/* ************************************************************************** */

#define J_SKY		"./textures/jerusalem/sky.png"
#define J_FLOOR		"./textures/jerusalem/floor.png"
#define HL_SKY		"./textures/hell/sky.png"
#define HL_FLOOR	"./textures/hell/floor.png"
#define HV_SKY		"./textures/heaven/sky.png"
#define HV_FLOOR	"./textures/heaven/floor.png"
#define C_SKY		"./textures/custom/sky.png"
#define C_FLOOR		"./textures/custom/floor.png"

/* ************************************************************************** */

void	set_supertextures(t_game *game)
{
	if (game->scene->environment == JERUSALEM)
	{
		game->sky = set_texture(game->window, J_SKY);
		game->floor = set_texture(game->window, J_FLOOR);
	}
	else if (game->scene->environment == HELL)
	{
		game->sky = set_texture(game->window, HL_SKY);
		game->floor = set_texture(game->window, HL_FLOOR);
	}
	else if (game->scene->environment == HEAVEN)
	{
		game->sky = set_texture(game->window, HV_SKY);
		game->floor = set_texture(game->window, HV_FLOOR);
	}
	else
	{
		game->sky = set_texture(game->window, C_SKY);
		game->floor = set_texture(game->window, C_FLOOR);
	}
}

extern inline void	unset_supertextures(t_game *game)
{
	mlx_delete_image(game->window, game->sky);
	game->sky = NULL;
	mlx_delete_image(game->window, game->floor);
}
