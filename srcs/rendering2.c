/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rendering2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omanar <omanar@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/22 16:25:54 by omanar            #+#    #+#             */
/*   Updated: 2022/09/24 21:27:59 by omanar           ###   ########.fr       */
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
		my_mlx_pixel_put(cub->img, pixelx * 0.25, pixely * 0.25, color);
		pixelx += deltax;
		pixely += deltay;
		--pixels;
	}
}

void	next_display(t_cub *cub)
{
	float	move_step;
	float	new_px;
	float	new_py;

	mlx_clear_window(cub->data->mlx, cub->data->win);
	cub->player->angle += cub->player->turndir * cub->player->turnspeed;
	move_step = cub->player->walkdir * cub->player->walkspeed;
	new_px = cub->player->x + cos(cub->player->angle) * move_step;
	new_py = cub->player->y + sin(cub->player->angle) * move_step;
	if (is_onempty(cub, new_px, new_py))
	{
		cub->player->x = new_px;
		cub->player->y = new_py;
	}
	display_cub(cub);
}
