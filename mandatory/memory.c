/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memory.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aheitz <aheitz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/09 11:24:08 by aheitz            #+#    #+#             */
/*   Updated: 2024/12/09 15:01:06 by aheitz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/* ************************************************************************** */

static inline t_memory	*add_memory(t_memory *head);
static inline void		set_allocation(void **target, const size_t size);
static inline void		zero_memory(void *target, size_t size);
static inline void		free_memory(t_memory *manager);

/* ************************************************************************** */

extern inline void	set_memory(void **target, const size_t size)
{
	static t_memory	*manager = NULL;

	if (target)
	{
		manager = add_memory(manager);
		set_allocation(target, size);
		manager->allocation = *target;
	}
	else
		free_memory(manager);
}

static inline t_memory	*add_memory(t_memory *head)
{
	t_memory	*new;

	set_allocation((void **)&new, sizeof(t_memory));
	new->allocation = NULL;
	new->previous = NULL;
	if (head)
		new->previous = head;
	return (new);
}

static inline void	set_allocation(void **target, const size_t size)
{
	*target = NULL;
	if (size)
	{
		*target = malloc(size);
		if (!*target)
			terminate("Looks like there's no more room to allocate your soul!");
		zero_memory(*target, size);
	}
}

static inline void	zero_memory(void *target, size_t size)
{
	while (size)
		((t_bit *)target)[--size] = 0;
}

static inline void	free_memory(t_memory *manager)
{
	t_memory	*target;

	while (manager)
	{
		target = manager;
		manager = manager->previous;
		if (target->allocation)
		{
			free(target->allocation);
			target->allocation = NULL;
		}
		free(target);
	}
}
