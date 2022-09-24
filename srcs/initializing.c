/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initializing.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omanar <omanar@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/15 20:23:10 by omanar            #+#    #+#             */
/*   Updated: 2022/09/24 21:34:10 by omanar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3D.h>

void	initialize(t_cub *cub)
{
	cub->img = malloc(sizeof(t_img));
	cub->cub = malloc(sizeof(t_img));
	cub->data = malloc(sizeof(t_data));
	cub->player = malloc(sizeof(t_player));
	cub->rays = malloc(sizeof(t_ray) * WINDOW_WIDTH);
	if (!cub->img || !cub->cub || !cub->data || !cub->player || !cub->rays)
		exit_strerr("malloc", errno);
	cub->data->mlx = mlx_init();
	if (!cub->data->mlx)
		exit_error("mlx_init", "Error initializing MLX");
	cub->data->win = mlx_new_window(cub->data->mlx,
			WINDOW_WIDTH, WINDOW_HEIGHT, "cub3D");
	if (!cub->data->win)
		exit_error("mlx_new_window", "Error creating MLX window");
}

void	player_config(t_cub *cub)
{
	cub->player->x = (WINDOW_WIDTH / 2);
	cub->player->y = (WINDOW_HEIGHT / 2);
	cub->player->angle = PI / 2;
	cub->player->turndir = 0;
	cub->player->walkdir = 0;
	cub->player->turnspeed = 5 * (PI / 180);
	cub->player->walkspeed = 10;
}
