/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dnahon <dnahon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/11 18:27:52 by dnahon            #+#    #+#             */
/*   Updated: 2025/06/30 19:12:41 by dnahon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/ft_printf.h"
#include "../../includes/get_next_line.h"
#include "../../includes/libft.h"
#include "../../includes/so_long.h"
#include "../../minilibx-linux/mlx.h"

int	move_player(t_data *data, t_pos prev, t_pos next)
{
	if (data->map[next.y][next.x] == '1' || next.y < 0 || next.x < 0)
		return (0);
	if (data->map[next.y][next.x] == 'C')
	{
		data->collected_items++;
		data->map[next.y][next.x] = '0';
	}
	if (data->map[next.y][next.x] == 'E')
	{
		if (data->collected_items == data->total_collectibles)
		{
			ft_printf("You won with %d movements! 🎉\n", data->movements);
			close_window(data);
		}
		else
		{
			ft_printf("You need to collect all items first!\n");
			return (0);
		}
	}
	if (data->map[next.y][next.x] == 'T')
		return (ft_printf("Error\nGame Over! The enemy caught you!\n"),
			close_window(data));
	update_player_position(data, prev, next);
	return (0);
}

int	move_enemy(t_data *data, t_pos prev, t_pos next)
{
	if (data->map[next.enemy_y][next.enemy_x] == '1' || next.enemy_y < 0
		|| next.enemy_x < 0)
		return (0);
	update_enemy_position(data, prev, next);
	return (0);
}

void	update_player_position(t_data *data, t_pos prev, t_pos next)
{
	data->map[prev.y][prev.x] = '0';
	data->map[next.y][next.x] = 'P';
	data->x = next.x * data->floor_width;
	data->y = next.y * data->floor_height;
	data->movements++;
	mlx_clear_window(data->mlx, data->win);
	draw_map(data);
	display_ui(data);
}

void	update_enemy_position(t_data *data, t_pos prev, t_pos next)
{
	if (data->enemy_on_collectible)
		data->map[prev.enemy_y][prev.enemy_x] = 'C';
	else
		data->map[prev.enemy_y][prev.enemy_x] = '0';
	if (data->map[next.enemy_y][next.enemy_x] == 'P')
	{
		ft_printf("Error\nGame Over! The enemy caught you!\n");
		close_window(data);
		return ;
	}
	if (data->map[next.enemy_y][next.enemy_x] == 'C')
		data->enemy_on_collectible = 1;
	else
		data->enemy_on_collectible = 0;
	if (data->map[next.enemy_y][next.enemy_x] == 'E')
		return ;
	data->map[next.enemy_y][next.enemy_x] = 'T';
	data->enemy_x = next.enemy_x * data->floor_width;
	data->enemy_y = next.enemy_y * data->floor_height;
	mlx_clear_window(data->mlx, data->win);
	draw_map(data);
	display_ui(data);
}
