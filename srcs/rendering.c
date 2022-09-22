/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rendering.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omanar <omanar@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/15 20:19:53 by omanar            #+#    #+#             */
/*   Updated: 2022/09/22 16:27:01 by omanar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3D.h>

void	cast_ray(t_cub *cub, float ray_angle, int ray)
{
	(void)ray;
	render_line(cub, cub->player->x, cub->player->y,
		cub->player->x + cos(ray_angle) * 1500,
		cub->player->y + sin(ray_angle) * 1500, 0xF2EFDC);
}

void	set_all_rays(t_cub *cub)
{
	int		i;
	float	ray_angle;

	ray_angle = cub->player->angle - (FOV_ANGLE / 2);
	i = -1;
	while (++i < WINDOW_WIDTH)
	{
		cast_ray(cub, ray_angle, i);
		ray_angle += FOV_ANGLE / WINDOW_WIDTH;
	}
}

void	set_map(t_cub *cub)
{
	int		i;
	int		j;
	int		tilex;
	int		tiley;

	j = -1;
	while (++j < MAP_NUM_ROWS)
	{
		i = -1;
		while (++i < MAP_NUM_COLS)
		{
			tilex = i * TILE_SIZE;
			tiley = j * TILE_SIZE;
			if (map[j][i] == 1)
				my_pixel_put(cub->img, tilex, tiley, 0xDFCD8B);
			else
				my_pixel_put(cub->img, tilex, tiley, 0xB1B3B2);
		}
	}
}

void	set_player(t_cub *cub)
{
	my_mlx_pixel_put(cub->img, cub->player->x, cub->player->y, 0x00203FFF);
	// render_line(cub, cub->player->x, cub->player->y,
	// 	cub->player->x + cos(cub->player->angle) * 40,
	// 	cub->player->y + sin(cub->player->angle) * 40, 0x00203FFF);
}

void	render_cub(t_cub *cub)
{
	mlx_put_image_to_window(cub->data->mlx,
		cub->data->win, cub->img->img, 0, 0);
}
