/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_bonus.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aheitz <aheitz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/23 12:35:48 by aheitz            #+#    #+#             */
/*   Updated: 2024/12/14 16:39:30 by aheitz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

static t_string	get_first_map_line(const t_fd fd);
static t_bool	has_valid_content(t_game *game, const t_string line);
static t_bool	confirm_character(t_game *game, const t_string line,
					const t_index x);
static void		set_view(t_game *game, const char orientation);

// 💬 Retrieves the map content from the file and stores it in a linked list.
t_line	*get_map_content(t_game *game)
{
	t_line			*first_line;
	t_line			*current_line;
	static t_string	next_line;

	set_memory((void **)&first_line, sizeof(t_line));
	first_line->content = get_first_map_line(game->scene->fd);
	current_line = first_line;
	while (current_line && has_valid_content(game, current_line->content))
	{
		++game->scene->height;
		if (game->scene->width < get_string_length(current_line->content))
			game->scene->width = get_string_length(current_line->content);
		current_line->next = NULL;
		next_line = get_next_line(game->scene->fd);
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

// 💬 Retrieves the first non-empty line from the file.
static t_string	get_first_map_line(const t_fd fd)
{
	t_string	line;

	line = get_next_line(fd);
	while (line && *line == NEWLINE)
		line = get_next_line(fd);
	if (!line)
		terminate("If there's no map, there's no salvation!");
	return (line);
}

// 💬 Checks if the line has valid content for the map.
static t_bool	has_valid_content(t_game *game, const t_string line)
{
	t_index	x;
	t_bool	has_content;

	x = 0;
	has_content = FALSE;
	if (line)
		while (line[x])
			if (confirm_character(game, line, x++))
				has_content = TRUE;
	return (has_content);
}

// 💬 Confirms if the character is valid and updates player position if needed.
static t_bool	confirm_character(t_game *game, const t_string line,
		const t_index x)
{
	static t_string	accepted_characters = AUTHORIZED_CHARACTERS;

	if (is_in_string(line[x], accepted_characters))
	{
		if (is_in_string(line[x], PLAYER_ORIENTATIONS))
		{
			set_memory((void **)&game->player, sizeof(t_player));
			game->player->position[Y] = game->scene->height;
			game->player->position[X] = x;
			set_view(game, line[x]);
			accepted_characters = BASIC_POSITIONS;
		}
		if (line[x] != SPACE)
		{
			++game->scene->elements;
			return (TRUE);
		}
	}
	else if (is_in_string(line[x], PLAYER_ORIENTATIONS))
		terminate("There's no need for two when faith is our guide!");
	else
		terminate("Nothing is unknown to Him, except your invalid character!");
	return (FALSE);
}

// 💬 Sets the player's view direction based on the orientation character.
static void	set_view(t_game *game, const char orientation)
{
	const t_double_vector	directions[4] = {{0.0, -1.0}, {+1.0, 0.0},
	{0.0, +1.0}, {-1.0, 0.0}};
	const t_orientation		orientations = {NORTH, EAST, SOUTH, WEST};
	t_index					scan;

	scan = 0;
	while (orientations[scan] != orientation)
		++scan;
	game->player->direction[X] = directions[scan][X];
	game->player->direction[Y] = directions[scan][Y];
	game->fov = PI / 3;
	game->fov = PI / 3;
	game->sensitivity = 1;
	game->player->plane[X] = -game->player->direction[Y] * game->fov;
	game->player->plane[Y] = game->player->direction[X] * game->fov;
}
