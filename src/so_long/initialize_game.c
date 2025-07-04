/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialize_game.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dnahon <dnahon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/11 18:26:53 by dnahon            #+#    #+#             */
/*   Updated: 2025/06/30 14:31:08 by dnahon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/ft_printf.h"
#include "../../includes/get_next_line.h"
#include "../../includes/libft.h"
#include "../../includes/so_long.h"
#include "../../minilibx-linux/mlx.h"

int	validate_args(int argc)
{
	if (argc != 2)
	{
		write(2, "Error: Please provide a .ber file\n", 34);
		return (0);
	}
	return (1);
}

int	initialize_game(t_data *data, char *map_file)
{
	data->map = read_map(map_file);
	if (!data->map)
		return (0);
	count_collectibles(data);
	validate_map(data);
	count_map_elements(data, &data->counts);
	data->mlx = mlx_init();
	if (!data->mlx)
		return (write(2, "Error\nFailed to initialize MLX\n", 32), 0);
	if (!init_window(data) || !init_images(data))
		return (0);
	data->current_player_img = data->player;
	data->current_enemy_img = data->enemy;
	free((data->movements = 0, data->collected_items = 0,
			data->enemy_on_collectible = 0, NULL));
	draw_map(data);
	return (1);
}

void	setup_hooks(t_data *data)
{
	mlx_hook(data->win, 17, 0, (void *)close_window, data);
	mlx_hook(data->win, 2, 1L << 0, unified_key_handler, data);
}
int	init_images(t_data *data)
{
	data->player = mlx_xpm_file_to_image(data->mlx, "assets/Player.xpm",
			&data->player_width, &data->player_height);
	data->player_left = mlx_xpm_file_to_image(data->mlx, "assets/Player2.xpm",
			&data->player_width, &data->player_height);
	data->enemy = mlx_xpm_file_to_image(data->mlx, "assets/Enemy.xpm",
			&data->enemy_width, &data->enemy_height);
	data->enemy_left = mlx_xpm_file_to_image(data->mlx, "assets/Enemy2.xpm",
			&data->enemy_width, &data->enemy_height);
	data->floor = mlx_xpm_file_to_image(data->mlx, "assets/Floor.xpm",
			&data->floor_width, &data->floor_height);
	data->wall = mlx_xpm_file_to_image(data->mlx, "assets/Wall.xpm",
			&data->wall_width, &data->wall_height);
	data->collectible = mlx_xpm_file_to_image(data->mlx,
			"assets/Collectible.xpm", &data->collectible_width,
			&data->collectible_height);
	data->exit = mlx_xpm_file_to_image(data->mlx, "assets/Closed-Exit.xpm",
			&data->exit_width, &data->exit_height);
	data->exit_opened = mlx_xpm_file_to_image(data->mlx,
			"assets/Opened-Exit.xpm", &data->exit_width, &data->exit_height);
	if (!data->player || !data->player_left || !data->enemy || !data->enemy_left
		|| !data->floor || !data->wall || !data->collectible || !data->exit
		|| !data->exit_opened)
		return (write(2, "Error\nFailed to load images\n", 29),
			close_window(data), 0);
	return (1);
}

int	init_window(t_data *data)
{
	data->win = mlx_new_window(data->mlx, data->win_width, data->win_height,
			"So Long");
	if (!data->win)
	{
		write(2, "Error\nFailed to create window\n", 31);
		mlx_destroy_display(data->mlx);
		ft_free(data->mlx);
		return (0);
	}
	return (1);
}
