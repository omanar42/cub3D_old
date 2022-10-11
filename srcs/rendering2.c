/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rendering2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omanar <omanar@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/22 16:25:54 by omanar            #+#    #+#             */
/*   Updated: 2022/10/12 00:31:50 by omanar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3D.h>

void	render_line(t_cub *cub, int endx, int endy, int color)
{
	int		pixels;
	double	pixelx;
	double	pixely;
	double	deltax;
	double	deltay;

	deltax = endx - cub->player->x;
	deltay = endy - cub->player->y;
	pixels = sqrt((deltax * deltax) + (deltay * deltay));
	deltax /= pixels;
	deltay /= pixels;
	pixelx = cub->player->x;
	pixely = cub->player->y;
	while (pixels && is_onempty(cub, pixelx, pixely, deltax, deltay))
	{
		my_mlx_pixel_put(cub->img, pixelx * 0.17, pixely * 0.17, color);
		pixelx += deltax;
		pixely += deltay;
		--pixels;
	}
}

int	player_can_move(t_cub *cub, int endx, int endy)
{
	int		pixels;
	double	pixelx;
	double	pixely;
	double	deltax;
	double	deltay;

	deltax = endx - cub->player->x;
	deltay = endy - cub->player->y;
	pixels = sqrt((deltax * deltax) + (deltay * deltay));
	deltax /= pixels;
	deltay /= pixels;
	pixelx = cub->player->x;
	pixely = cub->player->y;
	while (pixels && is_onempty(cub, pixelx, pixely, deltax, deltay))
	{
		pixelx += deltax;
		pixely += deltay;
		--pixels;
	}
	if (pixels == 0)
		return (TRUE);
	return (FALSE);
}

void	next_display(t_cub *cub)
{
	float	move_step;
	float	walk_step;
	float	new_px;
	float	new_py;

	cub->player->angle += cub->player->turndir * cub->player->turnspeed;
	walk_step = cub->player->walkdir * cub->player->walkspeed;
	move_step = cub->player->movedir * cub->player->walkspeed;
	if (cub->player->movedir != 0)
	{
		new_px = cub->player->x
			+ cos(cub->player->angle + M_PI / 2) * move_step;
		new_py = cub->player->y
			+ sin(cub->player->angle + M_PI / 2) * move_step;
	}
	else
	{
		new_px = cub->player->x + cos(cub->player->angle) * walk_step;
		new_py = cub->player->y + sin(cub->player->angle) * walk_step;
	}
	if (player_can_move(cub, new_px, new_py))
	{
		cub->player->x = new_px;
		cub->player->y = new_py;
	}
}

void	rendering_3d(t_cub *cub, int i,
	int wall_strip_height)
{
	int	j;
	int	wall_top_pixel;
	int	wall_bottom_pixel;

	j = 0;
	wall_top_pixel = (cub->data->window_height / 2) - (wall_strip_height / 2);
	if (wall_top_pixel < 0)
		wall_top_pixel = 0;
	wall_bottom_pixel = (cub->data->window_height / 2)
		+ (wall_strip_height / 2);
	if (wall_bottom_pixel > cub->data->window_height)
		wall_bottom_pixel = cub->data->window_height;
	while (j < wall_top_pixel)
		my_mlx_pixel_put(cub->cub, i, j++, cub->data->ceiling);
	j = wall_top_pixel;
	while (j < wall_bottom_pixel)
	{
		if (cub->rays[i].was_hit_vertical)
			my_mlx_pixel_put(cub->cub, i, j++, 0xDFCD8B);
		else
			my_mlx_pixel_put(cub->cub, i, j++, 0xFFFFFF);
	}
	j = wall_bottom_pixel;
	while (j < cub->data->window_height)
		my_mlx_pixel_put(cub->cub, i, j++, cub->data->floor);
}

void	generate_3d_projection(t_cub *cub)
{
	int		i;
	float	correct_distance;
	float	distance_proj_plane;
	float	projection_wall_height;
	int		wall_strip_height;

	i = -1;
	while (++i < cub->data->window_width)
	{
		correct_distance = cub->rays[i].distance
			* cos(cub->rays[i].angle - cub->player->angle);
		distance_proj_plane = (cub->data->window_width / 2)
			/ tan(cub->player->fov / 2);
		projection_wall_height = (TILE_SIZE / correct_distance)
			* distance_proj_plane;
		wall_strip_height = (int)projection_wall_height;
		rendering_3d(cub, i, wall_strip_height);
	}
}
