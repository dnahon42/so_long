/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dnahon <dnahon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/11 18:15:46 by dnahon            #+#    #+#             */
/*   Updated: 2025/07/04 20:36:45 by dnahon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/ft_printf.h"
#include "../../includes/get_next_line.h"
#include "../../includes/libft.h"
#include "../../includes/so_long.h"
#include "../../minilibx-linux/mlx.h"

void	free_map(char **map)
{
	int	y;

	y = 0;
	while (map[y])
	{
		ft_free(map[y]);
		y++;
	}
	ft_free(map);
}

void	free_map_copy(char **map_copy)
{
	int	y;

	y = 0;
	if (!map_copy)
		return ;
	while (map_copy[y])
	{
		ft_free(map_copy[y]);
		y++;
	}
	ft_free(map_copy);
}

void	destroy_images(t_data *data)
{
	if (data->floor)
		mlx_destroy_image(data->mlx, data->floor);
	if (data->player)
		mlx_destroy_image(data->mlx, data->player);
	if (data->player_left)
		mlx_destroy_image(data->mlx, data->player_left);
	if (data->enemy)
		mlx_destroy_image(data->mlx, data->enemy);
	if (data->enemy_left)
		mlx_destroy_image(data->mlx, data->enemy_left);
	if (data->wall)
		mlx_destroy_image(data->mlx, data->wall);
	if (data->collectible)
		mlx_destroy_image(data->mlx, data->collectible);
	if (data->exit)
		mlx_destroy_image(data->mlx, data->exit);
	if (data->exit_opened)
		mlx_destroy_image(data->mlx, data->exit_opened);
}
