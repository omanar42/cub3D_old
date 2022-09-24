/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setup.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omanar <omanar@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/22 16:02:57 by omanar            #+#    #+#             */
/*   Updated: 2022/09/24 23:10:46 by omanar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3D.h>

void	set_hooks(t_cub *cub)
{
	mlx_hook(cub->data->win, 2, 0, key_press, cub);
	mlx_hook(cub->data->win, 3, 0, key_release, cub);
	mlx_hook(cub->data->win, 17, 0, distroy_event, cub);
	// mlx_loop_hook(cub->data->mlx, loop_hook, cub);
}

void	set_cub(t_cub *cub)
{
	cub->img->img = mlx_new_image(cub->data->mlx, WINDOW_WIDTH * 0.25, WINDOW_HEIGHT * 0.25);
	cub->img->addr = mlx_get_data_addr(cub->img->img, &cub->img->bits_per_pixel,
			&cub->img->line_length, &cub->img->endian);
	cub->cub->img = mlx_new_image(cub->data->mlx, WINDOW_WIDTH, WINDOW_HEIGHT);
	cub->cub->addr = mlx_get_data_addr(cub->cub->img, &cub->cub->bits_per_pixel,
			&cub->cub->line_length, &cub->cub->endian);
}

void	clear_color_buffer(t_cub *cub)
{
	int	x;
	int	y;

	x = 0;
	while (x < WINDOW_WIDTH)
	{
		y = 0;
		while (y < WINDOW_HEIGHT)
		{
				my_mlx_pixel_put(cub->cub, x, y, 0xB1B3B2);
			y++;
		}
		x++;
	}
}

void	generate_3d_projection(t_cub *cub)
{
	int		i;
	float perp_distance;
	float distance_proj_plane;
	float projected_wall_height;
	int wall_strip_height;
	int wall_top_pixel;
	int wall_bottom_pixel;

	i = 0;
	while (i < WINDOW_WIDTH)
	{
		perp_distance = cub->rays[i].distance * cos(cub->rays[i].angle - cub->player->angle);
		distance_proj_plane = (WINDOW_WIDTH / 2) / tan(FOV_ANGLE / 2);
		projected_wall_height = (TILE_SIZE / perp_distance) * distance_proj_plane;
		wall_strip_height = (int)projected_wall_height;
		wall_top_pixel = (WINDOW_HEIGHT / 2) - (wall_strip_height / 2);
		if (wall_top_pixel < 0)
			wall_top_pixel = 0;
		wall_bottom_pixel = (WINDOW_HEIGHT / 2) + (wall_strip_height / 2);
		if (wall_bottom_pixel > WINDOW_HEIGHT)
			wall_bottom_pixel = WINDOW_HEIGHT;
		for (int j = wall_top_pixel; j < wall_bottom_pixel; j++)
			my_mlx_pixel_put(cub->cub, i, j, 0xDFCD8B);
		i++;
	}
}

void	display_cub(t_cub *cub)
{
	set_map(cub);
	set_all_rays(cub);
	set_player(cub);
	clear_color_buffer(cub);
	generate_3d_projection(cub);
	render_cub(cub);
}

void	setup(t_cub *cub)
{
	player_config(cub);
	set_hooks(cub);
	set_cub(cub);
	display_cub(cub);
}
