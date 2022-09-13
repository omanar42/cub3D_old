/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omanar <omanar@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/15 19:11:31 by omanar            #+#    #+#             */
/*   Updated: 2022/09/11 18:59:03 by omanar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3D.h>

void	distroy_cub(t_cub *cub)
{
	if (cub->data)
	{
		mlx_destroy_window(cub->data->mlx, cub->data->win);
		free(cub->data);
	}
	free(cub);
}

int	distroy_event(int keycode, t_cub *cub)
{
	(void)cub;
	(void)keycode;
	exit(0);
	return (0);
}

int	key_hook(int keycode, t_cub *cub)
{
	(void)cub;
	if (keycode == 53)
		exit(0);
	return (0);
}

void	initialize(t_cub *cub)
{
	cub->data = malloc(sizeof(t_data));
	if (!cub->data)
		exit_strerr("malloc", errno);
	cub->data->mlx = mlx_init();
	if (!cub->data->mlx)
		exit_error("mlx_init", "Error initializing MLX");
	cub->data->win = mlx_new_window(cub->data->mlx,
			WINDOW_WIDTH, WINDOW_HEIGHT, "cub3D");
	if (!cub->data->win)
		exit_error("mlx_new_window", "Error creating MLX window");
}

int	main(int ac, char **av)
{
	t_cub	*cub;

	if (ac != 2)
		exit_success("Usage: ./cub3D <map.cub>");
	cub = (t_cub *)malloc(sizeof(t_cub));
	parsing(av[1]);
	initialize(cub);
	mlx_hook(cub->data->win, 2, 0, key_hook, &cub);
	mlx_hook(cub->data->win, 17, 0, distroy_event, &cub);
	mlx_loop(cub->data->mlx);
	distroy_cub(cub);
	return (0);
}
