/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_validity2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dnahon <dnahon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 14:08:09 by dnahon            #+#    #+#             */
/*   Updated: 2025/06/30 13:32:34 by dnahon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/ft_printf.h"
#include "../../includes/get_next_line.h"
#include "../../includes/libft.h"
#include "../../includes/so_long.h"
#include "../../minilibx-linux/mlx.h"

void	check_vertical_walls(t_data *data, int width, int height)
{
	int	y;

	y = -1;
	while (++y < height)
	{
		if (data->map[y][0] != '1' || data->map[y][width - 1] != '1')
		{
			free_map(data->map);
			exit(write(2, "Error\nMap not enclosed by walls\n", 33));
		}
	}
}

void	check_horizontal_walls(t_data *data, int width, int height)
{
	int	x;

	x = -1;
	while (++x < width)
	{
		if (data->map[0][x] != '1' || data->map[height - 1][x] != '1')
		{
			free_map(data->map);
			exit(write(2, "Error\nMap not enclosed by walls\n", 33));
		}
	}
}

void	check_map_walls(t_data *data)
{
	int	width;
	int	height;

	height = 0;
	while (data->map[height])
		height++;
	width = ft_strlen(data->map[0]);
	check_vertical_walls(data, width, height);
	check_horizontal_walls(data, width, height);
}
void	check_map_size(t_data *data)
{
	int	i;

	i = 0;
	data->win_width = ft_strlen(data->map[0]) * 50;
	while (data->map[i])
		i++;
	data->win_height = i * 50;
	if (data->win_width > 1900 || data->win_height > 1000)
	{
		free_map(data->map);
		exit(write(2, "Error\nMap size too big\n", 24));
	}
}

void	validate_map(t_data *data)
{
	t_counts	counts;

	check_map_size(data);
	check_map_elements(data);
	check_rectangular_shape(data);
	check_map_walls(data);
	check_valid_path(data);
	count_map_elements(data, &counts);
	if (counts.enemy_count == 1)
	{
		if (!enemy_can_reach_player(data))
		{
			free_map(data->map);
			write(2, "Error\nEnemy cannot reach player\n", 32);
			exit(1);
		}
	}
}
