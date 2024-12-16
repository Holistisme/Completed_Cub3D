/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   string_handling_bonus.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aheitz <aheitz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/30 10:30:52 by aheitz            #+#    #+#             */
/*   Updated: 2024/12/12 16:01:39 by aheitz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

// 💬 Appends a character to the string and return the result.
t_string	append_character(t_string source, const char character)
{
	t_string		appended;
	const size_t	length = get_string_length(source);

	set_memory((void **)&appended, length + 2);
	copy_string(source, appended);
	appended[length] = character;
	return (appended);
}

// 💬 Concatenates the strings in the list and returns the result.
t_string	append_strings(t_string *list)
{
	t_string	appended;
	size_t		length;
	t_index		index;

	index = 0;
	length = 0;
	while (list[index])
		length += get_string_length(list[index++]);
	set_memory((void **)&appended, length + 1);
	while (*list)
		copy_string(*list++, appended + get_string_length(appended));
	return (appended);
}

// 💬 Copies the source string to the destination string.
void	copy_string(t_string source, t_string destination)
{
	if (source && destination)
		while (*source)
			*destination++ = *source++;
}
