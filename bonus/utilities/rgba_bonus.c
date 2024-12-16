/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rgba_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aheitz <aheitz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 10:50:19 by adesille          #+#    #+#             */
/*   Updated: 2024/12/12 16:01:33 by aheitz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

unsigned int	get_rgba(const t_rgba rgba)
{
	return ((rgba[R] << 24) | (rgba[G] << 16) | (rgba[B] << 8) | rgba[A]);
}