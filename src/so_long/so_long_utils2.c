/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long_utils2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dnahon <dnahon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/11 18:28:45 by dnahon            #+#    #+#             */
/*   Updated: 2025/07/01 14:29:42 by dnahon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/ft_printf.h"
#include "../../includes/get_next_line.h"
#include "../../includes/libft.h"
#include "../../includes/so_long.h"
#include "../../minilibx-linux/mlx.h"
void	flood_fill_player(char **map, int x, int y, t_data *data)
{
	if (!map || y < 0 || x < 0 || !map[y] || map[y][x] == '\0')
		return ;
	if (map[y][x] == '1' || map[y][x] == 'V' || map[y][x] == 'T')
		return ;
	if (map[y][x] == 'E')
	{
		data->exit_found = 1;
		return ;
	}
	if (map[y][x] == 'C')
		data->collectibles_found++;
	map[y][x] = 'V';
	flood_fill_player(map, x + 1, y, data);
	flood_fill_player(map, x - 1, y, data);
	flood_fill_player(map, x, y + 1, data);
	flood_fill_player(map, x, y - 1, data);
}

void	flood_fill_enemy(char **map, int x, int y, t_data *data)
{
	if (!map || y < 0 || x < 0 || !map[y] || map[y][x] == '\0')
		return ;
	if (map[y][x] == '1' || map[y][x] == 'V' || map[y][x] == 'E')
		return ;
	if (map[y][x] == 'P')
		data->player_found = 1;
	map[y][x] = 'V';
	flood_fill_enemy(map, x + 1, y, data);
	flood_fill_enemy(map, x - 1, y, data);
	flood_fill_enemy(map, x, y + 1, data);
	flood_fill_enemy(map, x, y - 1, data);
}

int	enemy_can_reach_player(t_data *data)
{
	int		enemy_x;
	int		enemy_y;
	char	**g_map_copy;

	find_enemy_position(data, &enemy_x, &enemy_y);
	data->player_found = 0;
	g_map_copy = copy_map(data->map);
	if (!g_map_copy)
		return (0);
	flood_fill_enemy(g_map_copy, enemy_x, enemy_y, data);
	free_map_copy(g_map_copy);
	return (data->player_found);
}

void	t(int a)
{
	(void)a;
}
