/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   achievements_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aheitz <aheitz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/16 12:18:07 by aheitz            #+#    #+#             */
/*   Updated: 2024/12/12 16:03:59 by aheitz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

/* ************************************************************************** */

static void	set_achievement(t_achievement achievement, t_goal goals);

#define MINUTE	60000
#define MILE	6000

/* ************************************************************************** */

extern inline void	display_achievement(t_legacies *legacies,
				const t_index factor)
{
	static t_index	index = 0;

	if (factor)
		play_sound("wheel", WHEEL);
	legacies->image[index]->enabled = false;
	legacies->descriptions[index]->enabled = false;
	index += factor;
	if (index < 0)
		index = ACHIEVEMENTS_COUNT - 1;
	else if (index == ACHIEVEMENTS_COUNT)
		index = 0;
	legacies->image[index]->enabled = true;
	legacies->descriptions[index]->enabled = true;
	draw_progress(legacies, legacies->achievement[index]);
}

void	set_achievements(t_achievements_list achievement)
{
	set_achievement(achievement[WALK], (t_goal){MILE / 10, MILE / 5, MILE / 2});
	set_achievement(achievement[WATCH], (t_goal){4200, 4200 * 3, 4200 * 5});
	set_achievement(achievement[PLAY],
		(t_goal){MINUTE, 3 * MINUTE, 5 * MINUTE});
}

static void	set_achievement(t_achievement achievement, t_goal goals)
{
	t_index	rank;

	rank = COPPER;
	while (rank <= GOLD)
		achievement[rank++] = *goals++;
}

extern inline void	update_achievement(t_achievements_list list,
					const t_index achievement, const t_progress progress)
{
	list[achievement][PROGRESSION] += progress;
	save_achievements(list);
}
