/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dnahon <dnahon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/11 18:16:06 by dnahon            #+#    #+#             */
/*   Updated: 2025/07/05 18:13:28 by dnahon           ###   ########.fr       */
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
		return (write(2, "Error\nFailed to open map\n", 26), NULL);
	map = ft_malloc(sizeof(char *) * 100);
	if (!map)
		return (write(2, "Error\nMemory allocation failed\n", 31), close(fd),
			NULL);
	rows = 0;
	line = get_next_line(fd);
	if (!line)
		return (ft_free(map), close(fd), write(2, "Error\nFailed to read map\n",
				33), NULL);
	while (line)
	{
		t((map[rows++] = ft_strtrim(line, "\n"), free(line), 0));
		if (rows % 100 == 0)
			map = resize_map(map, rows);
		line = get_next_line(fd);
	}
	return (map[rows] = NULL, close(fd), map);
}

int	main(int argc, char **argv)
{
	t_data	data;
	char	*ext;

	if (!validate_args(argc))
		return (-1);
	if (argc == 2)
	{
		ext = ft_strrchr(argv[1], '.');
		if (!ext || ft_strncmp(ext, ".ber", 4) != 0)
		{
			return (write(2, "Error\nInvalid file format. Use a .ber file\n",
					44), 0);
		}
		if (ft_strlen(argv[1]) < 5)
			return (write(2, "Error\nFile name too short\n", 28), 0);
		if (ft_strncmp(argv[1], "./", 2) == 0)
			return (write(2, "Error\nRelative paths are not allowed\n", 38), 0);
	}
	if (!initialize_game(&data, argv[1]))
		return (-1);
	setup_hooks(&data);
	mlx_loop(data.mlx);
	return (0);
}
