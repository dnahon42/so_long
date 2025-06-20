/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_validity2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dnahon <dnahon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 14:08:09 by dnahon            #+#    #+#             */
/*   Updated: 2025/06/20 19:03:05 by dnahon           ###   ########.fr       */
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

void	validate_map(t_data *data)
{
	check_map_elements(data);
	check_rectangular_shape(data);
	check_map_walls(data);
	check_valid_path(data);
	if (!enemy_can_reach_player(data))
	{
		free_map(data->map);
		write(2, "Error\nEnemy cannot reach player\n", 32);
		exit(1);
	}
}
