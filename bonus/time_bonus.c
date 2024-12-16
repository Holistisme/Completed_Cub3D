/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aheitz <aheitz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/11 14:24:17 by aheitz            #+#    #+#             */
/*   Updated: 2024/12/12 16:02:11 by aheitz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

// 💬 Checks if the specified time has elapsed.
t_bool	is_millisecond_elapsed(const long start, const long milliseconds)
{
	return ((get_current_time() - start) >= milliseconds);
}

// 💬 Gets the current time in milliseconds.
long	get_current_time(void)
{
	struct timeval	current;

	gettimeofday(&current, NULL);
	return ((current.tv_sec * MILLISECOND) + (current.tv_usec / MILLISECOND));
}

long	get_time(void)
{
	struct timeval	current_time;
	long			precise_time;

	gettimeofday(&current_time, NULL);
	precise_time = (current_time.tv_sec * 1000) + (current_time.tv_usec / 1000);
	return (precise_time);
}
