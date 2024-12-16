/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   typedefs_bonus.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aheitz <aheitz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/09 11:38:59 by aheitz            #+#    #+#             */
/*   Updated: 2024/12/16 10:23:29 by adesille         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TYPEDEFS_BONUS_H
# define TYPEDEFS_BONUS_H

# include "cub3d_bonus.h"

typedef enum e_bool
{
	FALSE = 0,
	TRUE = 1
}						t_bool;

typedef enum e_action
{
	UNSET				= -1,
	SET					= 0,
	GET					= 1
}						t_action;

typedef char			t_orientation[4];
typedef char			*t_extension;
typedef char			*t_string;
typedef char			*t_path;
typedef char			**t_map;

typedef unsigned char	t_bit;
typedef int				t_color;
typedef unsigned char	t_rgba[4];

typedef int				t_index;
typedef int				t_fd;
typedef int				t_vector[2];
typedef int				*t_bipoints;
typedef int				t_introduction[3];
typedef int32_t			t_resolution[2];
typedef int32_t			t_position[2];
typedef uint32_t		t_pixel[2];

typedef int				t_texture_pixel[3];
typedef int				t_draw[2];
typedef int				t_rgba_color;

typedef double			t_sensitivity;

typedef double			t_double_vector[2];
typedef double			t_fov;
typedef float			t_float_vector[2];

typedef size_t			t_achievements_list[3][4];
typedef size_t			t_achievement[4];
typedef size_t			t_goal[4];
typedef size_t			t_progress;

typedef enum e_sound_duration
{
	UNDEFINED			= 0,
	CHOICE				= 333,
	WHEEL				= 750,
	MAIN_MUSIC			= 130000,
	ON_EDGE				= 199000,
	WINNING				= 121000,
	DYING				= 130000
}						t_sound_duration;

typedef enum e_button
{
	NEW_CAMPAIGN		= 0,
	RESUME_BATTLE		= 0,
	CONTINUE_CAMPAIGN	= 1,
	SAVE_PROGRESS		= 1,
	MASTER_LEGACIES		= 2,
	EDIT_SETTINGS		= 3,
	EXIT_GAME			= 4,
	ABANDON_BATTLEFIELD	= 4
}						t_button;

typedef struct s_memory
{
	void				*allocation;
	struct s_memory		*previous;
}						t_memory;

typedef struct s_img_manager
{
	mlx_image_t			*allocation;
}						t_img_manager;

typedef struct s_textures
{
	t_path				north;
	t_path				south;
	t_path				west;
	t_path				east;
	t_color				*floor;
	t_color				*ceiling;
}						t_textures;

typedef struct s_line
{
	t_string			content;
	struct s_line		*next;
}						t_line;

typedef struct s_player
{
	t_double_vector		position;
	t_double_vector		direction;
	t_double_vector		prev_direction;
	t_double_vector		plane;
	float				angle;
	int					life;
	bool				dead;
	int					blue_cord_collected;
}						t_player;

typedef enum s_supertexture
{
	CUSTOM				= 0,
	JERUSALEM			= 1,
	HELL				= 2,
	HEAVEN				= 3
}						t_supertexture;

typedef struct s_scene
{
	t_fd				fd;
	t_map				map;
	t_textures			*textures;
	uint32_t			height;
	uint32_t			width;
	size_t				elements;
	t_rgba_color		ceiling;
	t_rgba_color		floor;
	t_supertexture		environment;
}						t_scene;

typedef struct s_scale
{
	uint32_t			element_height;
	uint32_t			element_width;
	uint32_t			pos[2];
	uint32_t			yy_start;
	uint32_t			xx_start;
	uint32_t			map_height;
	uint32_t			map_width;
	uint32_t			x_corner;
	uint32_t			y_corner;
	size_t				minimap_size;
	int					corner;
	t_map				**map;
	int					compass_width;
	int					compass_heigth;
	double				factor;
}						t_scale;

typedef struct s_minimap
{
	uint32_t			x;
	uint32_t			y;
	uint32_t			xx;
	uint32_t			yy;
}						t_minimap;

typedef struct s_data_cast
{
	t_vector			grid;
	t_double_vector		delta;
	t_double_vector		step;
	t_double_vector		side;
	int					axis;
	int					i;
}						t_data_cast;

typedef struct s_door_cast
{
	t_vector			grid;
	t_double_vector		step;
	int					height;
	double				perpendicular_distance;
	t_bool				x_side;
	bool				closed_door;
}						t_door_cast;

typedef struct s_raycast
{
	mlx_image_t			*texture;
	mlx_image_t			*floor;
	mlx_image_t			*bad_guy[2];
	mlx_image_t			*good_guy[4];
	mlx_image_t			*crusader1[5];
	mlx_image_t			*crusader2[5];
	mlx_image_t			*crusader3[5];
	mlx_image_t			*holy_item;
	mlx_image_t			*crusader_death;
	mlx_image_t			*gun[3];
	mlx_image_t			*gun_aim[3];
	mlx_image_t			*gun_reload[6];
	mlx_image_t			*crossbow[3];
	mlx_image_t			*crossbow_aim[3];
	mlx_image_t			*crossbow_reload[2];
	mlx_image_t			*bleeding;
	long				bleeding_start_time;
	mlx_image_t			*gaspar_item;
	int					enemy_flag;
	int					t_flag;
	t_double_vector		position;
	t_double_vector		ray;
	t_bool				hit;
	t_bool				x_side;
	bool				door;
	bool				draw_door;
	double				camera;
	double				perpendicular_distance;
	int					height;
	t_vector			pixel;
	int					texture_x;
	int					ceiling_x;
	double				time;
	int					map[2];
	double				wall_dist;
	int					draw_start;
	int					draw_end;

	int					temperature_shift;
	int					luminosity_shift;
	int					r_blue_offset;
	int					r_red_offset;
	int					r_green_offset;

	long				start_time;
	long				current_time;
	t_door_cast			door_cast[5];
	int					doors_to_draw;
}						t_raycast;

typedef struct s_sprite
{
	t_double_vector		position;
	mlx_image_t			*texture;
	bool				is_alive;
	bool				collision_buffer;
	int					type;
	long				start_sound;
	int					y_wall;
	int					x_wall;
	t_double_vector		direction;
	int					items_collected;
	bool				transformation;
	bool				transformed;
	int					transform_deformation;
	bool				hit;
	bool				collectible_collected;
	t_double_vector		eject_direction;
	bool				items_given;
	bool				dead;
	long				death_time;
	bool				in_crosshair;
	int					life;
	float				speed;
	int					hit_deformation;
}						t_sprite;

typedef struct s_sprite_cast
{
	int					sprite_screen_x;
	int					sprite_height;
	int					sprite_width;
	t_double_vector		transform;
	double				inv_det;
	int					i;
	int					draw_start_x;
	int					draw_end_x;
	int					draw_start_y;
	int					draw_end_y;
	int					x;
	int					y;
	int					tex_x;
	int					tex_y;
	int					vertical_offset;
	int					jump_height;
	int					jump_duration;
	int					jump_frame;
	bool				is_jumping;
}						t_sprite_cast;

typedef struct s_doors_cast
{
	t_vector			pos[100];
	bool				is_open[100];
	bool				is_close[100];
	bool				play_audio[100];
}						t_doors_cast;

typedef enum e_title
{
	WALK				= 0,
	WATCH				= 1,
	PLAY				= 2
}						t_title;

typedef enum e_direction
{
	LEFT_SIDE			= -2,
	DOWNSIDE			= -1,
	UPSIDE				= 1,
	RIGHT_SIDE			= 2
}						t_direction;

typedef enum e_setting
{
	RESOLUTION			= 0,
	SENSITIVITY			= 1,
	DIFFICULTY			= 2,
	SUPERTEXTURE		= 3
}						t_setting;

typedef struct s_settings
{
	mlx_image_t			*frame;
	mlx_image_t			*image[4];
	mlx_image_t			*slide[2];
	bool				animation;
	t_resolution		requested;
	t_scene				*loading_scene;
	size_t				difficulty;
	size_t				resolution;
	t_sensitivity		sensitivity;
	t_index				displayed_setting;
	bool				working;
}						t_settings;

typedef struct s_legacies
{
	mlx_image_t			*frame;
	mlx_image_t			*title;
	mlx_image_t			*star[3];
	mlx_image_t			*gauge[4];
	t_achievements_list	achievement;
	mlx_image_t			*image[ACHIEVEMENTS_COUNT];
	mlx_image_t			*descriptions[ACHIEVEMENTS_COUNT];
	long				ingame_start;
}						t_legacies;

typedef struct s_menu
{
	mlx_image_t			*resolution_window;
	mlx_image_t			*current_resolution;
	mlx_image_t			*blur_frame;
	mlx_image_t			*sword;
	mlx_image_t			*wall_resolution;
	size_t				new_resolution;
	mlx_image_t			*main;
	mlx_image_t			*button;
	mlx_image_t			*selected_button;
	mlx_image_t			*blocked_banner;
	mlx_image_t			*texts[5];
}						t_menu;

typedef struct s_campaign
{
	t_player			player;
	t_scene				scene;
	t_path				texture[4];
	t_supertexture		environment;
}						t_campaign;

typedef struct s_game	t_game;

typedef struct s_game
{
	mlx_t				*window;
	mlx_image_t			*compass;
	t_menu				*menu;
	mlx_image_t			*minimap;
	mlx_image_t			*frame;
	mlx_image_t			*sprites;
	mlx_image_t			*helmet;
	mlx_image_t			*uni_texture;
	mlx_image_t			*end_screen;
	mlx_image_t			*start_screen[6];
	mlx_image_t			*black_screen;
	mlx_image_t			*horror_screen;
	mlx_image_t			*doors[9];
	mlx_image_t			*door;
	t_scene				*scene;
	t_scale				*scale;
	t_string			title;
	t_resolution		resolution;
	t_fov				fov;
	t_player			*player;
	t_sensitivity		sensitivity;
	mlx_image_t			*alphabet[28];
	mlx_image_t			*opening_cinematic[3];
	mlx_image_t			*parchment;
	t_string			story[3][3];
	mlx_image_t			*textures[4];
	t_string			texture_path;
	t_raycast			*raycast;
	t_sprite			sprite[100];
	t_doors_cast		doors_cast;
	int					doors_count;
	bool				transformation;
	bool				dark_mode;
	bool				intro;
	bool				give_collectible_animation;
	bool				brainless_mode;
	bool				crusader_mode;
	bool				shoot_animation;
	bool				reload_animation;
	bool				open_door;
	bool				close_door;
	bool				aiming;
	bool				gun_cheat_code;
	int					bullets;
	int					max_bullets;
	int					screamer_start;
	float				sp_speed;

	double				*zbuffer;
	double				*door_buffer;
	int					sprite_count;
	int					items_count;
	int					vertical_offset;
	int					jump_height;
	int					jump_duration;
	int					jump_frame;
	bool				is_jumping;
	bool				set_uni_texture;
	bool				set_disco_mode;
	int					e_vertical_offset;
	int					e_jump_height;
	int					e_jump_duration;
	int					e_jump_frame;
	int					i_vertical_offset;
	int					i_jump_height;
	int					i_jump_duration;
	int					i_jump_frame;
	t_legacies			*legacies;
	t_settings			*settings;
	double				resize;
	void				(*state)(t_game *);
	void				(*main_menu)(t_game *);
	t_campaign			campaign;
	t_index				speed;
	bool				music;
	bool				restart;
	mlx_image_t			*sky;
	bool				requested_sky;
	mlx_image_t			*floor;
	t_position			intro_vector;
	t_position			intro_prev;
}						t_game;

#endif