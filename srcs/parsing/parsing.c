/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omanar <omanar@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/06 18:33:21 by omanar            #+#    #+#             */
/*   Updated: 2022/09/14 22:02:40 by omanar           ###   ########.fr       */
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

void	parsing(char *str)
{
	int		fd;

	file_checker(str);
	fd = open(str, O_RDONLY);
	if (fd == -1)
		exit_strerr(str, errno);
	close(fd);
	printf("Everything looks good\n");
}
