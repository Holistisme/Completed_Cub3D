/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adesille <adesille@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/09 09:58:01 by aheitz            #+#    #+#             */
/*   Updated: 2024/12/15 12:24:18 by adesille         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

static void	check_arguments(const int argc, const t_string *argv);
static void	open_cub_file(const t_string path, t_fd *fd);

// 💬 Main function: initializes, sets up the scene, and starts the game.
int	main(int argc, char *argv[])
{
	t_game	*game;

	check_arguments(argc, argv);
	set_memory((void **)&game, sizeof(t_game));
	set_memory((void **)&game->scene, sizeof(t_scene));
	set_memory((void **)&game->scale, sizeof(t_scale));
	open_cub_file(argv[1], &game->scene->fd);
	set_scene(game);
	game->title = append_strings((t_string[4]){GAME_TITLE, " - ", argv[1],
			NULL});
	game->title[get_string_length(game->title) - 4] = CUT_EXTENSION;
	if (is_same_string(argv[1], "maps/jerusalem.cub"))
		game->scene->environment = JERUSALEM;
	else if (is_same_string(argv[1], "maps/hell.cub"))
		game->scene->environment = HELL;
	else if (is_same_string(argv[1], "maps/heaven.cub"))
		game->scene->environment = HEAVEN;
	play(game);
	stop_sound();
	set_memory(NULL, 0);
	return (EXIT_SUCCESS);
}

// 💬 Checks if correct number of arguments is provided and validates extension.
static void	check_arguments(const int argc, const t_string *argv)
{
	size_t	length;

	if (argc != 2)
	{
		if (argc == 1)
			terminate("Need a map where you can prove you have been chosen!");
		terminate("You don't have the prerequisites to be omnipresent!");
	}
	length = get_string_length(argv[1]);
	if ((length < 4 || !is_same_string(&argv[1][length - 4], CUB)))
		terminate("The Eschatological Confrontation map must be a .cub file!");
}

// 💬 Opens the file at the given path and handles errors if cannot be opened.
static void	open_cub_file(const t_string path, t_fd *fd)
{
	*fd = open(path, O_RDONLY);
	if (*fd == FAILURE)
		terminate("If I can't open map, Gates of Heaven will remain closed!");
	manage_cub_fd(*fd);
}
