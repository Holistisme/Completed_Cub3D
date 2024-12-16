/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   defines_bonus.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adesille <adesille@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/09 15:07:38 by aheitz            #+#    #+#             */
/*   Updated: 2024/12/14 12:44:04 by adesille         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DEFINES_BONUS_H
# define DEFINES_BONUS_H

# include "cub3d_bonus.h"

# define R						0
# define G						1
# define B						2
# define A						3
# define OFFSET					2

# define START					0
# define END					1

# define WIDTH					0
# define HEIGHT					1
# define EXCLAMATION			26
# define COMMA					27

# define WAITING				-1
# define CHAPTER				0
# define SENTENCE				1
# define LETTER					2
# define ENDED					3

# define SUCCESS				0
# define CLOSE					0
# define FAILURE				-1

# define LEFT_TOP_CORNER		0
# define SUBTITLE_X				600
# define SUBTITLE_Y				1600

# define X 						0
# define Y 						1
# define DEGREE					0.017453293
# define CLOCKWISE				1

# define MILLISECOND			1000
# define SECOND					1000000

# define NORTH_SIDE				0
# define SOUTH_SIDE				1
# define WEST_SIDE				2
# define EAST_SIDE				3

# define SPACE					' '
# define CHECKED				'#'
# define CARRIAGE				'\r'
# define NEWLINE				'\n'
# define CUT_EXTENSION			'\0'
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
# define PNG					".png"
# define PNG_MAJOR				".PNG"
# define XPM42					".xpm42"
# define XPM42_MAJOR			".XPM42"
# define WAV					".wav"

# define EXTERNAL				" #"

# define WRITE_BINARIES			"wb"
# define READ_BINARIES			"rb"

# define ALPHABET_PATH			"./textures/alphabet/"
# define SHEET_PATH				"./sheet/"
# define SOUNDS_PATH			"./bonus/sounds/"
# define STORYTELLER_PATH		"./storyteller/"

# define APLAY					"aplay "
# define KILLALL				"killall "
# define MUTE					" > /dev/null 2>&1 &"

# define GAME_TITLE				"Divine Brawl"

# define CAMPAIGN_BINARY		"./.save/campaign.dat"
# define SETTINGS_BINARY		"./.save/settings.dat"

# define PI     				3.1415926535

# define WIDTH					0
# define HEIGHT					1
# define WIDTH_SIZE 			1000
# define HEIGHT_SIZE			1000

# define WALL_COLOR             0x000000FF
# define FLOOR_COLOR            0x00FFF0FF
# define PLAYER_COLOR           0x013800FF
# define EMPTY_COLOR            0xFFFFFFFF
# define GREY                   0x808080FF
# define RED                    0xFF0000FF
# define BLUE                   0x0000FFFF
# define GREEN                  0x00FF00FF
# define YELLOW                 0xFFFF00FF
# define ORANGE                 0xFFA500FF
# define PURPLE                 0x800080FF
# define PINK                   0xFFC0CBFF
# define BROWN                  0xA52A2AFF
# define CYAN                   0x00FFFFFF
# define MAGENTA                0xFF00FFFF
# define LIME                   0xBFFF00FF
# define OLIVE                  0x808000FF
# define MAROON                 0x800000FF
# define NAVY                   0x000080FF
# define TEAL                   0x008080FF
# define INDIGO                 0x4B0082FF
# define VIOLET                 0xEE82EEFF
# define GOLD_COLOR             0xFFD700FF
# define SILVER_COLOR           0xC0C0C0FF
# define BLACK                  0x000000FF
# define WHITE                  0xFFFFFFFF
# define LIGHT_GREY             0xD3D3D3FF
# define DARK_GREY              0xA9A9A9FF
# define LIGHT_BLUE             0xADD8E6FF
# define DARK_BLUE              0x00008BFF
# define LIGHT_GREEN            0x90EE90FF
# define DARK_GREEN             0x006400FF
# define LIGHT_RED              0xFF7F7FFF
# define DARK_RED               0x8B0000FF
# define LIGHT_YELLOW           0xFFFFE0FF
# define DARK_YELLOW            0xFFD700FF
# define GREEN_SCREEN			0xFF00E4FF

# define HD						1280
# define FHD					1920
# define QHD					2560
# define UHD					3840

# define UP_LEFT                0
# define UP_RIGHT               1
# define DOWN_LEFT              2
# define DOWN_RIGHT             3

# define HALF_PLAYER_SIZE       2

# define EPSILON				0.00001

# define OPAQUE					0xFF

# define COMPASS				0
# define ZOOM					1

# define W_KEY					87
# define S_KEY					83
# define A_KEY					65
# define D_KEY					68

# define BAD_GUY1				666
# define BAD_GUY2				667
# define GOOD_GUY				111
# define ITEMS					101
# define SWORD					100

# define ADD					0
# define DELETE					1
# define CLEAR_ALL				2
# define INIT					3
# define MODE					4

# define XX						0
# define YY						1
# define INVISIBLE				0x0

# define CODE					0xC0DE
# define CHILD					0

# define ACHIEVEMENTS_COUNT		3
# define SETTINGS_COUNT			4
# define COPPER					0
# define SILVER					1
# define GOLD					2
# define PROGRESSION			3

#endif