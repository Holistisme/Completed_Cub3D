/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialization_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adesille <adesille@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/23 13:11:06 by adesille          #+#    #+#             */
/*   Updated: 2024/12/16 11:26:35 by adesille         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

static inline void	init_items(t_game *game, int i)
{
	uint32_t	x_enemy;
	uint32_t	y_enemy;
	int			j;

	j = i;
	while (i < j + 18)
	{
		x_enemy = rand() % (game->scene->height - 1 + 1) + 1;
		y_enemy = rand() % (game->scene->width - 1 + 1) + 1;
		if (x_enemy < game->scene->width && y_enemy < game->scene->height)
		{
			if (game->scene->map[y_enemy][x_enemy] == '0')
			{
				game->sprite[++i].position[X] = x_enemy;
				game->sprite[i].position[Y] = y_enemy;
				correct_position(game, y_enemy, x_enemy,
					&game->sprite[i].position);
				game->sprite[i].type = ITEMS;
				set_values_to_0(game, i);
			}
		}
	}
	game->sprite_count = i + 1;
	game->items_count = i - j - 1;
}

extern inline void	init_sprites(t_game *game, int i)
{
	uint32_t	x_enemy;
	uint32_t	y_enemy;

	while (i < 18)
	{
		x_enemy = rand() % (game->scene->height - 1 + 1) + 1;
		y_enemy = rand() % (game->scene->width - 1 + 1) + 1;
		if (x_enemy < game->scene->width && y_enemy < game->scene->height
			&& game->scene->map[y_enemy][x_enemy] == '0' &&
			y_enemy != (uint32_t)game->player->position[Y]
			&& x_enemy != (uint32_t)game->player->position[X])
		{
			game->sprite[++i].position[X] = x_enemy;
			game->sprite[i].position[Y] = y_enemy;
			correct_position(game, y_enemy, x_enemy, &game->sprite[i].position);
			if (!(i % 3))
				game->sprite[i].type = GOOD_GUY;
			else if (i % 3 == 1)
				game->sprite[i].type = BAD_GUY1;
			else if (i % 3 == 2)
				game->sprite[i].type = BAD_GUY2;
			set_values_to_0(game, i);
		}
	}
	init_items(game, i);
}

extern inline void	correct_position(t_game *game, int y, int x,
		t_double_vector *position)
{
	if (game->scene->map[(int)((float)y + 0.5)][x] != '1'
		&& game->scene->map[(int)((float)y + 0.5)][x] != 'D')
		(*position)[Y] = y + 0.5;
	else if (game->scene->map[(int)((float)y + 0.5)][x] != 'D')
		(*position)[Y] = y - 0.5;
	else
		(*position)[Y] = y;
	if (game->scene->map[y][(int)((float)x + 0.5)] != '1'
		&& game->scene->map[y][(int)((float)x + 0.5)] != 'D')
		(*position)[X] = x + 0.5;
	else if (game->scene->map[y][(int)((float)x + 0.5)] != 'D')
		(*position)[X] = x - 0.5;
	else
		(*position)[X] = x;
}

// 💬 Initializes the MLX context and sets up the window.
extern inline void	init_mlx(t_game *game)
{
	srand(time(NULL));
	init_struct_variables(game);
	load_images(game, &game->frame, game->resolution[WIDTH],
		game->resolution[HEIGHT]);
	load_images(game, &game->minimap, game->resolution[WIDTH],
		game->resolution[HEIGHT]);
	display_image(game->window, game->frame, (t_vector){0, 0});
	display_image(game->window, game->minimap, (t_vector){0, 0});
	normalize_data(game, game->scale->minimap_size, game->scale->corner);
	load_textures(game);
	set_memory((void **)&game->zbuffer, sizeof(double)
		* game->resolution[WIDTH]);
	set_memory((void **)&game->door_buffer, sizeof(double)
		* game->resolution[WIDTH]);
}
