/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aheitz <aheitz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/09 09:58:01 by aheitz            #+#    #+#             */
/*   Updated: 2024/12/14 16:34:38 by aheitz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/* ************************************************************************** */

static void	check_arguments(const int argc, const t_string *argv);
static void	open_cub_file(const t_string path, t_fd *fd);

/* ************************************************************************** */

int	main(int argc, char *argv[])
{
	t_game	*game;

	check_arguments(argc, argv);
	set_memory((void **)&game, sizeof(t_game));
	open_cub_file(argv[1], &game->fd);
	game->window = mlx_init(WIDTH_SIZE, HEIGHT_SIZE,
			"Divine Brawl - Free Version", true);
	if (!game->window)
		terminate("Window remains closed, like Heaven for your character!");
	manage_mlx(game->window);
	set_scene(game);
	play(game);
	set_memory(NULL, 0);
	return (EXIT_SUCCESS);
}

static inline void	check_arguments(const int argc, const t_string *argv)
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

static inline void	open_cub_file(const t_string path, t_fd *fd)
{
	*fd = open(path, O_RDONLY);
	if (*fd == FAILURE)
		terminate("If I can't open map, Gates of Heaven will remain closed!");
	manage_cub_fd(*fd);
}

void	terminate(const t_string message)
{
	ft_write(STDERR_FILENO, "Error\n", 7);
	if (message)
	{
		ft_write(STDERR_FILENO, message, get_string_length(message));
		ft_write(STDERR_FILENO, "\n", 1);
	}
	set_memory(NULL, 0);
	manage_cub_fd(CLOSE);
	manage_mlx(NULL);
	exit(EXIT_FAILURE);
}
