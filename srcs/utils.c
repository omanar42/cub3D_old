/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omanar <omanar@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/15 20:25:28 by omanar            #+#    #+#             */
/*   Updated: 2022/10/23 01:40:25 by omanar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3D.h>

int	get_direction(t_cub *cub, float x, float y, int ray)
{
	// printf("x = %d, y = %d\n", (int)(x + 1), (int)(y + 1));
	static int i = 0;

		if (!cub->rays[ray].was_hit_vertical)
		{
			if (cub->data->map[(int)((y - 1) / 64)][(int)(x / 64)] == '0')
				return (DIR_SO);
			if (cub->data->map[(int)((y + 1) / 64)][(int)(x / 64)] == '0')
				return (DIR_NO);
			i = 0;
		}
		else 
		{
			if (cub->data->map[(int)(y / 64)][(int)((x - 1) / 64)] == '0')
				return (DIR_EA);
			if (cub->data->map[(int)(y / 64)][(int)((x + 1) / 64)] == '0')
				return (DIR_WE);
			i++;
		}
	return (DIR_WE);
}

void	get_info(t_cub *cub, float ray_angle, int ray)
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
	while (pixels)
	{
		if (cub->data->map[(int)(pixely / TILE_SIZE)][(int)((pixelx + deltax) / TILE_SIZE)] != '0') {
			cub->rays[ray].was_hit_vertical = 1;
			break ;
		}
		else if (cub->data->map[(int)((pixely + deltay) / TILE_SIZE)][(int)(pixelx / TILE_SIZE)] != '0') {
			cub->rays[ray].was_hit_vertical = 0;
			break ;
		}
		pixelx += deltax;
		pixely += deltay;
		--pixels;
	}
	cub->rays[ray].distance = sqrt(pow(pixelx - cub->player->x, 2)
			+ pow(pixely - cub->player->y, 2));
	cub->rays[ray].direction = get_direction(cub, pixelx, pixely, ray);
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
			if ((x + i) * 0.17 < img->width && (y + j) * 0.17 < img->height)
				my_mlx_pixel_put(img, (x + i) * 0.17, (y + j) * 0.17, color);
			j++;
		}
		i++;
	}
}
