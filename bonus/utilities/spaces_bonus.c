/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   spaces_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aheitz <aheitz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/10 11:06:53 by aheitz            #+#    #+#             */
/*   Updated: 2024/12/12 16:01:36 by aheitz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

static t_bool	is_space(const char character);

// 💬 Skips leading spaces in the given string.
void	ignore_spaces(t_string *line)
{
	while (**line == SPACE)
		++*line;
}

// 💬 Removes trailing spaces from the given string.
void	remove_trailing_spaces(const t_string line)
{
	t_index	index;

	index = get_string_length(line);
	while (index && is_space(line[index - 1]))
		--index;
	if (line)
		line[index] = '\0';
}

// 💬 Checks if the character is a space, tab, or carriage return.
static t_bool	is_space(const char character)
{
	return (character == SPACE || (character >= TAB && character <= CARRIAGE));
}
