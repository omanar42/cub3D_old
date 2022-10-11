/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rendering.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omanar <omanar@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/15 20:19:53 by omanar            #+#    #+#             */
/*   Updated: 2022/10/11 22:11:08 by omanar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3D.h>

void	cast_ray(t_cub *cub, float ray_angle, int ray)
{
	cub->rays[ray].angle = ray_angle;
	cub->rays[ray].distance = get_distance(cub, ray_angle);
	if (cub->rays[ray].distance == 0)
		cub->rays[ray].distance = 0.0001;
	cub->rays[ray].was_hit_vertical = is_his_vertical(ray_angle);
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
	while (++i < cub->data->window_width)
	{
		cast_ray(cub, ray_angle, i);
		ray_angle += FOV_ANGLE / cub->data->window_width;
	}
}

void	set_map(t_cub *cub)
{
	int		i;
	int		j;
	int		tilex;
	int		tiley;

	j = -1;
	while (cub->data->map[++j])
	{
		i = -1;
		while (cub->data->map[j][++i])
		{
			tilex = i * TILE_SIZE;
			tiley = j * TILE_SIZE;
			if (cub->data->map[j][i] == '1')
				my_pixel_put(cub->img, tilex, tiley, 0xDFCD8B);
			else if (cub->data->map[j][i] == ' ')
				my_pixel_put(cub->img, tilex, tiley, 0x000000);
			else
				my_pixel_put(cub->img, tilex, tiley, 0xB1B3B2);
		}
	}
}

void	set_player(t_cub *cub)
{
	my_mlx_pixel_put(cub->img, cub->player->x
		* 0.25, cub->player->y * 0.25, 0x00203FFF);
	render_line(cub, cub->player->x, cub->player->y,
		cub->player->x + cos(cub->player->angle) * 180,
		cub->player->y + sin(cub->player->angle) * 180, 0x00203FFF);
}

void	render_cub(t_cub *cub)
{
	mlx_clear_window(cub->mlxdata->mlx, cub->mlxdata->win);
	mlx_put_image_to_window(cub->mlxdata->mlx,
		cub->mlxdata->win, cub->cub->img, 0, 0);
	mlx_put_image_to_window(cub->mlxdata->mlx,
		cub->mlxdata->win, cub->img->img, 0, 0);
}
