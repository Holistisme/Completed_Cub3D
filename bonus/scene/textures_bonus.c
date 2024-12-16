/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aheitz <aheitz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/11 11:52:24 by aheitz            #+#    #+#             */
/*   Updated: 2024/12/16 10:24:06 by aheitz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

static t_bool		set_textures(const t_scene *scene);
static void			check_texture_extension(const t_string path);
static void			extract_path(t_string line, t_path *path);
static unsigned int	extract_color(t_string line, t_index digit);

// 💬 Allocates memory for textures and initializes them to NULL.
void	save_textures(t_scene *scene)
{
	set_memory((void **)&scene->textures, sizeof(t_textures));
	scene->textures->north = NULL;
	scene->textures->south = NULL;
	scene->textures->west = NULL;
	scene->textures->east = NULL;
	set_memory((void **)&scene->textures->floor, sizeof(t_color));
	set_memory((void **)&scene->textures->ceiling, sizeof(t_color));
	*scene->textures->floor = -1;
	*scene->textures->ceiling = -1;
	while (!scene->textures->north || !scene->textures->south
		|| !scene->textures->west || !scene->textures->east
		|| *scene->textures->floor == -1 || *scene->textures->ceiling == -1)
		if (!set_textures(scene))
			break ;
	if (!scene->textures->north || !scene->textures->south
		|| !scene->textures->west || !scene->textures->east
		|| *scene->textures->floor == -1 || *scene->textures->ceiling == -1)
		terminate("Cowl may not make the monk, but are necessary for the map!");
	scene->floor = *scene->textures->floor;
	scene->ceiling = *scene->textures->ceiling;
}

// 💬 Reads a line from the file and sets the corresponding texture or color.
static t_bool	set_textures(const t_scene *scene)
{
	t_string	line;

	line = get_next_line(scene->fd);
	if (!line)
		return (FALSE);
	if (line[0] == 'N' && line[1] == 'O' && line[2] == SPACE)
		extract_path(&line[2], &scene->textures->north);
	else if (line[0] == 'S' && line[1] == 'O' && line[2] == SPACE)
		extract_path(&line[2], &scene->textures->south);
	else if (line[0] == 'W' && line[1] == 'E' && line[2] == SPACE)
		extract_path(&line[2], &scene->textures->west);
	else if (line[0] == 'E' && line[1] == 'A' && line[2] == SPACE)
		extract_path(&line[2], &scene->textures->east);
	else if (line[0] == 'F' && line[1] == SPACE)
		*scene->textures->floor = extract_color(&line[1], 0);
	else if (line[0] == 'C' && line[1] == SPACE)
		*scene->textures->ceiling = extract_color(&line[1], 0);
	else if (*line != NEWLINE)
	{
		ignore_spaces(&line);
		if (*line == WALL)
			terminate("A texture or color is missing from the Call!");
		terminate("A line or a color does not follow the Law!");
	}
	return (TRUE);
}

// 💬 Extracts the texture path from the line and validates it.
static void	extract_path(t_string line, t_path *path)
{
	if (*path)
		terminate("I know the Kingdom is colorful, but don't overdo it!");
	ignore_spaces(&line);
	*path = line;
	remove_trailing_spaces(line);
	check_texture_extension(*path);
}

static inline unsigned int	extract_color(t_string line, t_index digit)
{
	t_index	color;
	int		component[4];

	color = R;
	component[R] = 0;
	ignore_spaces(&line);
	remove_trailing_spaces(line);
	while (line[digit])
	{
		if (digit && line[digit] == ',')
		{
			line = &line[digit + 1];
			digit = !(++color);
			component[color] = 0;
			continue ;
		}
		else if (line[digit] < '0' || line[digit] > '9' || color > B
			|| component[color] * 10 + line[digit] - '0' > 255)
			terminate("Color is beyond mortal comprehension (R,G,B [0-255])!");
		component[color] = component[color] * 10 + line[digit++] - '0';
	}
	if (color != B)
		terminate("The trinity of colors is not complete!");
	return (get_rgba((t_rgba){component[R], component[G], component[B], 255}));
}

// 💬 Checks if the texture file has a valid extension (PNG or XPM42).
static void	check_texture_extension(const t_string path)
{
	const size_t	length = get_string_length(path);

	if (!(length >= 4 && (is_same_string(&path[length - 4], PNG)
				|| is_same_string(&path[length - 4], PNG_MAJOR)))
		&& !(length >= 6 && (is_same_string(&path[length - 6], XPM42)
				|| is_same_string(&path[length - 6], XPM42_MAJOR))))
		terminate("Texture extension doesn't match the Creation (PNG/XPM42)!");
}
