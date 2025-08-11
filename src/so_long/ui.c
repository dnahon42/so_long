/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ui.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dnahon <dnahon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/11 18:25:04 by dnahon            #+#    #+#             */
/*   Updated: 2025/07/02 16:54:41 by dnahon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/ft_printf.h"
#include "../../includes/get_next_line.h"
#include "../../includes/libft.h"
#include "../../includes/so_long.h"
#include "../../minilibx-linux/mlx.h"

void	put_tile(t_data *data, char c, int x, int y)
{
	if (c == '1')
		mlx_put_image_to_window(data->mlx, data->win, data->wall, x
			* data->wall_width, y * data->wall_height);
	else if (c == '0')
		mlx_put_image_to_window(data->mlx, data->win, data->floor, x
			* data->floor_width, y * data->floor_height);
	else if (c == 'C')
	{
		mlx_put_image_to_window(data->mlx, data->win, data->collectible, x
			* data->collectible_width, y * data->collectible_height);
	}
	else if (c == 'E')
	{
		if (data->collected_items == data->total_collectibles)
			mlx_put_image_to_window(data->mlx, data->win, data->exit_opened, x
				* data->exit_width, y * data->exit_height);
		else
			mlx_put_image_to_window(data->mlx, data->win, data->exit, x
				* data->exit_width, y * data->exit_height);
	}
}

void	put_tile2(t_data *data, char c, int x, int y)
{
	if (c == 'P')
	{
		data->x = x * data->floor_width;
		data->y = y * data->floor_height;
	}
	else if (c == 'T')
	{
		data->enemy_x = x * data->floor_width;
		data->enemy_y = y * data->floor_height;
	}
}

void	draw_map(t_data *data)
{
	int	x;
	int	y;

	y = 0;
	while (data->map[y])
	{
		x = -1;
		while (data->map[y][++x])
		{
			put_tile(data, data->map[y][x], x, y);
			put_tile2(data, data->map[y][x], x, y);
		}
		y++;
	}
	mlx_put_image_to_window(data->mlx, data->win, data->current_player_img,
		data->x, data->y);
	if (data->counts.enemy_count == 1)
		mlx_put_image_to_window(data->mlx, data->win, data->current_enemy_img,
			data->enemy_x, data->enemy_y);
}

void	display_ui(t_data *data)
{
	char	*movements;

	mlx_put_image_to_window(data->mlx, data->win, data->current_player_img,
		data->x, data->y);
	mlx_string_put(data->mlx, data->win, 10, 10, 0xFFFFFF, "Movements: ");
	movements = ft_itoa(data->movements);
	mlx_string_put(data->mlx, data->win, 100, 10, 0xFFFFFF, movements);
	free(movements);
}

int	close_window(t_data *data)
{
	free_map(data->map);
	destroy_images(data);
	mlx_destroy_window(data->mlx, data->win);
	mlx_destroy_display(data->mlx);
	free(data->mlx);
	exit(0);
	return (0);
}
