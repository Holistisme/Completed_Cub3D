/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aheitz <aheitz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/11 11:51:07 by aheitz            #+#    #+#             */
/*   Updated: 2024/12/11 15:22:45 by aheitz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/* ************************************************************************** */

static inline t_map	set_map(t_game *game);
static inline size_t	check_path(const t_game *game, t_map scan,
						const size_t x, const size_t y);

/* ************************************************************************** */

void	set_scene(t_game *game)
{
	save_textures(game);
	game->map = set_map(game);
	if (!game->player[POSITION][X] && !game->player[POSITION][Y])
		terminate("Looks like the character is already in the afterlife!");
	if (game->elements != check_path(game, set_map(game),
			game->player[POSITION][X], game->player[POSITION][Y]))
		terminate("The map should be as united as the Church!");
	manage_cub_fd(CLOSE);
}

static inline t_map	set_map(t_game *game)
{
	static t_line	*map_start;
	t_line			*current_line;
	t_map			map;
	t_index			y;

	if (!map_start)
		map_start = get_map_content(game);
	set_memory((void **)&map, sizeof(t_string) * (game->height + 1));
	map[game->height] = NULL;
	y = 0;
	current_line = map_start;
	while (current_line)
	{
		set_memory((void **)&map[y], game->width + 1);
		copy_string(current_line->content, map[y]);
		while (get_string_length(map[y]) < game->width)
			map[y] = append_character(map[y], SPACE);
		++y;
		current_line = current_line->next;
	}
	return (map);
}

static inline size_t	check_path(const t_game *game, t_map scan,
							const size_t x, const size_t y)
{
	size_t	elements;

	elements = 0;
	if (scan[y][x] != WALL
		&& (!x || !y
			|| x == game->width - 1 || y == game->height - 1
			|| scan[y + 1][x] == SPACE || scan[y - 1][x] == SPACE
			|| scan[y][x + 1] == SPACE || scan[y][x - 1] == SPACE))
		terminate("The map must have borders against demons!");
	scan[y][x] = CHECKED;
	if ((y != game->height - 1)
		&& !is_in_string(scan[y + 1][x], EXTERNAL))
		elements += check_path(game, scan, x, y + 1);
	if (y != 0 && !is_in_string(scan[y - 1][x], EXTERNAL))
		elements += check_path(game, scan, x, y - 1);
	if ((x != game->width - 1)
		&& !is_in_string(scan[y][x + 1], EXTERNAL))
		elements += check_path(game, scan, x + 1, y);
	if (x != 0 && !is_in_string(scan[y][x - 1], EXTERNAL))
		elements += check_path(game, scan, x - 1, y);
	return (elements + 1);
}
