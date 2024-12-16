/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_brainless_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adesille <adesille@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/29 13:46:22 by adesille          #+#    #+#             */
/*   Updated: 2024/12/16 10:39:47 by adesille         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

/* ************************************************************************** */

#define TRGASPAR		"./textures/brainless/trgaspar.png"
#define SUPER_GASPAR	"./textures/brainless/super_gaspar.png"
#define MAGA42_0		"./textures/brainless/MAGA42_0.png"
#define MAGA42_1		"./textures/brainless/MAGA42_1.png"
#define MAGA42_2		"./textures/brainless/MAGA42_2.png"
#define MAGA42_3		"./textures/brainless/MAGA42_3.png"
#define GASPAR_POWER3	"./textures/brainless/gaspar_power3.png"
#define BLACK_SCREEN	"./textures/brainless/black_screen.png"
#define ACHTUNG			"./textures/brainless/achtung.png"
#define CREEPY_GASPAR1	"./textures/brainless/creepy_gaspar1.png"
#define CREEPY_GASPAR2	"./textures/brainless/creepy_gaspar2.png"
#define CREEPY_GASPAR3	"./textures/brainless/creepy_gaspar3.png"
#define CREEPY_GASPAR4	"./textures/brainless/creepy_gaspar4.png"
#define CREEPY_GASPAR5	"./textures/brainless/creepy_gaspar5.png"

/* ************************************************************************** */

extern inline void	load_brainless_textures(t_game *game)
{
	game->raycast->bad_guy[0] = set_texture(game->window, TRGASPAR);
	game->raycast->bad_guy[1] = set_texture(game->window, SUPER_GASPAR);
	game->raycast->good_guy[0] = set_texture(game->window, MAGA42_0);
	game->raycast->good_guy[1] = set_texture(game->window, MAGA42_1);
	game->raycast->good_guy[2] = set_texture(game->window, MAGA42_2);
	game->raycast->good_guy[3] = set_texture(game->window, MAGA42_3);
	game->raycast->gaspar_item = set_texture(game->window, GASPAR_POWER3);
}

extern inline void	load_brainless_intro(t_game *game)
{
	int	i;

	game->start_screen[0] = set_texture(game->window, BLACK_SCREEN);
	game->start_screen[1] = set_texture(game->window, ACHTUNG);
	game->start_screen[2] = set_texture(game->window, CREEPY_GASPAR1);
	game->start_screen[2] = set_texture(game->window, CREEPY_GASPAR2);
	game->start_screen[3] = set_texture(game->window, CREEPY_GASPAR3);
	game->start_screen[4] = set_texture(game->window, CREEPY_GASPAR4);
	game->start_screen[5] = set_texture(game->window, CREEPY_GASPAR5);
	i = -1;
	while (++i < 6)
		mlx_resize_image(game->start_screen[i], game->resolution[WIDTH],
			game->resolution[HEIGHT]);
	i = -1;
	while (++i < 6)
		display_image(game->window, game->start_screen[i], (t_vector){0, 0});
	i = 1;
	while (++i < 6)
		game->start_screen[i]->enabled = FALSE;
}
