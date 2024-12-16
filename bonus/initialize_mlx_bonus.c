/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialize_mlx_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adesille <adesille@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/30 12:12:55 by aheitz            #+#    #+#             */
/*   Updated: 2024/12/15 12:37:40 by adesille         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

/* ************************************************************************** */

#define ICON_PNG	"textures/icon.png"

static inline void	initialize_memory(t_game *game);
static inline void	set_speed(t_game *game);
static inline void	set_campaign_data(t_game *game);

/* ************************************************************************** */

void	initialize_mlx(t_game *game)
{
	mlx_texture_t	*icon;

	initialize_memory(game);
	set_speed(game);
	game->window = mlx_init(game->resolution[WIDTH], game->resolution[HEIGHT],
			game->title, TRUE);
	if (!game->window)
		terminate("Window remains closed, like Heaven for your character!");
	mlx_set_window_pos(game->window, (3840 / 2) - game->window->width / 2,
		(2160 / 2) - game->window->height / 2);
	init_mlx(game);
	if (!game->restart)
	{
		set_campaign_data(game);
		icon = mlx_load_png(ICON_PNG);
		if (!icon)
			terminate("The Devil prevented the loading of the icon!");
		mlx_set_icon(game->window, icon);
		mlx_delete_texture(icon);
	}
	game->state = &display_studio;
	game->resize = (double)game->resolution[WIDTH] / 3840.0;
	manage_mlx(game->window);
	if (game->requested_sky)
		set_supertextures(game);
}

static inline void	set_campaign_data(t_game *game)
{
	game->campaign.player = *game->player;
	game->campaign.scene = *game->scene;
	game->campaign.texture[NORTH_SIDE] = game->scene->textures->north;
	game->campaign.texture[SOUTH_SIDE] = game->scene->textures->south;
	game->campaign.texture[WEST_SIDE] = game->scene->textures->west;
	game->campaign.texture[EAST_SIDE] = game->scene->textures->east;
	game->campaign.environment = game->scene->environment;
	game->menu->blocked_banner = NULL;
}

static inline void	initialize_memory(t_game *game)
{
	if (!game->restart)
	{
		set_memory((void **)&game->menu, sizeof(t_menu));
		set_memory((void **)&game->raycast, sizeof(t_raycast));
		set_memory((void **)&game->legacies, sizeof(t_legacies));
		set_memory((void **)&game->settings, sizeof(t_settings));
		set_memory((void **)&game->settings->loading_scene, sizeof(t_scene));
		set_memory((void **)&game->settings->loading_scene->textures,
			sizeof(t_textures));
		set_memory((void **)&game->settings->loading_scene->textures->ceiling,
			sizeof(t_color));
		set_memory((void **)&game->settings->loading_scene->textures->floor,
			sizeof(t_color));
	}
	load_settings(game);
	game->sensitivity = game->settings->sensitivity;
	handle_resolution(game, 0);
}

static inline void	set_speed(t_game *game)
{
	if (game->resolution[WIDTH] == HD)
		game->speed = 1;
	else if (game->resolution[WIDTH] == FHD)
		game->speed = 2;
	else if (game->resolution[WIDTH] == QHD)
		game->speed = 3;
	else if (game->resolution[WIDTH] == UHD)
		game->speed = 4;
}
