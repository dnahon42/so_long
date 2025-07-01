/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dnahon <dnahon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/11 18:28:45 by dnahon            #+#    #+#             */
/*   Updated: 2025/06/30 12:49:15 by dnahon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/ft_printf.h"
#include "../../includes/get_next_line.h"
#include "../../includes/libft.h"
#include "../../includes/so_long.h"
#include "../../minilibx-linux/mlx.h"

char	**resize_map(char **map, int old_rows)
{
	int		i;
	char	**new_map;

	new_map = ft_malloc(sizeof(char *) * (old_rows + 100));
	if (!new_map)
		return (free_map(map), NULL);
	i = -1;
	while (++i < old_rows)
		new_map[i] = map[i];
	return (ft_free(map), new_map);
}

void	count_collectibles(t_data *data)
{
	int	x;
	int	y;

	if (!data->map)
	{
		write(2, "Error\nInvalid map structure\n", 28);
		exit(1);
	}
	data->total_collectibles = 0;
	y = 0;
	while (data->map[y])
	{
		x = 0;
		while (data->map[y][x])
		{
			if (data->map[y][x] == 'C')
				data->total_collectibles++;
			x++;
		}
		y++;
	}
}

void	find_player_position(t_data *data, int *px, int *py)
{
	int	x;
	int	y;

	y = 0;
	while (data->map[y])
	{
		x = 0;
		while (data->map[y][x])
		{
			if (data->map[y][x] == 'P')
			{
				*px = x;
				*py = y;
				return ;
			}
			x++;
		}
		y++;
	}
	exit(write(2, "Error\nNo player start position found\n", 38));
}

void	find_enemy_position(t_data *data, int *px, int *py)
{
	int	x;
	int	y;

	y = 0;
	while (data->map[y])
	{
		x = 0;
		while (data->map[y][x])
		{
			if (data->map[y][x] == 'T')
			{
				*px = x;
				*py = y;
				return ;
			}
			x++;
		}
		y++;
	}
	exit(write(2, "Error\nNo player start position found\n", 38));
}

char	**copy_map(char **map)
{
	int		y;
	char	**copy;

	y = 0;
	while (map[y])
		y++;
	copy = ft_malloc(sizeof(char *) * (y + 1));
	if (!copy)
		return (NULL);
	y = 0;
	while (map[y])
	{
		copy[y] = ft_strdup(map[y]);
		if (!copy[y])
		{
			while (--y >= 0)
				ft_free(copy[y]);
			ft_free(copy);
			return (NULL);
		}
		y++;
	}
	copy[y] = NULL;
	return (copy);
}
