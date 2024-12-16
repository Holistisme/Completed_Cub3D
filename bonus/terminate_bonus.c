/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   terminate_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adesille <adesille@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/10 11:22:30 by aheitz            #+#    #+#             */
/*   Updated: 2024/12/15 12:27:19 by adesille         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

// 💬 Prints an error message to STDERR and terminates the program.
void	terminate(const t_string message)
{
	ft_write(STDERR_FILENO, "Error\n", 7);
	if (message)
	{
		ft_write(STDERR_FILENO, message, get_string_length(message));
		ft_write(STDERR_FILENO, "\n", 1);
	}
	set_memory(NULL, 0);
	manage_cub_fd(CLOSE);
	stop_sound();
	manage_mlx(NULL);
	exit(EXIT_FAILURE);
}

// 💬 Manages the MLX context, initializing or terminating it as needed.
void	manage_mlx(mlx_t *context)
{
	static mlx_t	*mlx = NULL;

	if (context)
		mlx = context;
	else if (mlx)
	{
		mlx_terminate(mlx);
		mlx = NULL;
	}
}

int	ft_strcmp(char *str1, char *str2)
{
	size_t	i;

	i = 0;
	if (!str1 || !str2)
		return (-1);
	while (str1[i] && str2[i])
	{
		if (str1[i] != str2[i])
			return ((unsigned char)str1[i] - (unsigned char)str2[i]);
		i++;
	}
	if (!str1[i] && !str2[i])
		return (0);
	return ((unsigned char)str1[i] - (unsigned char)str2[i]);
}
