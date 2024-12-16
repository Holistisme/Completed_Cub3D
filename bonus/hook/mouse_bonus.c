/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aheitz <aheitz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/30 12:58:21 by aheitz            #+#    #+#             */
/*   Updated: 2024/12/12 16:05:26 by aheitz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

/* ************************************************************************** */

#define ALPHA	2

/* ************************************************************************** */

void	mouse_hook(mouse_key_t button, action_t action,
					modifier_key_t mods, void *param)
{
	t_game	*game;
	t_index	index;

	(void)mods;
	game = (t_game *)param;
	if ((game->state == &display_main_menu || game->state == &pause_game)
		&& action == MLX_PRESS && (button == MLX_MOUSE_BUTTON_LEFT))
	{
		index = 0;
		while (index < 5)
			if (game->menu->selected_button->instances[index++].enabled)
				return (click_button(game, index - 1));
	}
	else if (game->state != &raycast && game->state != &display_main_menu
		&& action == MLX_PRESS && button == MLX_MOUSE_BUTTON_RIGHT)
		game->state(game);
}

t_index	selected_image(const t_double_vector mouse, const mlx_image_t *button,
					const t_index instance)
{
	int	pixel[3];

	if (mouse[X] > (int)button->instances[instance].x
		&& mouse[X] < (int)(button->instances[instance].x + button->width)
		&& mouse[Y] > (int)button->instances[instance].y
		&& mouse[Y] < (int)(button->instances[instance].y + button->height))
	{
		pixel[X] = (int)mouse[X] - button->instances[instance].x;
		pixel[Y] = (int)mouse[Y] - button->instances[instance].y;
		pixel[ALPHA]
			= button->pixels[(pixel[Y] * button->width + pixel[X]) * 4 + A];
		if (pixel[ALPHA])
			return (instance);
	}
	return (-1);
}
