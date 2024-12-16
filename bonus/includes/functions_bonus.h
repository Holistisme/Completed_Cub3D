/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   functions_bonus.h                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adesille <adesille@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/09 11:25:43 by aheitz            #+#    #+#             */
/*   Updated: 2024/12/16 11:12:06 by adesille         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FUNCTIONS_BONUS_H
# define FUNCTIONS_BONUS_H

# include "cub3d_bonus.h"

int				main(int argc, char *argv[]);
void			play(t_game *game);
void			init_mlx(t_game *game);
void			set_values_to_0(t_game *game, int i);
void			draw_doors(t_game *game);
void			correct_position(t_game *game, int y, int x,
					t_double_vector *position);
void			init_struct_variables(t_game *game);

void			set_memory(void **target, const size_t size);
void			terminate(const t_string message);
void			manage_cub_fd(const t_fd fd);

void			set_scene(t_game *game);
void			save_textures(t_scene *scene);
t_line			*get_map_content(t_game *game);
t_string		get_next_line(const t_fd fd);

t_string		append_character(t_string source, const char character);
t_string		append_strings(t_string *list);
void			copy_string(t_string source, t_string destination);
size_t			get_string_length(t_string target);

void			ignore_spaces(t_string *line);
void			remove_trailing_spaces(t_string line);

t_bool			is_same_string(t_string first, t_string second);
t_bool			is_in_string(const char character, t_string string);

void			hook_init(t_game *game);
void			rotate(double xpos, double ypos, void *param);
void			manage_animations(t_game *game, keys_t key);
void			cheat_code_check(t_game *game, keys_t key);

void			normalize_data(t_game *game, size_t size_factor, int corner);
void			draw_minimap(void *param);

void			manage_mlx(mlx_t *context);
void			manage_images(t_game *game, mlx_image_t *context, int action);
void			load_textures(t_game *game);
mlx_image_t		*set_texture(mlx_t *window, const t_path file);
size_t			write_on_windows(t_game *game, const char character,
					t_vector position);
void			display_image(mlx_t *window, mlx_image_t *image,
					const t_vector position);
void			load_brainless_intro(t_game *game);
void			load_brainless_textures(t_game *game);
void			load_crusade_textures(t_game *game);
void			load_crossbow_textures(t_game *game);
void			load_gun_textures(t_game *game);
void			delete_gun_textures(t_game *game);
void			delete_crossbow_textures(t_game *game);
void			delete_brainless_intro(t_game *game);
void			delete_brainless_textures(t_game *game);
void			delete_crusade_textures(t_game *game);

void			introduce(t_game *game);
void			set_introduction_message(t_game *game);

uint32_t		which_object(t_game *game, uint32_t y, uint32_t x);
void			manage_zoom(t_game *game, keys_t key);
void			change_corner(t_game *game, int corner);
void			draw_pixel(t_game *game, uint32_t x, uint32_t y,
					uint32_t color);
void			draw_player_direction(t_game *game, double factor);
void			rotate(double xpos, double ypos, void *param);
void			audiovisualize(t_game *game, t_introduction introduction);

t_bool			is_millisecond_elapsed(const long start,
					const long microsecond);
long			get_current_time(void);
long			get_time(void);
bool			skip_chapter(t_game *game, t_action action);

void			calculate_ray_n_delta_dist(t_game *game, t_data_cast *d);
void			calculate_wall_height(t_game *game, t_data_cast *d,
					t_raycast *raycast);
void			determine_step_n_side_dist(t_game *game, t_data_cast *d);
void			do_dda(t_game *game, t_data_cast *d);
void			draw(t_game *game, t_raycast *raycast, t_vector pixel,
					const bool is_horizontal);
int				get_pixel_color(t_raycast *raycast, int texture_pixel_y,
					t_double_vector player_position, mlx_image_t *texture);
unsigned int	get_rgba(const t_rgba rgba);

void			erase_player(t_game *game);
bool			valid_player_collision(t_game *game, int j);

void			display_main_menu(t_game *game);
t_index			selected_image(const t_double_vector mouse,
					const mlx_image_t *button, const t_index instance);
void			click_button(t_game *game, t_index button);
void			master_legacies(t_game *game);
void			display_achievement(t_legacies *legacies, const t_index factor);

void			play_sound(const t_string name, const long duration);
void			update_achievement(t_achievements_list list,
					const t_index achievement, const t_progress progress);
char			*select_death_sound(int n);

mlx_image_t		*set_texture(mlx_t *window, const t_path file);
mlx_image_t		*set_image(t_game *game, const t_path file, t_vector position,
					const bool displayed);
mlx_image_t		*set_image2(t_game *game, const t_path file, t_vector size,
					const bool displayed);

void			display_studio(t_game *game);
void			raycast(t_game *game);
void			pause_game(t_game *game);

bool			load_game(t_game *game);
void			save_game(t_game *game);

bool			write_file(const void *ptr, size_t size, size_t n, FILE *s);
bool			read_file(void *ptr, size_t size, size_t n, FILE *stream);
FILE			*open_file(const char *filename, const char *modes);
bool			close_file(FILE *stream, const t_path file);

void			edit_settings(t_game *game);
void			change_setting(t_game *game, t_index index);

void			set_image_visibility(mlx_instance_t *image, bool reveal);
void			aim_menu(t_game *game);

bool			serialize_scene(FILE *save, const t_scene *scene);
bool			deserialize_scene(FILE *save, t_game *game);
void			delete_available_binary(const t_path binary);

bool			binary_file_available(const t_path binary);

bool			check_key(FILE *file, const t_path binary);
bool			write_key(FILE *file);

void			change_textures(t_game *game, const bool load);

void			set_gauges(t_game *game);

void			draw_progress(t_legacies *legacies, t_achievement achievement);
void			save_achievements(t_achievements_list achievements);

void			stop_sound(void);

mlx_image_t		*create_image(mlx_t *window, const t_pixel dimensions);

void			blur_frame(t_game *game);
;
void			open_menu(t_game *game);

void			initialize_mlx(t_game *game);

void			set_achievements(t_achievements_list achievement);
void			get_achievements(t_achievements_list list);

void			main_hook(void *context);

void			scroll_hook(double xdelta, double ydelta, void *param);
void			mouse_hook(mouse_key_t button, action_t action,
					modifier_key_t mods, void *param);
void			key_hook(mlx_key_data_t keydata, void *param);
int				is_allowed_move(t_game *game, keys_t key);
int				load_fade(t_game *game, t_index image);
bool			fade_intro(t_game *game, const t_path reference);

void			write_subtitle(t_game *game, const char c);

void			set_setting(t_game *game, const int change);
void			display_data(t_game *game);

void			save_settings(t_game *game);
void			load_settings(t_game *game);

void			handle_resolution(t_game *game, const int action);
void			handle_sensitivity(t_game *game, const int action);
void			handle_difficulty(t_game *game, const int action);
void			handle_supertextures(t_game *game);

void			animate_setting(t_game *game, mlx_image_t *image,
					const int direction);

void			set_supertextures(t_game *game);
void			display_sky(t_game *game);
void			display_floor(t_game *game);

void			unset_supertextures(t_game *game);

void			play_ambience(t_game *game, t_action action);
void			draw_floor(t_game *game, t_vector pixel);
void			draw_sky(t_game *game, t_vector pixel, t_vector draw);
void			safe_put_pixel(t_game *game, int32_t pos[2], int color,
					bool is_door);
uint32_t		disco_mode_bro(uint32_t color, float percent);
uint32_t		damage_colorization(uint32_t color, float percent);

int				which_corner(keys_t key);
void			load_images(t_game *game, mlx_image_t **img, int width,
					int height);
void			movements(void *param);
int				is_move_ok(t_game *game, keys_t key);
void			x_move1(t_game *game, int i, int *x_wall,
					t_double_vector position);
void			x_move2(t_game *game, int i, int *x_wall,
					t_double_vector position);
void			y_move1(t_game *game, int i, int *y_wall,
					t_double_vector position);
void			y_move2(t_game *game, int i, int *y_wall,
					t_double_vector position);
void			manage_compass_zoom(t_game *game, keys_t key);
int				set_closest_bad_guy_position(t_game *game, int i,
					t_double_vector *position);
int				set_closest_good_guy_position(t_game *game, int i,
					t_double_vector *position);
void			collision_buffer_management(t_game *game, int i,
					t_double_vector position);

void			update_jump(t_game *game);
void			crossbow_shoot_animation(t_game *game);
void			crossbow_reload_animation(t_game *game);
void			gun_shoot_animation(t_game *game);
void			gun_reload_animation(t_game *game);
void			intro(t_game *game);
void			display_end_screen(t_game *game);
void			set_game_textures(t_game *game);

void			cast_sprites(t_game *game);
void			draw_sprites(t_game *game, t_sprite_cast e, t_sprite *ee);
void			animate_sprites(t_game *game, int i, int *vertical_offset);
void			set_death(t_game *game, t_sprite *sprite);
void			update_texture(t_game *game, int i, int type);
void			update_jump_enemy(t_game *game);
void			update_floating_items(t_game *game);
void			make_dat_heresy_move(t_game *game, int i);
void			betrayal_effect(t_game *game);

void			calculate_door_height(t_game *game, t_door_cast *door_cast);
void			draw_door(t_game *game, t_raycast *raycast, t_draw draw,
					t_vector pixel);
void			door_management(t_game *game, int i);
int				return_door_index(t_game *game, t_vector pos);
int				is_door(t_game *game, uint32_t x, uint32_t y);

void			init_sprites(t_game *game, int i);

bool			load_sprites(t_game *game);
bool			save_sprites(t_game *game);

size_t			enemies_remaining(t_game *game);
void			display_endgame(t_game *game);

void			ft_write(int fildes, const void *buf, size_t nbyte);

#endif