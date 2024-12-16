/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   save_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aheitz <aheitz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/20 13:11:39 by aheitz            #+#    #+#             */
/*   Updated: 2024/12/12 16:04:07 by aheitz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

/* ************************************************************************** */

#define ACHIEVEMENTS_BINARY	"./.save/achievements.dat"

/* ************************************************************************** */

void	save_achievements(t_achievements_list achievements)
{
	FILE	*save;

	save = open_file(ACHIEVEMENTS_BINARY, WRITE_BINARIES);
	if (!save || !write_key(save)
		|| !write_file(achievements, sizeof(t_achievements_list), 1, save))
		return ;
	close_file(save, ACHIEVEMENTS_BINARY);
}

void	get_achievements(t_achievements_list list)
{
	FILE				*save;
	t_index				index;
	t_achievements_list	achievement;

	if (!binary_file_available(ACHIEVEMENTS_BINARY))
		return ;
	save = open_file(ACHIEVEMENTS_BINARY, READ_BINARIES);
	if (!save || !check_key(save, ACHIEVEMENTS_BINARY)
		|| !read_file(&achievement, sizeof(t_achievements_list), 1, save))
		return ;
	close_file(save, ACHIEVEMENTS_BINARY);
	index = WALK;
	while (index < ACHIEVEMENTS_COUNT)
	{
		list[index][PROGRESSION] = (achievement[index][PROGRESSION]);
		++index;
	}
}
