/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setup.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omanar <omanar@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/22 16:02:57 by omanar            #+#    #+#             */
/*   Updated: 2022/10/24 04:24:34 by omanar           ###   ########.fr       */
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
			* 0.17, cub->data->window_height * 0.17);
	cub->img->addr = mlx_get_data_addr(cub->img->img, &cub->img->bits_per_pixel,
			&cub->img->line_length, &cub->img->endian);
	cub->img->width = cub->data->window_width * 0.17;
	cub->img->height = cub->data->window_height * 0.17;
	cub->cub->img = mlx_new_image(cub->mlxdata->mlx,
			cub->data->window_width, cub->data->window_height);
	cub->cub->addr = mlx_get_data_addr(cub->cub->img, &cub->cub->bits_per_pixel,
			&cub->cub->line_length, &cub->cub->endian);
	cub->cub->width = cub->data->window_width;
	cub->cub->height = cub->data->window_height;
	cub->assets->no->img = mlx_xpm_file_to_image(cub->mlxdata->mlx,
			cub->data->no, &cub->assets->width, &cub->assets->height);
	cub->assets->no->addr = mlx_get_data_addr(cub->assets->no->img,
			&cub->assets->no->bits_per_pixel, &cub->assets->no->line_length,
			&cub->assets->no->endian);
	cub->assets->so->img = mlx_xpm_file_to_image(cub->mlxdata->mlx, cub->data->so,
			&cub->assets->width, &cub->assets->height);
	cub->assets->so->addr = mlx_get_data_addr(cub->assets->so->img,
			&cub->assets->so->bits_per_pixel, &cub->assets->so->line_length,
			&cub->assets->so->endian);
	cub->assets->we->img = mlx_xpm_file_to_image(cub->mlxdata->mlx, cub->data->we,
			&cub->assets->width, &cub->assets->height);
	cub->assets->we->addr = mlx_get_data_addr(cub->assets->we->img,
			&cub->assets->we->bits_per_pixel, &cub->assets->we->line_length,
			&cub->assets->we->endian);
	cub->assets->ea->img = mlx_xpm_file_to_image(cub->mlxdata->mlx, cub->data->ea,
			&cub->assets->width, &cub->assets->height);
	cub->assets->ea->addr = mlx_get_data_addr(cub->assets->ea->img,
			&cub->assets->ea->bits_per_pixel, &cub->assets->ea->line_length,
			&cub->assets->ea->endian);
}

void	display_cub(t_cub *cub)
{
	set_map(cub);
	set_all_rays(cub);
	set_player(cub);
	generate_3d_projection(cub);
	render_cub(cub);
}

void	setup(t_cub *cub)
{
	set_hooks(cub);
	set_cub(cub);
	display_cub(cub);
}
