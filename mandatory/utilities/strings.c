/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   strings.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aheitz <aheitz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/30 10:30:52 by aheitz            #+#    #+#             */
/*   Updated: 2024/12/09 14:54:58 by aheitz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/* ************************************************************************** */

extern inline t_string	append_character(t_string source, const char character)
{
	t_string		appended;
	const size_t	length = get_string_length(source);

	set_memory((void **)&appended, length + 2);
	copy_string(source, appended);
	appended[length] = character;
	return (appended);
}

extern inline void	copy_string(t_string source, t_string destination)
{
	if (source && destination)
		while (*source)
			*destination++ = *source++;
}

extern inline bool	is_same_string(t_string first, t_string second)
{
	while (*first && *second)
		if (*first++ != *second++)
			return (false);
	return (*first == *second);
}

extern inline size_t	get_string_length(t_string string)
{
	const t_string	start = string;

	if (string)
		while (*string)
			string++;
	return (string - start);
}

extern inline bool	is_in_string(const char character, t_string string)
{
	while (*string)
		if (*string++ == character)
			return (true);
	return (false);
}
