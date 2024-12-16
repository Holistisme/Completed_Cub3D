/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   defines.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aheitz <aheitz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/09 15:07:38 by aheitz            #+#    #+#             */
/*   Updated: 2024/12/16 10:15:54 by aheitz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DEFINES_H
# define DEFINES_H

# include "cub3d.h"

# define WIDTH_SIZE				3000
# define HEIGHT_SIZE			1500
# define UNSET					-1
# define FOV					1.047197551

# define R						0
# define G						1
# define B						2
# define A						3

# define OFFSET					2

# define START					0
# define END					1

# define CLOSE					0
# define FAILURE				-1

# define X 						0
# define Y 						1
# define DEGREE					0.017453293
# define CLOCKWISE				1

# define NORTH_SIDE				0
# define SOUTH_SIDE				1
# define WEST_SIDE				2
# define EAST_SIDE				3

# define SPACE					' '
# define CHECKED				'#'
# define CARRIAGE				'\r'
# define NEWLINE				'\n'
# define TAB					'\t'

# define WALL					'1'
# define NORTH					'N'
# define SOUTH					'S'
# define WEST					'W'
# define EAST					'E'

# define AUTHORIZED_CHARACTERS	" 01NSEW"
# define PLAYER_ORIENTATIONS	"NSEW"
# define BASIC_POSITIONS		" 01"

# define CUB					".cub"

# define EXTERNAL				" #"

# define PI     				3.1415926535

# define OPAQUE					0xFF

#endif