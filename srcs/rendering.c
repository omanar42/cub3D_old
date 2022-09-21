/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rendering.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omanar <omanar@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/15 20:19:53 by omanar            #+#    #+#             */
/*   Updated: 2022/09/21 17:35:33 by omanar           ###   ########.fr       */
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
	mlx_put_image_to_window(cub->data->mlx, cub->data->win, cub->map->img, 0, 0);
}

void	render_rays(t_cub *cub)
{
	cast_all_rays(cub);
}

void	render_player(t_cub *cub)
{
	mlx_pixel_put(cub->data->mlx, cub->data->win,
		cub->player->x, cub->player->y, 0x00203FFF);
	// render_line(cub, cub->player->x, cub->player->y,
	// 	cub->player->x + cos(cub->player->angle) * 40,
	// 	cub->player->y + sin(cub->player->angle) * 40, 0x00203FFF);
}
