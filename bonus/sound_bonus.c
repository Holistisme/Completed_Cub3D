/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sound_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aheitz <aheitz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 10:38:48 by aheitz            #+#    #+#             */
/*   Updated: 2024/12/16 11:36:59 by aheitz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

/* ************************************************************************** */

static inline void	*play_sound_thread(void *sound);

/* ************************************************************************** */

extern inline void	play_sound(const t_string name, const long duration)
{
	const long		current_time = get_current_time();
	static long		last_time = 0;
	pthread_t		sound_thread;

	if (duration != UNDEFINED)
	{
		if (current_time - duration < last_time)
			return ;
		last_time = current_time;
	}
	if (pthread_create(&sound_thread, NULL, play_sound_thread, (void *)name)
		!= SUCCESS || pthread_detach(sound_thread) != SUCCESS)
		terminate("Maybe you are not blind, but you are deaf!");
}

static inline void	*play_sound_thread(void *sound)
{
	if (system(append_strings((t_string[6]){APLAY, SOUNDS_PATH,
				(t_string)sound, WAV, MUTE, NULL})) == FAILURE)
		terminate("System looks like it has no faith in the sound!");
	pthread_exit(NULL);
}

extern inline void	stop_sound(void)
{
	if (system(append_strings((t_string[4]){KILLALL, APLAY, MUTE, NULL}))
		== FAILURE)
		terminate("A sonic PTSD seems to stay in your ears forever!");
}
