/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rendering.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omanar <omanar@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/15 20:19:53 by omanar            #+#    #+#             */
/*   Updated: 2022/09/16 01:30:35 by omanar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3D.h>

void	render_line(t_cub *cub, int beginx, int beginy,
					int endx, int endy, int color)
{
	int		pixels;
	double	pixelx;
	double	pixely;
	double	deltax;
	double	deltay;

	deltax = endx - beginx;
	deltay = endy - beginy;
	pixels = sqrt((deltax * deltax) + (deltay * deltay));
	deltax /= pixels;
	deltay /= pixels;
	pixelx = beginx;
	pixely = beginy;
	while (pixels)
	{
		mlx_pixel_put(cub->data->mlx, cub->data->win, pixelx, pixely, color);
		pixelx += deltax;
		pixely += deltay;
		--pixels;
	}
}

void	render_map(t_cub *cub)
{
	int		i;
	int		j;
	int		tilex;
	int		tiley;
	t_img	img;

	img.img = mlx_new_image(cub->data->mlx, WINDOW_WIDTH, WINDOW_HEIGHT);
	img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel,
			&img.line_length, &img.endian);
	j = -1;
	while (++j < MAP_NUM_ROWS)
	{
		i = -1;
		while (++i < MAP_NUM_COLS)
		{
			tilex = i * TILE_SIZE;
			tiley = j * TILE_SIZE;
			if (map[j][i] == 1)
				my_pixel_put(&img, tilex, tiley, 0xDFCD8B);
			else
				my_pixel_put(&img, tilex, tiley, 0xB1B3B2);
		}
	}
	mlx_put_image_to_window(cub->data->mlx, cub->data->win, img.img, 0, 0);
}

void	render_player(t_cub *cub)
{
	int		i;
	int		j;
	t_img	img;

	img.img = mlx_new_image(cub->data->mlx, 1, 1);
	img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel,
			&img.line_length, &img.endian);
	i = 0;
	while (i < 1)
	{
		j = 0;
		while (j < 1)
		{
			my_mlx_pixel_put(&img, i, j, 0x00203FFF);
			j++;
		}
		i++;
	}
	mlx_put_image_to_window(cub->data->mlx, cub->data->win,
		img.img, cub->player->x, cub->player->y);
	render_line(cub, cub->player->x, cub->player->y,
		cub->player->x + cos(cub->player->angle) * 40,
		cub->player->y + sin(cub->player->angle) * 40, 0x00203FFF);
}
