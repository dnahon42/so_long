/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dnahon <dnahon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/15 13:10:17 by dnahon            #+#    #+#             */
/*   Updated: 2025/06/30 12:54:43 by dnahon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H

typedef struct s_counts
{
	int			exit_count;
	int			player_count;
	int			item_count;
	int			enemy_count;
	int			wrong;
}				t_counts;

typedef struct s_data
{
	t_counts	counts;
	void		*player;
	void		*player_left;
	void		*current_player_img;
	int			player_width;
	int			player_height;
	int			x;
	int			y;
	int			player_found;

	void		*enemy;
	void		*enemy_left;
	void		*current_enemy_img;
	int			enemy_width;
	int			enemy_height;
	int			enemy_x;
	int			enemy_y;
	int			enemy_on_collectible;

	void		*wall;
	int			wall_width;
	int			wall_height;

	void		*exit;
	void		*exit_opened;
	int			exit_width;
	int			exit_height;
	int			exit_found;

	void		*floor;
	int			floor_width;
	int			floor_height;

	void		*collectible;
	int			collectible_width;
	int			collectible_height;
	int			collected_items;
	int			total_collectibles;
	int			collectibles_found;

	int			win_height;
	int			win_width;
	void		*mlx;
	void		*win;
	int			movements;
	char		**map;
}				t_data;

typedef struct s_pos
{
	int			x;
	int			y;
	int			enemy_x;
	int			enemy_y;
}				t_pos;

void			free_map(char **map);
void			free_map_copy(char **map_copy);
void			destroy_images(t_data *data);
int				validate_args(int argc);
int				initialize_game(t_data *data, char *map_file);
void			setup_hooks(t_data *data);
int				init_images(t_data *data);
int				init_window(t_data *data);
int				key_handler(int keycode, t_data *data);
int				key_handler_enemy(int keycode, t_data *data);
int				unified_key_handler(int keycode, t_data *data);
void			check_vertical_walls(t_data *data, int width, int height);
void			check_horizontal_walls(t_data *data, int width, int height);
void			check_map_walls(t_data *data);
void			validate_map(t_data *data);
void			count_map_elements(t_data *data, t_counts *counts);
void			validate_element_counts(t_data *data, t_counts *counts);
void			check_map_elements(t_data *data);
void			check_rectangular_shape(t_data *data);
void			check_valid_path(t_data *data);
int				move_player(t_data *data, t_pos prev, t_pos next);
int				move_enemy(t_data *data, t_pos prev, t_pos next);
void			update_player_position(t_data *data, t_pos prev, t_pos next);
void			update_enemy_position(t_data *data, t_pos prev, t_pos next);
char			**read_map(char *file);
int				main(int argc, char **argv);
void			flood_fill_player(char **map, int x, int y, t_data *data);
void			flood_fill_enemy(char **map, int x, int y, t_data *data);
int				enemy_can_reach_player(t_data *data);
char			**resize_map(char **map, int old_rows);
void			count_collectibles(t_data *data);
void			find_player_position(t_data *data, int *px, int *py);
void			find_enemy_position(t_data *data, int *px, int *py);
char			**copy_map(char **map);
void			put_tile(t_data *data, char c, int x, int y);
void			put_tile2(t_data *data, char c, int x, int y);
void			draw_map(t_data *data);
void			display_ui(t_data *data);
int				close_window(t_data *data);
void			t(int a);

#endif