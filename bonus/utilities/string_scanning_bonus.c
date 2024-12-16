/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   string_scanning_bonus.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aheitz <aheitz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/30 10:30:49 by aheitz            #+#    #+#             */
/*   Updated: 2024/12/12 16:01:42 by aheitz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

// 💬 Checks if the two strings are identical.
t_bool	is_same_string(t_string first, t_string second)
{
	while (*first && *second)
		if (*first++ != *second++)
			return (FALSE);
	return (*first == *second);
}

// 💬 Returns the length of the given string.
size_t	get_string_length(t_string string)
{
	const t_string	start = string;

	if (string)
		while (*string)
			string++;
	return (string - start);
}

// 💬 Checks if the character is present in the given string.
t_bool	is_in_string(const char character, t_string string)
{
	while (*string)
		if (*string++ == character)
			return (TRUE);
	return (FALSE);
}
