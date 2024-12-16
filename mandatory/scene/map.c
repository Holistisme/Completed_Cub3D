/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aheitz <aheitz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/23 12:35:48 by aheitz            #+#    #+#             */
/*   Updated: 2024/12/14 16:23:00 by aheitz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/* ************************************************************************** */

static inline t_string	get_first_map_line(const t_fd fd);
static inline bool		has_valid_content(t_game *game, const t_string line);
static inline bool		confirm_character(t_game *game, const t_string line,
							const t_index x);
static inline void		set_view(t_game *game, const char orientation);

/* ************************************************************************** */

extern inline t_line	*get_map_content(t_game *game)
{
	t_line			*first_line;
	t_line			*current_line;
	static t_string	next_line;

	set_memory((void **)&first_line, sizeof(t_line));
	first_line->content = get_first_map_line(game->fd);
	current_line = first_line;
	while (current_line && has_valid_content(game, current_line->content))
	{
		++game->height;
		if (game->width < get_string_length(current_line->content))
			game->width = get_string_length(current_line->content);
		current_line->next = NULL;
		next_line = get_next_line(game->fd);
		if (next_line)
		{
			set_memory((void **)&current_line->next, sizeof(t_line));
			current_line->next->content = next_line;
			remove_trailing_spaces(current_line->content);
		}
		current_line = current_line->next;
	}
	if (next_line)
		terminate("Map must be end of file, nothing will be left afterwards!");
	return (first_line);
}

static inline t_string	get_first_map_line(const t_fd fd)
{
	t_string	line;

	line = get_next_line(fd);
	if (line)
		while (*line == NEWLINE)
			line = get_next_line(fd);
	else
		terminate("If there's no map, there's no salvation!");
	return (line);
}

static inline bool	has_valid_content(t_game *game, const t_string line)
{
	t_index	index;
	bool	has_content;

	index = 0;
	has_content = false;
	if (line)
		while (line[index])
			if (confirm_character(game, line, index++))
				has_content = true;
	return (has_content);
}

static inline bool	confirm_character(t_game *game, const t_string line,
						const t_index x)
{
	static t_string	accepted_characters = AUTHORIZED_CHARACTERS;

	if (is_in_string(line[x], accepted_characters))
	{
		if (is_in_string(line[x], PLAYER_ORIENTATIONS))
		{
			game->player[POSITION][X] = x;
			game->player[POSITION][Y] = game->height;
			accepted_characters = BASIC_POSITIONS;
			set_view(game, line[x]);
		}
		if (line[x] != SPACE)
			return (++game->elements);
	}
	else if (is_in_string(line[x], PLAYER_ORIENTATIONS))
		terminate("There's no need for two when faith is our guide!");
	else if (line[X] == NEWLINE)
		terminate("You're not Moses, you can't cut the .cub in two!");
	else
		terminate("Nothing is unknown to Him, except your invalid character!");
	return (false);
}

static inline void	set_view(t_game *game, const char orientation)
{
	t_index					scan;
	const t_double_vector	direction[4] = {{0.0, -1.0}, {+1.0, 0.0},
	{0.0, +1.0}, {-1.0, 0.0}};
	const t_orientation		compass = {NORTH, EAST, SOUTH, WEST};

	scan = 0;
	while (compass[scan] != orientation)
		++scan;
	game->player[DIRECTION][X] = direction[scan][X];
	game->player[DIRECTION][Y] = direction[scan][Y];
	game->player[PLANE][X] = -game->player[DIRECTION][Y] * FOV;
	game->player[PLANE][Y] = game->player[DIRECTION][X] * FOV;
}
