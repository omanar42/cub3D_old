/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rendering.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omanar <omanar@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/15 20:19:53 by omanar            #+#    #+#             */
/*   Updated: 2022/09/22 04:36:15 by omanar           ###   ########.fr       */
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
	while (pixels && is_onempty(cub, pixelx, pixely))
	{
		my_mlx_pixel_put(cub->img, pixelx, pixely, color);
		pixelx += deltax;
		pixely += deltay;
		--pixels;
	}
}

void	set_cub(t_cub *cub)
{
	cub->img->img = mlx_new_image(cub->data->mlx, WINDOW_WIDTH, WINDOW_HEIGHT);
	cub->img->addr = mlx_get_data_addr(cub->img->img, &cub->img->bits_per_pixel,
			&cub->img->line_length, &cub->img->endian);
}

void	render_cub(t_cub *cub)
{
	mlx_put_image_to_window(cub->data->mlx, cub->data->win, cub->img->img, 0, 0);
}

void	set_player(t_cub *cub)
{
	my_mlx_pixel_put(cub->img, cub->player->x, cub->player->y, 0x00203FFF);
	// render_line(cub, cub->player->x, cub->player->y,
	// 	cub->player->x + cos(cub->player->angle) * 40,
	// 	cub->player->y + sin(cub->player->angle) * 40, 0x00203FFF);
}
