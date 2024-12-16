/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hook_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aheitz <aheitz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/01 16:34:23 by aheitz            #+#    #+#             */
/*   Updated: 2024/12/13 11:57:23 by aheitz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

/* ************************************************************************** */

static inline void	play_chapter(t_game *game, t_introduction *introduction);
static inline void	manage_alphabet(t_game *game, t_action action);
static inline void	manage_cinematics(t_game *game, t_action action);

/* ************************************************************************** */

// 💬 Displays the cinematics and introduction texts.
void	introduce(t_game *game)
{
	static t_introduction	introduction = {0, WAITING, WAITING};

	if (introduction[CHAPTER] < 3)
		play_chapter(game, &introduction);
	else
	{
		introduction[CHAPTER] = 0;
		manage_cinematics(game, UNSET);
		manage_alphabet(game, UNSET);
		raycast(game);
		game->state = &raycast;
	}
}

static inline void	play_chapter(t_game *game, t_introduction *introduction)
{
	if (skip_chapter(game, GET) && (*introduction)[LETTER] != WAITING)
	{
		++(*introduction)[CHAPTER];
		(*introduction)[SENTENCE] = WAITING;
		(*introduction)[LETTER] = WAITING;
	}
	else if ((*introduction)[LETTER] != WAITING)
		audiovisualize((t_game *)game, *introduction);
	else
	{
		if (!(*introduction)[CHAPTER] && (*introduction)[SENTENCE] == WAITING)
		{
			manage_cinematics(game, SET);
			manage_alphabet(game, SET);
		}
		manage_alphabet(game, UNSET);
		manage_alphabet(game, SET);
		game->opening_cinematic[(*introduction)[CHAPTER]]->enabled = true;
		game->parchment->instances->z = game->opening_cinematic
		[(*introduction)[CHAPTER]]->instances->z + 1;
		(*introduction)[LETTER] = 0;
	}
}

// 💬 Initializes the introduction text.
void	set_introduction_message(t_game *game)
{
	game->story[0][0]
		= "Some time ago, all Christians gathered to harmonize their beliefs\n";
	game->story[0][1]
		= "But council broke up arguing about candle number on altar\n";
	game->story[0][2]
		= "And everyone called for a crusade just because, why not!\n";
	game->story[1][0]
		= "All the Christians decided to march against the other infidels\n";
	game->story[1][1]
		= "Armed with swords and shields, they picked up their picnic tables\n";
	game->story[1][2]
		= "No one knew where they were going, nor why they were going there!\n";
	game->story[2][0]
		= "Finally, they reached the Holy Land, and decided to take a break\n";
	game->story[2][1]
		= "But there was no place to sit so, they decided to kill everyone\n";
	game->story[2][2]
		= "Thus began the first crusade, and the first of many to come!\n";
}

// 💬 Initializes the alphabet textures for the game.
static inline void	manage_alphabet(t_game *game, t_action action)
{
	t_path	letter_path;
	t_index	index;

	index = 0;
	while (index < 28)
	{
		if (action == SET)
		{
			if (index < 26)
				letter_path = append_character(ALPHABET_PATH, index + 'a');
			else if (index == EXCLAMATION)
				letter_path = append_character(ALPHABET_PATH, '!');
			else
				letter_path = append_character(ALPHABET_PATH, ',');
			letter_path = append_strings((t_string[3]){letter_path, PNG, NULL});
			game->alphabet[index++]
				= set_image(game, letter_path, (t_vector){424242}, true);
		}
		if (action == UNSET)
			mlx_delete_image(game->window, game->alphabet[index++]);
	}
}

// 💬 Initializes the cinematics textures for the game.
static inline void	manage_cinematics(t_game *game, t_action action)
{
	if (action == SET)
	{
		game->opening_cinematic[0] = set_image(game,
				"textures/cinematics/council.png",
				(t_vector){0}, false);
		game->opening_cinematic[1] = set_image(game,
				"textures/cinematics/march.png", (t_vector){0}, false);
		game->opening_cinematic[2] = set_image(game,
				"textures/cinematics/crusade.png",
				(t_vector){0}, false);
		game->parchment = set_image(game,
				"./textures/cinematics/parchment.png",
				(t_vector){0}, true);
		game->parchment->instances->x = game->resolution[WIDTH] / 2
			- game->parchment->width / 2;
		game->parchment->instances->y = game->resolution[HEIGHT] / 1.38;
	}
	else
	{
		mlx_delete_image(game->window, game->opening_cinematic[0]);
		mlx_delete_image(game->window, game->opening_cinematic[1]);
		mlx_delete_image(game->window, game->opening_cinematic[2]);
		mlx_delete_image(game->window, game->parchment);
	}
}
