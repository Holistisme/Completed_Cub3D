/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   spaces.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aheitz <aheitz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/10 11:06:53 by aheitz            #+#    #+#             */
/*   Updated: 2024/12/10 11:28:10 by aheitz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/* ************************************************************************** */

extern inline void	ignore_spaces(t_string *line)
{
	while (**line == SPACE)
		++*line;
}

extern inline void	remove_trailing_spaces(t_string line)
{
	t_index	index;

	index = get_string_length(line);
	while (index && (line[index - 1] == SPACE
			|| (line[index - 1] >= TAB && line[index - 1] <= CARRIAGE)))
		--index;
	if (line)
		line[index] = 0;
}
