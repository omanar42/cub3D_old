/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omanar <omanar@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/15 19:11:31 by omanar            #+#    #+#             */
/*   Updated: 2022/10/11 21:43:58 by omanar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3D.h>

void	init_window(t_cub *cub)
{
	cub->data->window_width = cub->data->width * TILE_SIZE;
	cub->data->window_height = cub->data->height * TILE_SIZE;
	cub->mlxdata->mlx = mlx_init();
	if (!cub->mlxdata->mlx)
		exit_error("mlx_init", "Error initializing MLX");
	cub->mlxdata->win = mlx_new_window(cub->mlxdata->mlx,
			cub->data->window_width, cub->data->window_height, "cub3D");
	if (!cub->mlxdata->win)
		exit_error("mlx_new_window", "Error creating MLX window");
	cub->rays = malloc(sizeof(t_ray) * cub->data->window_width + 1);
	if (!cub->rays)
		exit_strerr("malloc", errno);
}

int	main(int ac, char **av)
{
	t_cub	*cub;

	if (ac != 2)
		exit_success("Usage: ./cub3D <map.cub>");
	cub = (t_cub *)malloc(sizeof(t_cub));
	parsing(cub, av[1]);
	init_window(cub);
	setup(cub);
	mlx_loop(cub->mlxdata->mlx);
	return (0);
}
