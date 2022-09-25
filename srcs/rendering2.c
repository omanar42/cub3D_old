/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rendering2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omanar <omanar@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/22 16:25:54 by omanar            #+#    #+#             */
/*   Updated: 2022/09/25 05:04:40 by omanar           ###   ########.fr       */
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

void	rendering_3d(t_cub *cub, int i,
	int wall_top_pixel, int wall_bottom_pixel)
{
	int	j;

	j = 0;
	while (j < wall_top_pixel)
		my_mlx_pixel_put(cub->cub, i, j++, 0x67C1CA);
	j = wall_top_pixel;
	while (j < wall_bottom_pixel)
	{
		if (cub->rays[i].was_hit_vertical)
			my_mlx_pixel_put(cub->cub, i, j++, 0xDFCD8B);
		else
			my_mlx_pixel_put(cub->cub, i, j++, 0xFFFFFF);
	}
	j = wall_bottom_pixel;
	while (j < WINDOW_HEIGHT)
		my_mlx_pixel_put(cub->cub, i, j++, 0xB1B3B2);
}

void	generate_3d_projection(t_cub *cub)
{
	int		i;
	float	perp_distance;
	float	distance_proj_plane;
	float	projected_wall_height;
	int		wall_strip_height;
	int		wall_top_pixel;
	int		wall_bottom_pixel;

	i = -1;
	while (++i < WINDOW_WIDTH)
	{
		perp_distance = cub->rays[i].distance
			* cos(cub->rays[i].angle - cub->player->angle);
		distance_proj_plane = (WINDOW_WIDTH / 2) / tan(FOV_ANGLE / 2);
		projected_wall_height = (TILE_SIZE / perp_distance)
			* distance_proj_plane;
		wall_strip_height = (int)projected_wall_height;
		wall_top_pixel = (WINDOW_HEIGHT / 2) - (wall_strip_height / 2);
		if (wall_top_pixel < 0)
			wall_top_pixel = 0;
		wall_bottom_pixel = (WINDOW_HEIGHT / 2) + (wall_strip_height / 2);
		if (wall_bottom_pixel > WINDOW_HEIGHT)
			wall_bottom_pixel = WINDOW_HEIGHT;
		rendering_3d(cub, i, wall_top_pixel, wall_bottom_pixel);
	}
}
