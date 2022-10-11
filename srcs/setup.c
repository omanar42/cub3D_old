/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setup.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omanar <omanar@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/22 16:02:57 by omanar            #+#    #+#             */
/*   Updated: 2022/10/11 22:15:19 by omanar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3D.h>

void	set_hooks(t_cub *cub)
{
	mlx_hook(cub->mlxdata->win, 2, 0, key_press, cub);
	mlx_hook(cub->mlxdata->win, 3, 0, key_release, cub);
	mlx_hook(cub->mlxdata->win, 17, 0, distroy_event, cub);
	// mlx_loop_hook(cub->mlx, loop_hook, cub);
}

void	set_cub(t_cub *cub)
{
	cub->img->img = mlx_new_image(cub->mlxdata->mlx, cub->data->window_width
			* 0.25, cub->data->window_height * 0.25);
	cub->img->addr = mlx_get_data_addr(cub->img->img, &cub->img->bits_per_pixel,
			&cub->img->line_length, &cub->img->endian);
	cub->cub->img = mlx_new_image(cub->mlxdata->mlx, cub->data->window_width, cub->data->window_height);
	cub->cub->addr = mlx_get_data_addr(cub->cub->img, &cub->cub->bits_per_pixel,
			&cub->cub->line_length, &cub->cub->endian);
}

void	clear_color_buffer(t_cub *cub)
{
	int	x;
	int	y;

	x = 0;
	while (x < cub->data->window_width)
	{
		y = 0;
		while (y < cub->data->window_height)
		{
			if (y >= cub->data->window_height / 2)
				my_mlx_pixel_put(cub->cub, x, y, 0xB1B3B2);
			else
				my_mlx_pixel_put(cub->cub, x, y, 0x67C1CA);
			y++;
		}
		x++;
	}
}

void	display_cub(t_cub *cub)
{
	set_map(cub);
	set_all_rays(cub);
	set_player(cub);
	// clear_color_buffer(cub);
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
