/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omanar <omanar@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/15 19:11:31 by omanar            #+#    #+#             */
/*   Updated: 2022/08/15 21:34:06 by omanar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3D.h>

void	parsing(char *str)
{
	int		fd;
	char	*ext;

	ext = ft_strrchr(str, '.');
	if (ft_strncmp(ext, ".cub\0", 5))
		exit_error("invalid file extension", ext);
	fd = open(str, O_RDONLY);
	if (fd == -1)
		exit_strerr(str, errno);
	close(fd);
	printf("Everything looks good\n");
}

int	main(int ac, char **av)
{
	if (ac != 2)
	{
		printf("Usage: ./cub3D <filename.cub>\n");
		return (0);
	}
	parsing(av[1]);
	return (0);
}
