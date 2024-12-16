/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   audiovisual_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aheitz <aheitz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/14 16:14:59 by aheitz            #+#    #+#             */
/*   Updated: 2024/12/12 16:04:41 by aheitz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

static void	write_next_line(t_game *game, t_introduction introduction,
				const long last_action);
static void	play_audio(const t_introduction introduction);

// 💬 Displays the cinematics and introduction texts.
void	audiovisualize(t_game *game, t_introduction introduction)
{
	static long	last_action = 0;
	const char	letter = game->story[introduction[CHAPTER]]
	[introduction[SENTENCE]][introduction[LETTER]];

	if (introduction[SENTENCE] == WAITING)
	{
		last_action = get_current_time();
		introduction[SENTENCE] = 0;
	}
	else if (is_millisecond_elapsed(last_action, 49))
	{
		play_audio(introduction);
		if (letter)
		{
			write_subtitle(game, letter);
			++introduction[LETTER];
			last_action = get_current_time();
		}
		else
			write_next_line(game, introduction, last_action);
	}
}

// 💬 Saves skip state.
bool	skip_chapter(t_game *game, t_action action)
{
	static bool	skip = false;

	if (action == SET)
		skip = true;
	else if (skip)
	{
		stop_sound();
		write_subtitle(game, 0);
		skip = false;
		return (true);
	}
	return (false);
}

// 💬 Checks if the next line is ready to be displayed and update informations.
static void	write_next_line(t_game *game, t_introduction introduction,
					const long last_action)
{
	if (introduction[SENTENCE] == 2
		&& is_millisecond_elapsed(last_action, 1500))
	{
		introduction[SENTENCE] = ENDED;
		play_audio(introduction);
		write_subtitle(game, 0);
		++introduction[CHAPTER];
		introduction[SENTENCE] = 0;
		introduction[LETTER] = WAITING;
	}
	else if (introduction[SENTENCE] != 2
		&& is_millisecond_elapsed(last_action, 1000))
	{
		++introduction[SENTENCE];
		introduction[LETTER] = 0;
	}
}

// 💬 Writes a character on the window at the specified position.
size_t	write_on_windows(t_game *game,
					const char character, t_vector position)
{
	t_index	character_index;

	if (character >= 'a' && character <= 'z')
		character_index = character - 'a';
	else if (character >= 'A' && character <= 'Z')
		character_index = character - 'A';
	else if (character == '!')
		character_index = EXCLAMATION;
	else if (character == ',')
		character_index = COMMA;
	if (character == ',')
		display_image(game->window, game->alphabet[character_index],
			(t_vector){position[X], position[Y] + game->alphabet[0]->height});
	else
		display_image(game->window, game->alphabet[character_index],
			(t_vector){position[X], position[Y]});
	if (character == 'i' || character == 'I'
		|| character == 'j' || character == 'J')
		return (game->alphabet[character_index]->width + game->speed);
	return (game->alphabet[character_index]->width + game->speed);
}

// 💬 Plays the audio corresponding to the moment.
static void	play_audio(const t_introduction introduction)
{
	const t_path	sound[3][3] = {
	{"arguing", "angry", "horn"},
	{"march", "gallop", "neigh"},
	{"peace", "duel", "war"}
	};

	if (!introduction[LETTER])
	{
		play_sound(sound[introduction[CHAPTER]][introduction[SENTENCE]],
			UNDEFINED);
		play_sound(append_character(STORYTELLER_PATH,
				introduction[CHAPTER] * 3 + introduction[SENTENCE] + '1'),
			UNDEFINED);
	}
	if (introduction[SENTENCE] > 2)
	{
		stop_sound();
		play_sound(append_character(SHEET_PATH, introduction[CHAPTER] + '1'),
			UNDEFINED);
	}
}
