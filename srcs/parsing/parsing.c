/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omanar <omanar@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/06 18:33:21 by omanar            #+#    #+#             */
/*   Updated: 2022/10/11 23:37:28 by omanar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3D.h>

void	file_checker(char *str)
{
	char	*ext;

	ext = ft_strrchr(str, '.');
	if (!ext)
		exit_str("No extension found");
	else if (ft_strncmp(ext, ".cub\0", 5))
		exit_error("invalid file extension", ext);
}

void	if_something_missing(t_cub *cub)
{
	if (!cub->data->no || !cub->data->so || !cub->data->we || !cub->data->ea)
		exit_str("Missing texture");
	else if (cub->data->floor == -1 || cub->data->ceiling == -1)
		exit_str("Missing color");
	else if (!cub->data->map[0])
		exit_str("Missing map");
}

void	file_parsing(t_cub *cub, int fd)
{
	int		i;
	char	*line;

	i = 0;
	line = get_next_line(fd);
	while (line)
	{
		if (line[0] != '\n')
		{
			if (line_parsing(cub, line))
			{
				map_parsing(cub, line, fd);
				return ;
			}
		}
		free(line);
		line = get_next_line(fd);
		i++;
	}
}

void	add_player(t_cub *cub, char **map, int y, int x)
{
	if (cub->player->x != -1 || cub->player->y != -1)
		exit_str("Duplicate player");
	cub->player->x = (x * TILE_SIZE) + 0.5;
	cub->player->y = (y * TILE_SIZE) + 0.5;
	if (map[y][x] == 'N')
		cub->player->angle = 270 * (M_PI / 180);
	else if (map[y][x] == 'S')
		cub->player->angle = 90 * (M_PI / 180);
	else if (map[y][x] == 'W')
		cub->player->angle = 180 * (M_PI / 180);
	else if (map[y][x] == 'E')
		cub->player->angle = 0 * (M_PI / 180);
	cub->data->map[y][x] = '0';
}

void	check_border(t_cub *cub, char **map)
{
	int	y;
	int	x;

	y = -1;
	while (map[++y])
	{
		x = -1;
		while (map[y][++x])
		{
			if (x == 0 || x == (int)ft_strlen(map[y]) - 1
				|| y == 0 || y == cub->data->height - 1)
				if (map[y][x] != '1' && map[y][x] != ' ')
					exit_str("Invalid map");
			if (map[y][x] == '0')
				if (map[y][x + 1] == ' ' || map[y][x - 1] == ' '
					|| map[y + 1][x] == ' ' || map[y - 1][x] == ' ')
					exit_str("Invalid map");
			if (map[y][x] == 'N' || map[y][x] == 'S'
				|| map[y][x] == 'E' || map[y][x] == 'W')
				add_player(cub, map, y, x);
		}
	}
}

void	parsing(t_cub *cub, char *str)
{
	int		fd;

	file_checker(str);
	fd = open(str, O_RDONLY);
	if (fd == -1)
		exit_strerr(str, errno);
	initialize(cub);
	file_parsing(cub, fd);
	close(fd);
	if_something_missing(cub);
	check_border(cub, cub->data->map);
}
