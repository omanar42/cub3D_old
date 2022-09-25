/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omanar <omanar@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/15 20:25:28 by omanar            #+#    #+#             */
/*   Updated: 2022/09/25 05:04:12 by omanar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3D.h>

int	is_his_vertical(float ray_angle)
{
	(void)ray_angle;
	return (1);
}

int	is_onempty(t_cub *cub, float x, float y)
{
	int	map_grid_index_x;
	int	map_grid_index_y;

	(void)cub;
	if (x < 0 || x > (MAP_NUM_COLS * TILE_SIZE)
		|| y < 0 || y > (MAP_NUM_ROWS * TILE_SIZE))
		return (FALSE);
	map_grid_index_x = floor(x / TILE_SIZE);
	map_grid_index_y = floor(y / TILE_SIZE);
	return (map[map_grid_index_y][map_grid_index_x] == 0);
}

float	get_distance(t_cub *cub, float ray_angle)
{
	int		pixels;
	double	pixelx;
	double	pixely;
	double	deltax;
	double	deltay;

	deltax = cub->player->x + cos(ray_angle) * 1500 - cub->player->x;
	deltay = cub->player->y + sin(ray_angle) * 1500 - cub->player->y;
	pixels = sqrt((deltax * deltax) + (deltay * deltay));
	deltax /= pixels;
	deltay /= pixels;
	pixelx = cub->player->x;
	pixely = cub->player->y;
	while (pixels && is_onempty(cub, pixelx, pixely))
	{
		pixelx += deltax;
		pixely += deltay;
		--pixels;
	}
	return (sqrt(pow(pixelx - cub->player->x, 2)
			+ pow(pixely - cub->player->y, 2)));
}

void	my_mlx_pixel_put(t_img *img, int x, int y, int color)
{
	char	*dst;

	dst = img->addr + (y * img->line_length + x * (img->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}

void	my_pixel_put(t_img *img, int x, int y, int color)
{
	int	i;
	int	j;

	i = 0;
	while (i < TILE_SIZE)
	{
		j = 0;
		while (j < TILE_SIZE)
		{
			my_mlx_pixel_put(img, (x + i) * 0.25, (y + j) * 0.25, color);
			j++;
		}
		i++;
	}
}
