/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   typedefs.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aheitz <aheitz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/09 11:38:59 by aheitz            #+#    #+#             */
/*   Updated: 2024/12/10 12:34:26 by aheitz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TYPEDEFS_H
# define TYPEDEFS_H

# include "cub3d.h"

typedef char			t_orientation[4];

typedef char			*t_string;
typedef char			*t_path;
typedef char			**t_map;

typedef unsigned char	t_bit;
typedef unsigned char	t_rgba[4];

typedef int				t_index;
typedef int				t_fd;
typedef int				t_vector[2];

typedef int				t_texture_pixel[3];
typedef int				t_draw[2];
typedef int				t_rgba_color;

typedef double			t_double_vector[2];

typedef struct s_memory
{
	void				*allocation;
	struct s_memory		*previous;
}						t_memory;

typedef struct s_line
{
	t_string			content;
	struct s_line		*next;
}						t_line;

typedef struct s_raycast
{
	t_vector			pixel;
	t_vector			grid;
	t_double_vector		ray;
	t_double_vector		delta;
	t_double_vector		step;
	t_double_vector		side;
	int					axis;
	int					i;
	bool				x_side;
	int					height;
	double				camera;
	double				perpendicular_distance;
	t_draw				draw;
	double				wall_y;
}						t_raycast;

typedef enum e_player_element
{
	POSITION			= 0,
	DIRECTION			= 1,
	PLANE				= 2
}						t_player_element;

typedef struct s_game
{
	mlx_t				*window;
	mlx_image_t			*frame;
	t_raycast			raycast;
	t_fd				fd;
	t_map				map;
	uint32_t			height;
	uint32_t			width;
	mlx_image_t			*texture[4];
	size_t				elements;
	t_rgba_color		ceiling;
	t_rgba_color		floor;
	t_double_vector		player[3];
}						t_game;

#endif