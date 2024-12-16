/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_bonus.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aheitz <aheitz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/27 11:36:51 by aheitz            #+#    #+#             */
/*   Updated: 2024/12/14 16:43:22 by aheitz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

/* ************************************************************************** */

extern inline bool	check_key(FILE *file, const t_path binary)
{
	uint16_t	key;

	if (!read_file(&key, sizeof(uint16_t), 1, file))
		return (false);
	if (key != CODE)
	{
		ft_write(STDERR_FILENO, "Cheating is a sin!\n", 19);
		if (close_file(file, binary))
			delete_available_binary(binary);
	}
	return (key == CODE);
}

extern inline bool	write_key(FILE *file)
{
	const uint16_t	key = CODE;

	return (write_file(&key, sizeof(uint16_t), 1, file));
}
