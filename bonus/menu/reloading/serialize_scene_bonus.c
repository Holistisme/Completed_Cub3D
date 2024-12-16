/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   serialize_scene_bonus.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aheitz <aheitz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/27 13:07:54 by aheitz            #+#    #+#             */
/*   Updated: 2024/12/12 16:04:15 by aheitz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

/* ************************************************************************** */

static inline bool	write_data(FILE *save, const t_scene *scene);
static inline bool	write_textures(FILE *save, const t_textures *textures);
static inline bool	write_map(FILE *save, const t_scene *scene);

/* ************************************************************************** */

bool	serialize_scene(FILE *save, const t_scene *scene)
{
	if (write_data(save, scene) && write_textures(save, scene->textures)
		&& write_map(save, scene))
		return (true);
	return (false);
}

static inline bool	write_data(FILE *save, const t_scene *scene)
{
	return (write_file(&scene->height, sizeof(uint32_t), 1, save)
		&& write_file(&scene->width, sizeof(uint32_t), 1, save)
		&& write_file(&scene->elements, sizeof(size_t), 1, save)
		&& write_file(&scene->ceiling, sizeof(t_rgba_color), 1, save)
		&& write_file(&scene->floor, sizeof(t_rgba_color), 1, save)
		&& write_file(&scene->environment, sizeof(t_supertexture), 1, save));
}

static inline bool	write_textures(FILE *save, const t_textures *textures)
{
	t_index			index;
	size_t			length;
	const t_path	paths[4] = {textures->north, textures->south,
		textures->west, textures->east};

	index = 0;
	while (index < 4)
	{
		length = get_string_length(paths[index]) + 1;
		if (!write_file(&length, sizeof(size_t), 1, save)
			|| !write_file(paths[index++], sizeof(char), length, save))
			return (false);
	}
	return (write_file(textures->floor, sizeof(t_color), 1, save)
		&& write_file(textures->ceiling, sizeof(t_color), 1, save));
}

static inline bool	write_map(FILE *save, const t_scene *scene)
{
	uint32_t	index;

	index = 0;
	while (index < scene->height)
		if (!write_file(scene->map[index++], sizeof(char), scene->width, save))
			return (false);
	return (true);
}
