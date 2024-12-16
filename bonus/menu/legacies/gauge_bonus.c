/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gauge_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aheitz <aheitz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 13:13:59 by aheitz            #+#    #+#             */
/*   Updated: 2024/12/12 16:04:01 by aheitz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

/* ************************************************************************** */

static void			set_star(t_game *game);
static inline double		get_progression(t_achievement achievement);
static inline void		draw_gauge(mlx_image_t **gauge,
						const double percent);

#define DEFAULT			0
#define PROGRESSIVE		1
#define CURRENT			2
#define FINALE			3

#define LATEST			0
#define TOTAL			1
#define GOAL			2

#define EMPTY_PNG		"./textures/legacies/gauge/empty.png"
#define PROGRESS_PNG	"./textures/legacies/gauge/progressive.png"
#define FINALE_PNG		"./textures/legacies/gauge/finale.png"

#define COPPER_STAR		"./textures/legacies/stars/copper.png"
#define SILVER_STAR		"./textures/legacies/stars/silver.png"
#define GOLD_STAR		"./textures/legacies/stars/gold.png"

/* ************************************************************************** */

extern inline void	draw_progress(t_legacies *legacies,
						t_achievement achievement)
{
	const double	percent = get_progression(achievement);
	t_index			index;

	index = 0;
	while (index < 3)
		legacies->star[index++]->enabled = false;
	if (percent >= 300)
	{
		legacies->star[GOLD]->enabled = true;
		legacies->gauge[CURRENT]->enabled = false;
		legacies->gauge[FINALE]->enabled = true;
		return ;
	}
	else if (percent >= 200)
		legacies->star[GOLD]->enabled = true;
	else if (percent >= 100)
		legacies->star[SILVER]->enabled = true;
	else
		legacies->star[COPPER]->enabled = true;
	legacies->gauge[CURRENT]->enabled = true;
	legacies->gauge[FINALE]->enabled = false;
	draw_gauge(legacies->gauge, (int)percent % 100);
}

static inline void	draw_gauge(mlx_image_t **gauge, const double percent)
{
	t_pixel			pixel;
	t_index			alpha_pixel;
	const uint32_t	gauge_to_fill = gauge[PROGRESSIVE]->width / (100 / percent);

	pixel[X] = 0;
	while (pixel[X] < gauge[PROGRESSIVE]->width)
	{
		pixel[Y] = 0;
		while (pixel[Y] < gauge[PROGRESSIVE]->height)
		{
			alpha_pixel = (((pixel[Y]++)
						* gauge[PROGRESSIVE]->width + pixel[X]) * 4) + A;
			if (pixel[X] < gauge_to_fill)
				gauge[CURRENT]->pixels[alpha_pixel]
					= gauge[PROGRESSIVE]->pixels[alpha_pixel];
			else
				gauge[CURRENT]->pixels[alpha_pixel] = 0;
		}
		++pixel[X];
	}
}

void	set_gauges(t_game *game)
{
	const t_vector	positioning = {game->resolution[WIDTH] / 3.225,
		game->resolution[HEIGHT] / 1.255};

	game->legacies->gauge[DEFAULT]
		= set_image(game, EMPTY_PNG, (t_bipoints)positioning, true);
	game->legacies->gauge[PROGRESSIVE]
		= set_image(game, PROGRESS_PNG, (t_bipoints)positioning, false);
	game->legacies->gauge[CURRENT]
		= set_image(game, PROGRESS_PNG, (t_bipoints)positioning, true);
	game->legacies->gauge[FINALE]
		= set_image(game, FINALE_PNG, (t_bipoints)positioning, false);
	set_star(game);
}

static void	set_star(t_game *game)
{
	const uint32_t	height = game->legacies->gauge[DEFAULT]->instances->y
		+ game->legacies->gauge[DEFAULT]->height / 3.5;
	const uint32_t	middle = game->legacies->gauge[DEFAULT]->instances->x
		+ game->legacies->gauge[DEFAULT]->width / 2;

	game->legacies->star[COPPER] = set_image(game, COPPER_STAR,
			(t_vector){middle, height}, true);
	game->legacies->star[SILVER] = set_image(game, SILVER_STAR,
			(t_vector){middle
			- game->legacies->star[DEFAULT]->width, height}, true);
	game->legacies->star[GOLD] = set_image(game, GOLD_STAR,
			(t_vector){middle, height}, true);
	display_image(game->window, game->legacies->star[SILVER],
		(t_vector){middle + game->legacies->star[DEFAULT]->width, height});
	display_image(game->window, game->legacies->star[GOLD],
		(t_vector){middle - game->legacies->star[DEFAULT]->width * 2, height});
	display_image(game->window, game->legacies->star[GOLD],
		(t_vector){middle + game->legacies->star[DEFAULT]->width * 2, height});
}

static inline double	get_progression(t_achievement achievement)
{
	t_index	rank;
	double	progression[3];

	progression[TOTAL] = 0.0;
	if (achievement[PROGRESSION] >= achievement[GOLD])
		return (300.0);
	else if (achievement[PROGRESSION] > achievement[SILVER])
		progression[TOTAL] = 200.0;
	else if (achievement[PROGRESSION] > achievement[COPPER])
		progression[TOTAL] = 100.0;
	rank = (int)(progression[TOTAL] / 100.0);
	progression[GOAL] = achievement[rank];
	progression[LATEST] = achievement[PROGRESSION];
	if (rank)
	{
		progression[GOAL] -= achievement[rank - 1];
		progression[LATEST] -= achievement[rank - 1];
	}
	return (progression[TOTAL]
		+ (progression[LATEST] / progression[GOAL] * 100.0));
}
