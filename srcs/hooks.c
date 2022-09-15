/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omanar <omanar@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/15 20:23:43 by omanar            #+#    #+#             */
/*   Updated: 2022/09/15 21:03:13 by omanar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3D.h>

int	loop_hook(t_cub *cub)
{
	static int	frame = 0;

	(void)cub;
	if (frame == 30)
	{
		frame = 0;
	}
	else
		frame++;
	return (0);
}

int	key_hook(int keycode, t_cub *cub)
{
	if (keycode == ESC_KEY)
		exit(0);
	else if (keycode == W_KEY || keycode == UP_KEY)
		cub->player->walkdir = +1;
	else if (keycode == S_KEY || keycode == DOWN_KEY)
		cub->player->walkdir = -1;
	else if (keycode == D_KEY || keycode == RIGHT_KEY)
		cub->player->turndir = +1;
	else if (keycode == A_KEY || keycode == LEFT_KEY)
		cub->player->turndir = -1;
	move_player(cub);
	return (0);
}

int	set_defeult(int keycode, t_cub *cub)
{
	if (keycode == W_KEY || keycode == UP_KEY)
		cub->player->walkdir = 0;
	else if (keycode == S_KEY || keycode == DOWN_KEY)
		cub->player->walkdir = 0;
	else if (keycode == D_KEY || keycode == RIGHT_KEY)
		cub->player->turndir = 0;
	else if (keycode == A_KEY || keycode == LEFT_KEY)
		cub->player->turndir = 0;
	return (0);
}

int	is_onempty(t_cub *cub, float x, float y)
{
	int	map_grid_index_x;
	int	map_grid_index_y;

	(void)cub;
	if (x < 0 || x > (MAP_NUM_COLS * TILE_SIZE)
		|| y < 0 || y > (MAP_NUM_ROWS * TILE_SIZE))
		return (FALSE);
	map_grid_index_x = floor(x / TILE_SIZE);
	map_grid_index_y = floor(y / TILE_SIZE);
	return (map[map_grid_index_y][map_grid_index_x] == 0);
}

void	move_player(t_cub *cub)
{
	float	move_step;
	float	new_px;
	float	new_py;

	cub->player->angle += cub->player->turndir * cub->player->turnspeed;
	move_step = cub->player->walkdir * cub->player->walkspeed;
	new_px = cub->player->x + cos(cub->player->angle) * move_step;
	new_py = cub->player->y + sin(cub->player->angle) * move_step;
	if (is_onempty(cub, new_px, new_py))
	{
		cub->player->x = new_px;
		cub->player->y = new_py;
		mlx_clear_window(cub->data->mlx, cub->data->win);
		render_map(cub);
		render_player(cub);
	}
}