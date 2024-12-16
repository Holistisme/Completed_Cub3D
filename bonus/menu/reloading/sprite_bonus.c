/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprite_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aheitz <aheitz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/13 14:34:35 by aheitz            #+#    #+#             */
/*   Updated: 2024/12/14 19:06:32 by aheitz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

/* ************************************************************************** */

#define SPRITES_BINARY  ".save/sprites.dat"

static inline bool	handle_sprites_data(t_game *game, FILE *save,
						bool (*function)(t_sprite *, FILE *));
static bool		write_sprite_data(t_sprite *sprite, FILE *save);
static bool		read_sprite_data(t_sprite *sprite, FILE *save);

/* ************************************************************************** */

bool	load_sprites(t_game *game)
{
	FILE	*save;
	bool	success;

	success = false;
	save = open_file(SPRITES_BINARY, READ_BINARIES);
	if (save && check_key(save, SPRITES_BINARY)
		&& read_file(&game->doors_cast, sizeof(t_doors_cast), 1, save)
		&& read_file(&game->doors_count, sizeof(int), 1, save))
	{
		success = handle_sprites_data(game, save, read_sprite_data);
		close_file(save, SPRITES_BINARY);
	}
	return (success);
}

bool	save_sprites(t_game *game)
{
	FILE	*save;
	bool	success;

	success = false;
	save = open_file(SPRITES_BINARY, WRITE_BINARIES);
	if (save)
	{
		if (write_key(save)
			&& write_file(&game->doors_cast, sizeof(t_doors_cast), 1, save)
			&& write_file(&game->doors_count, sizeof(int), 1, save))
			success = handle_sprites_data(game, save, write_sprite_data);
		close_file(save, SPRITES_BINARY);
	}
	return (success);
}

static inline bool	handle_sprites_data(t_game *game, FILE *save,
							bool (*function)(t_sprite *, FILE *))
{
	t_index	i;

	i = 0;
	while (i < 36)
		if (!function(&game->sprite[i++], save))
			return (false);
	return (true);
}

static bool	write_sprite_data(t_sprite *sprite, FILE *save)
{
	return (write_file(&sprite->position, sizeof(t_double_vector), 1, save)
		&& write_file(&sprite->is_alive, sizeof(bool), 1, save)
		&& write_file(&sprite->collision_buffer, sizeof(bool), 1, save)
		&& write_file(&sprite->type, sizeof(int), 1, save)
		&& write_file(&sprite->start_sound, sizeof(long), 1, save)
		&& write_file(&sprite->y_wall, sizeof(int), 1, save)
		&& write_file(&sprite->x_wall, sizeof(int), 1, save)
		&& write_file(&sprite->direction, sizeof(t_double_vector), 1, save)
		&& write_file(&sprite->items_collected, sizeof(int), 1, save)
		&& write_file(&sprite->transformation, sizeof(bool), 1, save)
		&& write_file(&sprite->transformed, sizeof(bool), 1, save)
		&& write_file(&sprite->transform_deformation, sizeof(int), 1, save)
		&& write_file(&sprite->hit, sizeof(bool), 1, save)
		&& write_file(&sprite->collectible_collected, sizeof(bool), 1, save)
		&& write_file(&sprite->eject_direction,
			sizeof(t_double_vector), 1, save)
		&& write_file(&sprite->items_given, sizeof(bool), 1, save)
		&& write_file(&sprite->dead, sizeof(bool), 1, save)
		&& write_file(&sprite->death_time, sizeof(long), 1, save)
		&& write_file(&sprite->in_crosshair, sizeof(bool), 1, save)
		&& write_file(&sprite->life, sizeof(int), 1, save)
		&& write_file(&sprite->speed, sizeof(float), 1, save)
		&& write_file(&sprite->hit_deformation, sizeof(int), 1, save));
}

static bool	read_sprite_data(t_sprite *sprite, FILE *save)
{
	return (read_file(&sprite->position, sizeof(t_double_vector), 1, save)
		&& read_file(&sprite->is_alive, sizeof(bool), 1, save)
		&& read_file(&sprite->collision_buffer, sizeof(bool), 1, save)
		&& read_file(&sprite->type, sizeof(int), 1, save)
		&& read_file(&sprite->start_sound, sizeof(long), 1, save)
		&& read_file(&sprite->y_wall, sizeof(int), 1, save)
		&& read_file(&sprite->x_wall, sizeof(int), 1, save)
		&& read_file(&sprite->direction, sizeof(t_double_vector), 1, save)
		&& read_file(&sprite->items_collected, sizeof(int), 1, save)
		&& read_file(&sprite->transformation, sizeof(bool), 1, save)
		&& read_file(&sprite->transformed, sizeof(bool), 1, save)
		&& read_file(&sprite->transform_deformation, sizeof(int), 1, save)
		&& read_file(&sprite->hit, sizeof(bool), 1, save)
		&& read_file(&sprite->collectible_collected, sizeof(bool), 1, save)
		&& read_file(&sprite->eject_direction, sizeof(t_double_vector), 1, save)
		&& read_file(&sprite->items_given, sizeof(bool), 1, save)
		&& read_file(&sprite->dead, sizeof(bool), 1, save)
		&& read_file(&sprite->death_time, sizeof(long), 1, save)
		&& read_file(&sprite->in_crosshair, sizeof(bool), 1, save)
		&& read_file(&sprite->life, sizeof(int), 1, save)
		&& read_file(&sprite->speed, sizeof(float), 1, save)
		&& read_file(&sprite->hit_deformation, sizeof(int), 1, save));
}
