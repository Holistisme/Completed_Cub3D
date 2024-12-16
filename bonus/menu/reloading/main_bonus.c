/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aheitz <aheitz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/21 11:16:30 by aheitz            #+#    #+#             */
/*   Updated: 2024/12/16 10:30:11 by aheitz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

/* ************************************************************************** */

bool	load_game(t_game *game)
{
	FILE	*save;
	bool	success;

	success = false;
	save = open_file(CAMPAIGN_BINARY, READ_BINARIES);
	if (save && check_key(save, CAMPAIGN_BINARY))
	{
		if (read_file(game->player, sizeof(t_player), 1, save)
			&& deserialize_scene(save, game)
			&& load_sprites(game))
		{
			change_textures(game, true);
			success = true;
		}
		return (close_file(save, CAMPAIGN_BINARY) && success);
	}
	return (success);
}

void	save_game(t_game *game)
{
	FILE			*save;

	save = open_file(CAMPAIGN_BINARY, WRITE_BINARIES);
	if (!save)
		return ;
	if (write_key(save)
		&& write_file(game->player, sizeof(t_player), 1, save)
		&& serialize_scene(save, game->scene)
		&& save_sprites(game))
	{
		if (game->menu->blocked_banner)
		{
			mlx_delete_image(game->window, game->menu->blocked_banner);
			game->menu->blocked_banner = NULL;
		}
	}
	close_file(save, CAMPAIGN_BINARY);
}

extern inline void	change_textures(t_game *game, const bool load)
{
	t_index	index;
	t_path	*current_textures[4];

	index = 0;
	current_textures[NORTH_SIDE] = &game->scene->textures->north;
	current_textures[SOUTH_SIDE] = &game->scene->textures->south;
	current_textures[WEST_SIDE] = &game->scene->textures->west;
	current_textures[EAST_SIDE] = &game->scene->textures->east;
	if (!load)
	{
		*game->player = game->campaign.player;
		*game->scene = game->campaign.scene;
	}
	while (index <= EAST_SIDE)
	{
		if (!load)
			*current_textures[index] = game->campaign.texture[index];
		mlx_delete_image(game->window, game->textures[index]);
		game->textures[index]
			= set_texture(game->window, *current_textures[index]);
		++index;
	}
}
