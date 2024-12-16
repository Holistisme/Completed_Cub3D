/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   functions.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aheitz <aheitz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/09 11:25:43 by aheitz            #+#    #+#             */
/*   Updated: 2024/12/16 10:21:16 by aheitz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FUNCTIONS_H
# define FUNCTIONS_H

# include "cub3d.h"

int				main(int argc, char *argv[]);
void			terminate(const t_string message);
void			play(t_game *game);

void			correct_position(t_game *game, int y, int x,
					t_double_vector *position);

void			set_memory(void **target, const size_t size);

t_string		get_next_line(const t_fd fd);
void			manage_cub_fd(const t_fd context);

void			set_scene(t_game *game);
void			save_textures(t_game *game);

void			manage_mlx(mlx_t *context);
void			key_hook(mlx_key_data_t keydata, void *param);
void			raycast(void *context);

t_line			*get_map_content(t_game *game);

void			ignore_spaces(t_string *line);
void			remove_trailing_spaces(t_string line);

t_string		append_character(t_string source, const char character);
void			copy_string(t_string source, t_string destination);
bool			is_same_string(t_string first, t_string second);
size_t			get_string_length(t_string string);
bool			is_in_string(const char character, t_string string);

void			draw(t_game *game);
unsigned int	get_rgba(const t_rgba rgba);

void			ft_write(int fildes, const void *buf, size_t nbyte);

#endif