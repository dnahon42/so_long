/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_validity.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dnahon <dnahon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/11 18:16:42 by dnahon            #+#    #+#             */
/*   Updated: 2025/06/25 14:15:03 by dnahon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/ft_printf.h"
#include "../../includes/get_next_line.h"
#include "../../includes/libft.h"
#include "../../includes/so_long.h"
#include "../../minilibx-linux/mlx.h"

void	count_map_elements(t_data *data, t_counts *counts)
{
	int	x;
	int	y;

	free((counts->exit_count = 0, counts->player_count = 0,
			counts->item_count = 0, counts->enemy_count = 0, y = -1, NULL));
	counts->wrong = 0;
	while (data->map[++y])
	{
		x = -1;
		while (data->map[y][++x])
		{
			if (data->map[y][x] == 'E')
				counts->exit_count++;
			else if (data->map[y][x] == 'P')
				counts->player_count++;
			else if (data->map[y][x] == 'C')
				counts->item_count++;
			else if (data->map[y][x] == 'T')
				counts->enemy_count++;
			else if (data->map[y][x] != 'E' && data->map[y][x] != 'P'
				&& data->map[y][x] != 'C' && data->map[y][x] != 'T'
				&& data->map[y][x] != '0' && data->map[y][x] != '1')
				counts->wrong = 1;
		}
	}
}

void	validate_element_counts(t_data *data, t_counts *counts)
{
	if (counts->exit_count != 1 || counts->player_count != 1
		|| counts->item_count < 1 || counts->enemy_count > 1
		|| counts->wrong == 1)
	{
		free_map(data->map);
		exit(write(2, "Error\nInvalid map elements\n", 28));
	}
}

void	check_map_elements(t_data *data)
{
	t_counts	counts;

	count_map_elements(data, &counts);
	validate_element_counts(data, &counts);
}

void	check_rectangular_shape(t_data *data)
{
	int	y;
	int	len;
	int	first_row_len;

	free((y = 0, first_row_len = ft_strlen(data->map[0]), NULL));
	if (data->map[0][first_row_len - 1] == '\n')
		first_row_len--;
	while (data->map[y])
	{
		len = ft_strlen(data->map[y]);
		if (data->map[y][len - 1] == '\n')
			len--;
		if (len != first_row_len)
			free((free_map(data->map), write(2,
						"Error\nMap is not rectangular\n", 30), exit(1), NULL));
		y++;
	}
}

void	check_valid_path(t_data *data)
{
	char	**map_copy;
	int		px;
	int		py;

	map_copy = copy_map(data->map);
	if (!map_copy)
	{
		free_map(data->map);
		exit(write(2, "Error\nMemory allocation failed\n", 31));
	}
	find_player_position(data, &px, &py);
	data->exit_found = 0;
	data->collectibles_found = 0;
	flood_fill_player(map_copy, px, py, data);
	if (!data->exit_found
		|| data->collectibles_found < data->total_collectibles)
	{
		free_map_copy(map_copy);
		free_map(data->map);
		exit(write(2, "Error\nUnreachable element detected\n", 36));
	}
	free_map_copy(map_copy);
}
