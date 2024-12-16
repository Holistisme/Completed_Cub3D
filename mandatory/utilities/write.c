/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   write.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aheitz <aheitz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/14 16:16:19 by aheitz            #+#    #+#             */
/*   Updated: 2024/12/14 16:30:22 by aheitz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	ft_write(int fildes, const void *buf, size_t nbyte)
{
	const ssize_t	result = write(fildes, buf, nbyte);

	return ((void)result);
}
