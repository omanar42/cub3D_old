/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omanar <omanar@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/15 19:11:31 by omanar            #+#    #+#             */
/*   Updated: 2022/09/15 03:30:56 by omanar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3D.h>

const int	map[MAP_NUM_ROWS][MAP_NUM_COLS] = {
{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
{1, 0, 0, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 0, 1},
{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 1},
{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 1},
{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 1},
{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 0, 0, 1},
{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}
};

int	distroy_event(int keycode, t_cub *cub)
{
	(void)cub;
	(void)keycode;
	exit(0);
	return (0);
}

int	is_onwall(t_cub *cub, float x, float y)
{
	int	map_grid_index_x;
	int	map_grid_index_y;

	(void)cub;
	map_grid_index_x = floor(x / TILE_SIZE);
	map_grid_index_y = floor(y / TILE_SIZE);
	return (map[map_grid_index_y][map_grid_index_x] != 0);
}

void	move_player(t_cub *cub)
{
	float	move_step;
	float	new_px;
	float	new_py;

	mlx_clear_window(cub->data->mlx, cub->data->win);
	cub->player->angle += cub->player->turndir * cub->player->turnspeed;
	move_step = cub->player->walkdir * cub->player->walkspeed;
	new_px = cub->player->x + cos(cub->player->angle) * move_step;
	new_py = cub->player->y + sin(cub->player->angle) * move_step;
	if (!is_onwall(cub, new_px, new_py))
	{
		cub->player->x = new_px;
		cub->player->y = new_py;
	}
	render_map(cub);
	render_player(cub);
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

void	initialize(t_cub *cub)
{
	cub->data = malloc(sizeof(t_data));
	cub->player = malloc(sizeof(t_player));
	if (!cub->data || !cub->player)
		exit_strerr("malloc", errno);
	cub->data->mlx = mlx_init();
	if (!cub->data->mlx)
		exit_error("mlx_init", "Error initializing MLX");
	cub->data->win = mlx_new_window(cub->data->mlx,
			WINDOW_WIDTH, WINDOW_HEIGHT, "cub3D");
	if (!cub->data->win)
		exit_error("mlx_new_window", "Error creating MLX window");
}

void	my_mlx_pixel_put(t_img *img, int x, int y, int color)
{
	char	*dst;

	dst = img->addr + (y * img->line_length + x * (img->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}

void	my_pixel_put(t_img *img, int x, int y, int color)
{
	int	i;
	int	j;

	i = 0;
	while (i < TILE_SIZE)
	{
		j = 0;
		while (j < TILE_SIZE)
		{
			my_mlx_pixel_put(img, x + i, y + j, color);
			j++;
		}
		i++;
	}
}

void	draw_line(t_cub *cub, int beginx, int beginy,
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

void	render_map(t_cub *cub)
{
	int		i;
	int		j;
	int		tilex;
	int		tiley;
	t_img	img;

	img.img = mlx_new_image(cub->data->mlx, WINDOW_WIDTH, WINDOW_HEIGHT);
	img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel,
			&img.line_length, &img.endian);
	j = 0;
	while (j < MAP_NUM_ROWS)
	{
		i = 0;
		while (i < MAP_NUM_COLS)
		{
			tilex = i * TILE_SIZE;
			tiley = j * TILE_SIZE;
			if (map[j][i] == 1)
				my_pixel_put(&img, tilex, tiley, 0xDFCD8B);
			else
				my_pixel_put(&img, tilex, tiley, 0xB1B3B2);
			i++;
		}
		j++;
	}
	mlx_put_image_to_window(cub->data->mlx, cub->data->win, img.img, 0, 0);
}

void	render_player(t_cub *cub)
{
	int		i;
	int		j;
	t_img	img;

	img.img = mlx_new_image(cub->data->mlx, 1, 1);
	img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel,
			&img.line_length, &img.endian);
	i = 0;
	while (i < 1)
	{
		j = 0;
		while (j < 1)
		{
			my_mlx_pixel_put(&img, i, j, 0x00203FFF);
			j++;
		}
		i++;
	}
	mlx_put_image_to_window(cub->data->mlx, cub->data->win,
		img.img, cub->player->x, cub->player->y);
	draw_line(cub, cub->player->x, cub->player->y,
		cub->player->x + cos(cub->player->angle) * 40,
		cub->player->y + sin(cub->player->angle) * 40, 0x00203FFF);
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

void	setup(t_cub *cub)
{
	cub->player->x = WINDOW_WIDTH / 2;
	cub->player->y = WINDOW_HEIGHT / 2;
	cub->player->angle = PI / 2;
	cub->player->turndir = 0;
	cub->player->walkdir = 0;
	cub->player->turnspeed = 5 * (PI / 180);
	cub->player->walkspeed = 10;
	mlx_hook(cub->data->win, 2, 0, key_hook, cub);
	mlx_hook(cub->data->win, 3, 0, set_defeult, cub);
	mlx_hook(cub->data->win, 17, 0, distroy_event, cub);
	// mlx_loop_hook(cub->data->mlx, loop_hook, cub);
	render_map(cub);
	// render_rays(cub);
	render_player(cub);
}

int	main(int ac, char **av)
{
	t_cub	*cub;

	if (ac != 2)
		exit_success("Usage: ./cub3D <map.cub>");
	cub = (t_cub *)malloc(sizeof(t_cub));
	parsing(av[1]);
	initialize(cub);
	setup(cub);
	mlx_loop(cub->data->mlx);
	return (0);
}
