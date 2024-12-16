/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aheitz <aheitz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/11 11:41:38 by aheitz            #+#    #+#             */
/*   Updated: 2024/12/12 16:02:32 by aheitz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

static void	read_next_character(const t_fd fd, char *save);

// 💬 Reads the next line from the file descriptor.
t_string	get_next_line(const t_fd fd)
{
	t_string	next_line;
	char		next_character;

	next_line = NULL;
	next_character = 0;
	while (next_character != NEWLINE)
	{
		read_next_character(fd, &next_character);
		if (!next_character || (next_line && next_character == NEWLINE))
			break ;
		next_line = append_character(next_line, next_character);
	}
	return (next_line);
}

// 💬 Reads the next character from the file descriptor.
static void	read_next_character(const t_fd fd, char *save)
{
	static t_string	buffer = NULL;
	ssize_t			number_read;

	if (!buffer)
		set_memory((void **)&buffer, 2);
	number_read = read(fd, buffer, 1);
	if (number_read > 0)
		*save = *buffer;
	else if (number_read == FAILURE)
		terminate("Could not read file!");
	else
		*save = 0;
}

// 💬 Manages the file descriptor for the .cub file.
void	manage_cub_fd(const t_fd context)
{
	static t_fd	fd = 0;

	if (context)
		fd = context;
	else if (fd)
	{
		close(fd);
		fd = 0;
	}
}
