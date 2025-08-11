/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_handler.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dnahon <dnahon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/20 15:23:45 by dnahon            #+#    #+#             */
/*   Updated: 2025/07/02 16:54:31 by dnahon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/ft_printf.h"
#include "../../includes/get_next_line.h"
#include "../../includes/libft.h"
#include "../../includes/so_long.h"
#include "../../minilibx-linux/mlx.h"

int	key_handler(int keycode, t_data *data)
{
	t_pos	prev;
	t_pos	next;

	prev.x = data->x / data->floor_width;
	prev.y = data->y / data->floor_height;
	next = prev;
	if (keycode == 65307)
		close_window(data);
	else if (keycode == 97)
		t((data->current_player_img = data->player_left, next.x -= 1, 0));
	else if (keycode == 100)
		t((data->current_player_img = data->player, next.x += 1, 0));
	else if (keycode == 115)
		next.y += 1;
	else if (keycode == 119)
		next.y -= 1;
	else
		return (0);
	return (move_player(data, prev, next));
}

int	key_handler_enemy(int keycode, t_data *data)
{
	t_pos	prev;
	t_pos	next;

	if (data->counts.enemy_count != 1)
		return (0);
	prev.enemy_x = data->enemy_x / data->floor_width;
	prev.enemy_y = data->enemy_y / data->floor_height;
	next = prev;
	if (keycode == 65307)
		close_window(data);
	else if (keycode == 65361)
		t((data->current_enemy_img = data->enemy_left, next.enemy_x -= 1, 0));
	else if (keycode == 65363)
		t((data->current_enemy_img = data->enemy, next.enemy_x += 1, 0));
	else if (keycode == 65364)
		next.enemy_y += 1;
	else if (keycode == 65362)
		next.enemy_y -= 1;
	else
		return (0);
	return (move_enemy(data, prev, next));
}

int	unified_key_handler(int keycode, t_data *data)
{
	if (keycode == 97 || keycode == 100 || keycode == 115 || keycode == 119
		|| keycode == 65307)
		return (key_handler(keycode, data));
	else if (keycode == 65361 || keycode == 65362 || keycode == 65363
		|| keycode == 65364)
		return (key_handler_enemy(keycode, data));
	else if (keycode == 65307)
		close_window(data);
	return (0);
}
