/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   deserialize_scene_bonus.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aheitz <aheitz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/28 09:27:14 by aheitz            #+#    #+#             */
/*   Updated: 2024/12/12 16:04:11 by aheitz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

/* ************************************************************************** */

static inline bool	load_data(FILE *save, t_scene *scene);
static inline bool	load_texture(FILE *save, t_textures *textures);
static inline bool	load_map(FILE *save, t_scene *scene);

/* ************************************************************************** */

bool	deserialize_scene(FILE *save, t_game *game)
{
	if (load_data(save, game->settings->loading_scene)
		&& load_texture(save, game->settings->loading_scene->textures)
		&& load_map(save, game->settings->loading_scene))
	{
		game->scene = game->settings->loading_scene;
		return (true);
	}
	return (false);
}

static inline bool	load_data(FILE *save, t_scene *scene)
{
	return (read_file(&scene->height, sizeof(uint32_t), 1, save)
		&& read_file(&scene->width, sizeof(uint32_t), 1, save)
		&& read_file(&scene->elements, sizeof(size_t), 1, save)
		&& read_file(&scene->ceiling, sizeof(t_rgba_color), 1, save)
		&& read_file(&scene->floor, sizeof(t_rgba_color), 1, save)
		&& read_file(&scene->environment, sizeof(t_supertexture), 1, save));
}

static inline bool	load_texture(FILE *save, t_textures *textures)
{
	t_index	index;
	t_path	*texture_paths[4];
	size_t	texture_length;

	index = 0;
	texture_paths[NORTH_SIDE] = &textures->north;
	texture_paths[SOUTH_SIDE] = &textures->south;
	texture_paths[WEST_SIDE] = &textures->west;
	texture_paths[EAST_SIDE] = &textures->east;
	while (index < 4)
	{
		if (!read_file(&texture_length, sizeof(size_t), 1, save))
			return (false);
		set_memory((void **)texture_paths[index], texture_length);
		if (!read_file(*texture_paths[index++],
				sizeof(char), texture_length, save))
			return (false);
	}
	return (read_file(textures->floor, sizeof(t_color), 1, save)
		&& read_file(textures->ceiling, sizeof(t_color), 1, save));
}

static inline bool	load_map(FILE *save, t_scene *scene)
{
	uint32_t	index;

	set_memory((void **)&scene->map, (scene->height + 1) * sizeof(t_string));
	index = 0;
	while (index < scene->height)
	{
		set_memory((void **)&scene->map[index], scene->width + 1);
		if (!read_file(scene->map[index++], sizeof(char), scene->width, save))
			return (false);
	}
	scene->map[index] = NULL;
	return (true);
}
