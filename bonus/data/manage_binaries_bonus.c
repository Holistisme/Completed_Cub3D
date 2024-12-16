/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_binaries_bonus.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aheitz <aheitz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/27 11:35:33 by aheitz            #+#    #+#             */
/*   Updated: 2024/12/12 16:05:45 by aheitz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

/* ************************************************************************** */

extern inline bool	binary_file_available(const t_path binary)
{
	return (access(binary, F_OK) != FAILURE);
}

extern inline void	delete_available_binary(const t_path binary)
{
	if (binary_file_available(binary))
		remove(binary);
}
