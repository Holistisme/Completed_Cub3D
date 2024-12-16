/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adesille <adesille@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/11 11:52:24 by aheitz            #+#    #+#             */
/*   Updated: 2024/12/16 11:27:00 by adesille         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/* ************************************************************************** */

static bool					set_textures(t_game *game);
static void					extract_path(t_game *game, t_string line,
								mlx_image_t **texture);
static unsigned int			extract_color(t_string line, t_index digit);
static mlx_image_t			*set_texture(mlx_t *window, const t_path file);

/* ************************************************************************** */

void	save_textures(t_game *game)
{
	game->texture[NORTH_SIDE] = NULL;
	game->texture[SOUTH_SIDE] = NULL;
	game->texture[WEST_SIDE] = NULL;
	game->texture[EAST_SIDE] = NULL;
	game->floor = UNSET;
	game->ceiling = UNSET;
	while (!game->texture[NORTH_SIDE] || !game->texture[SOUTH_SIDE]
		|| !game->texture[WEST_SIDE] || !game->texture[EAST_SIDE]
		|| game->floor == UNSET || game->ceiling == UNSET)
		if (!set_textures(game))
			break ;
	if (!game->texture[NORTH_SIDE] || !game->texture[SOUTH_SIDE]
		|| !game->texture[WEST_SIDE] || !game->texture[EAST_SIDE]
		|| game->floor == UNSET || game->ceiling == UNSET)
		terminate("Cowl may not make the monk, but are necessary for the map!");
}

static bool	set_textures(t_game *game)
{
	t_string	line;

	line = get_next_line(game->fd);
	if (!line)
		return (false);
	if (line[0] == 'N' && line[1] == 'O' && line[2] == SPACE)
		extract_path(game, &line[2], &game->texture[NORTH_SIDE]);
	else if (line[0] == 'S' && line[1] == 'O' && line[2] == SPACE)
		extract_path(game, &line[2], &game->texture[SOUTH_SIDE]);
	else if (line[0] == 'W' && line[1] == 'E' && line[2] == SPACE)
		extract_path(game, &line[2], &game->texture[WEST_SIDE]);
	else if (line[0] == 'E' && line[1] == 'A' && line[2] == SPACE)
		extract_path(game, &line[2], &game->texture[EAST_SIDE]);
	else if (line[0] == 'F' && line[1] == SPACE)
		game->floor = extract_color(&line[1], 0);
	else if (line[0] == 'C' && line[1] == SPACE)
		game->ceiling = extract_color(&line[1], 0);
	else if (*line != NEWLINE)
	{
		ignore_spaces(&line);
		if (*line == WALL)
			terminate("A texture or color is missing from the Call!");
		terminate("A line or a color does not follow the Law!");
	}
	return (true);
}

static void	extract_path(t_game *game, t_string line, mlx_image_t **texture)
{
	if (*texture)
		terminate("I know the Kingdom is colorful, but don't overdo it!");
	ignore_spaces(&line);
	remove_trailing_spaces(line);
	*texture = set_texture(game->window, line);
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

static mlx_image_t	*set_texture(mlx_t *window, const t_path file)
{
	mlx_image_t		*image;
	mlx_texture_t	*texture;

	texture = mlx_load_png(file);
	if (!texture)
		terminate("The Devil prevented the loading of a texture!");
	image = mlx_texture_to_image(window, texture);
	if (!image)
		terminate("The Devil stealed your image!");
	mlx_delete_texture(texture);
	return (image);
}
