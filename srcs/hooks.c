/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omanar <omanar@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/15 20:23:43 by omanar            #+#    #+#             */
/*   Updated: 2022/09/27 16:21:42 by omanar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3D.h>

int	distroy_event(int keycode, t_cub *cub)
{
	(void)cub;
	(void)keycode;
	exit(EXIT_SUCCESS);
	return (0);
}

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

int	key_press(int keycode, t_cub *cub)
{
	if (keycode == ESC_KEY)
		exit(0);
	else if (keycode == W_KEY)
		cub->player->walkdir = +1;
	else if (keycode == S_KEY)
		cub->player->walkdir = -1;
	else if (keycode == D_KEY)
		cub->player->movedir = +1;
	else if (keycode == A_KEY)
		cub->player->movedir = -1;
	else if (keycode == UP_KEY)
		cub->player->walkdir = +1;
	else if (keycode == DOWN_KEY)
		cub->player->walkdir = -1;
	else if (keycode == RIGHT_KEY)
		cub->player->turndir = +1;
	else if (keycode == LEFT_KEY)
		cub->player->turndir = -1;
	next_display(cub);
	return (0);
}

int	key_release(int keycode, t_cub *cub)
{
	if (keycode == W_KEY)
		cub->player->walkdir = 0;
	else if (keycode == S_KEY)
		cub->player->walkdir = 0;
	else if (keycode == D_KEY)
		cub->player->movedir = 0;
	else if (keycode == A_KEY)
		cub->player->movedir = 0;
	else if (keycode == UP_KEY)
		cub->player->walkdir = 0;
	else if (keycode == DOWN_KEY)
		cub->player->walkdir = 0;
	else if (keycode == RIGHT_KEY)
		cub->player->turndir = 0;
	else if (keycode == LEFT_KEY)
		cub->player->turndir = 0;
	return (0);
}
