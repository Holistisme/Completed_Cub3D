/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aheitz <aheitz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 10:49:10 by aheitz            #+#    #+#             */
/*   Updated: 2024/12/12 16:04:04 by aheitz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

/* ************************************************************************** */

static void	set_descriptions(t_game *game);
static void	open_legacies(t_game *game);
static void	close_legacies(t_game *game);

#define FRAME			"./textures/legacies/frame.png"
#define TITLE			"./textures/legacies/title.png"

#define WALK_DESC		"./textures/legacies/descriptions/walk.png"
#define VIEW_DESC		"./textures/legacies/descriptions/view.png"
#define TIME_DESC		"./textures/legacies/descriptions/time.png"

#define WALK_PIC		"./textures/legacies/pictures/walk.png"
#define VIEW_PIC		"./textures/legacies/pictures/view.png"
#define TIME_PIC		"./textures/legacies/pictures/time.png"

/* ************************************************************************** */

void	master_legacies(t_game *game)
{
	if (game->state == &master_legacies)
		close_legacies(game);
	else
		open_legacies(game);
}

static void	set_descriptions(t_game *game)
{
	t_index			index;
	const t_path	descriptions[ACHIEVEMENTS_COUNT + 1]
		= {WALK_DESC, VIEW_DESC, TIME_DESC, NULL};
	const t_vector	positioning = {game->resolution[WIDTH] / 1.925,
		game->resolution[HEIGHT] / 1.365};

	index = 0;
	while (descriptions[index])
	{
		game->legacies->descriptions[index]
			= set_image(game, descriptions[index],
				(t_bipoints)positioning, false);
		game->legacies->descriptions[index]->instances->x
			-= game->legacies->descriptions[index]->width / 2;
		++index;
	}
}

static void	open_legacies(t_game *game)
{
	const t_path	pictures[ACHIEVEMENTS_COUNT + 1]
		= {WALK_PIC, VIEW_PIC, TIME_PIC, NULL};
	const t_vector	positioning = {game->resolution[WIDTH] / 2.66,
		game->resolution[HEIGHT] / 5.5};
	t_index			index;

	index = 0;
	while (index < ACHIEVEMENTS_COUNT)
	{
		game->legacies->image[index] = set_image(game, pictures[index],
				(t_bipoints)positioning, false);
		++index;
	}
	game->legacies->frame = set_image(game, FRAME, (t_vector){0}, true);
	game->legacies->title = set_image(game, TITLE,
			(t_vector){game->resolution[WIDTH] / 2.02,
			game->resolution[HEIGHT] / 7.35}, true);
	set_descriptions(game);
	set_gauges(game);
	display_achievement(game->legacies, 0);
	game->state = &master_legacies;
}

static void	close_legacies(t_game *game)
{
	t_index	index;

	mlx_delete_image(game->window, game->legacies->frame);
	mlx_delete_image(game->window, game->legacies->title);
	index = 0;
	while (index < ACHIEVEMENTS_COUNT + 1)
	{
		if (index <= GOLD)
		{
			mlx_delete_image(game->window, game->legacies->star[index]);
			mlx_delete_image(game->window, game->legacies->image[index]);
			mlx_delete_image(game->window, game->legacies->descriptions[index]);
		}
		mlx_delete_image(game->window, game->legacies->gauge[index++]);
	}
	game->state = game->main_menu;
}
