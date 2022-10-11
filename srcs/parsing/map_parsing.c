/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_parsing.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omanar <omanar@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/11 16:37:07 by omanar            #+#    #+#             */
/*   Updated: 2022/10/11 22:34:50 by omanar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3D.h>

void	map_parsing(t_cub *cub, char *line, int fd)
{
	char	*tmp;

	while (line)
	{
		if (!is_map(line))
			exit_error("Invalid map", line);
		cub->data->height++;
		tmp = ft_strtrim(line, "\n");
		if (cub->data->width < (int)ft_strlen(tmp))
			cub->data->width = ft_strlen(tmp);
		cub->data->map = advanced_add(cub->data->map, tmp);
		free(line);
		free(tmp);
		line = get_next_line(fd);
	}
	free(line);
}
