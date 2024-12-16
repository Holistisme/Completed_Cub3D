/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_crusaders_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aheitz <aheitz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/09 10:15:32 by adesille          #+#    #+#             */
/*   Updated: 2024/12/12 16:01:24 by aheitz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

static inline void	load_crusade_textures_utils(t_game *game)
{
	game->raycast->crusader3[0] = set_texture(game->window,
			"textures/crusade/Red_0.png");
	game->raycast->crusader3[1] = set_texture(game->window,
			"textures/crusade/Red_2.png");
	game->raycast->crusader3[2] = set_texture(game->window,
			"textures/crusade/Red_3.png");
	game->raycast->crusader3[3] = set_texture(game->window,
			"textures/crusade/Red_4.png");
	game->raycast->holy_item = set_texture(game->window,
			"textures/crusade/Holy_Item.png");
	game->raycast->crusader_death = set_texture(game->window,
			"textures/crusade/Death.png");
}

extern inline void	load_crusade_textures(t_game *game)
{
	game->raycast->crusader1[0] = set_texture(game->window,
			"textures/crusade/Blue_0.png");
	game->raycast->crusader1[1] = set_texture(game->window,
			"textures/crusade/Blue_2.png");
	game->raycast->crusader1[2] = set_texture(game->window,
			"textures/crusade/Blue_3.png");
	game->raycast->crusader1[3] = set_texture(game->window,
			"textures/crusade/Blue_4.png");
	game->raycast->crusader2[0] = set_texture(game->window,
			"textures/crusade/White_0.png");
	game->raycast->crusader2[1] = set_texture(game->window,
			"textures/crusade/White_2.png");
	game->raycast->crusader2[2] = set_texture(game->window,
			"textures/crusade/White_3.png");
	game->raycast->crusader2[3] = set_texture(game->window,
			"textures/crusade/White_4.png");
	load_crusade_textures_utils(game);
}
