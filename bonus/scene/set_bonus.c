/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_bonus.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aheitz <aheitz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/11 11:51:07 by aheitz            #+#    #+#             */
/*   Updated: 2024/12/12 16:02:34 by aheitz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

static size_t	check_path(const t_map scan, const t_index x,
					const t_index y, const t_scene *scene);
static t_map	set_map(t_game *game);

// 💬 Sets up the game scene by loading textures and initializing the map.
void	set_scene(t_game *game)
{
	save_textures(game->scene);
	game->scene->map = set_map(game);
	if (!game->player)
		terminate("Looks like the character is already in the afterlife!");
	if (game->scene->elements != check_path(set_map(game),
			game->player->position[X], game->player->position[Y], game->scene))
		terminate("The map should be as united as the Church!");
	manage_cub_fd(CLOSE);
}

// 💬 Initializes the map by reading its content and formatting it.
static t_map	set_map(t_game *game)
{
	static t_line	*map_start = NULL;
	t_line			*current_line;
	t_map			map;
	t_index			line_index;

	if (!map_start)
		map_start = get_map_content(game);
	set_memory((void **)&map, sizeof(t_string) * (game->scene->height + 1));
	map[game->scene->height] = NULL;
	line_index = 0;
	current_line = map_start;
	while (current_line)
	{
		set_memory((void **)&map[line_index], game->scene->width + 1);
		copy_string(current_line->content, map[line_index]);
		while (get_string_length(map[line_index]) < game->scene->width)
			map[line_index] = append_character(map[line_index], SPACE);
		++line_index;
		current_line = current_line->next;
	}
	return (map);
}

// 💬 Checks the map for valid paths and counts the elements.
static size_t	check_path(const t_map scan, const t_index x,
					const t_index y, const t_scene *scene)
{
	size_t	elements;

	elements = 0;
	if (scan[y][x] != WALL
		&& (x == 0 || y == 0
			|| (size_t)x == scene->width - 1 || (size_t)y == scene->height - 1
			|| scan[y + 1][x] == SPACE || scan[y - 1][x] == SPACE
			|| scan[y][x + 1] == SPACE || scan[y][x - 1] == SPACE))
		terminate("The map must have borders against demons!");
	scan[y][x] = CHECKED;
	if (((size_t)y != scene->height - 1)
		&& !is_in_string(scan[y + 1][x], EXTERNAL))
		elements += check_path(scan, x, y + 1, scene);
	if (y != 0 && !is_in_string(scan[y - 1][x], EXTERNAL))
		elements += check_path(scan, x, y - 1, scene);
	if (((size_t)x != scene->width - 1)
		&& !is_in_string(scan[y][x + 1], EXTERNAL))
		elements += check_path(scan, x + 1, y, scene);
	if (x != 0 && !is_in_string(scan[y][x - 1], EXTERNAL))
		elements += check_path(scan, x - 1, y, scene);
	return (elements + 1);
}
