/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dnahon <dnahon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/11 18:16:06 by dnahon            #+#    #+#             */
/*   Updated: 2025/06/20 14:23:10 by dnahon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/ft_printf.h"
#include "../../includes/get_next_line.h"
#include "../../includes/libft.h"
#include "../../includes/so_long.h"
#include "../../minilibx-linux/mlx.h"

char	**read_map(char *file)
{
	int		fd;
	char	**map;
	char	*line;
	int		rows;

	fd = open(file, O_RDONLY);
	if (fd < 0)
		return (write(2, "Error\nImpossible d'ouvrir la map\n", 33), NULL);
	map = ft_malloc(sizeof(char *) * 100);
	if (!map)
		return (write(2, "Error\nMemory allocation failed\n", 31), close(fd),
			NULL);
	rows = 0;
	line = get_next_line(fd);
	if (!line)
		return (close(fd), write(2, "Error\nImpossible de lire la map\n", 33),
			NULL);
	while (line)
	{
		map[rows++] = trim_newline(line);
		if (rows % 100 == 0)
			map = resize_map(map, rows);
		line = get_next_line(fd);
	}
	return (map[rows] = NULL, close(fd), map);
}

char	*trim_newline(char *line)
{
	int	len;

	len = ft_strlen(line);
	if (line[len - 1] == '\n')
		line[len - 1] = '\0';
	return (line);
}

int	main(int argc, char **argv)
{
	t_data	data;

	if (!validate_args(argc))
		return (-1);
	if (!initialize_game(&data, argv[1]))
		return (-1);
	setup_hooks(&data);
	mlx_loop(data.mlx);
	return (0);
}
