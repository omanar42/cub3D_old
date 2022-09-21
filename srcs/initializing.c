/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initializing.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omanar <omanar@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/15 20:23:10 by omanar            #+#    #+#             */
/*   Updated: 2022/09/21 17:35:22 by omanar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3D.h>

void	initialize(t_cub *cub)
{
	cub->data = malloc(sizeof(t_data));
	cub->player = malloc(sizeof(t_player));
	cub->rays = malloc(sizeof(t_ray) * WINDOW_WIDTH);
	cub->map = malloc(sizeof(t_img));
	if (!cub->data || !cub->player || !cub->rays || !cub->map)
		exit_strerr("malloc", errno);
	cub->data->mlx = mlx_init();
	if (!cub->data->mlx)
		exit_error("mlx_init", "Error initializing MLX");
	cub->data->win = mlx_new_window(cub->data->mlx,
			WINDOW_WIDTH, WINDOW_HEIGHT, "cub3D");
	if (!cub->data->win)
		exit_error("mlx_new_window", "Error creating MLX window");
}

void	set_map(t_cub *cub)
{
	int		i;
	int		j;
	int		tilex;
	int		tiley;

	cub->map->img = mlx_new_image(cub->data->mlx, WINDOW_WIDTH, WINDOW_HEIGHT);
	cub->map->addr = mlx_get_data_addr(cub->map->img, &cub->map->bits_per_pixel,
			&cub->map->line_length, &cub->map->endian);
	j = -1;
	while (++j < MAP_NUM_ROWS)
	{
		i = -1;
		while (++i < MAP_NUM_COLS)
		{
			tilex = i * TILE_SIZE;
			tiley = j * TILE_SIZE;
			if (map[j][i] == 1)
				my_pixel_put(cub->map, tilex, tiley, 0xDFCD8B);
			else
				my_pixel_put(cub->map, tilex, tiley, 0xB1B3B2);
		}
	}
}

void	setup(t_cub *cub)
{
	cub->player->x = WINDOW_WIDTH / 2;
	cub->player->y = WINDOW_HEIGHT / 2;
	cub->player->angle = PI / 2;
	cub->player->turndir = 0;
	cub->player->walkdir = 0;
	cub->player->turnspeed = 5 * (PI / 180);
	cub->player->walkspeed = 10;
	mlx_hook(cub->data->win, 2, 0, key_hook, cub);
	mlx_hook(cub->data->win, 3, 0, set_defeult, cub);
	mlx_hook(cub->data->win, 17, 0, distroy_event, cub);
	// mlx_loop_hook(cub->data->mlx, loop_hook, cub);
	set_map(cub);
	render_map(cub);
	render_rays(cub);
	render_player(cub);
}
