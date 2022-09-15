/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omanar <omanar@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/15 19:11:08 by omanar            #+#    #+#             */
/*   Updated: 2022/09/15 21:02:42 by omanar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <mlx.h>
# include <math.h>
# include <libft.h>
# include <stdio.h>
# include <fcntl.h>
# include <errno.h>
# include <unistd.h>
# include <stdlib.h>
# include <string.h>

# define TRUE 1
# define FALSE 0

# define ESC_KEY 53
# define A_KEY 0
# define D_KEY 2
# define W_KEY 13
# define S_KEY 1
# define LEFT_KEY 123
# define RIGHT_KEY 124
# define UP_KEY 126
# define DOWN_KEY 125

# define PI 3.14159265359
# define TWO_PI 6.28318530718

# define TILE_SIZE 64
# define MAP_NUM_ROWS 13
# define MAP_NUM_COLS 20

# define WINDOW_WIDTH (MAP_NUM_COLS * TILE_SIZE)
# define WINDOW_HEIGHT (MAP_NUM_ROWS * TILE_SIZE)

# define FOV_ANGLE (60 * (PI / 180))

# define NUM_RAYS WINDOW_WIDTH

static const int	map[MAP_NUM_ROWS][MAP_NUM_COLS] = {
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

typedef struct s_img {
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}	t_img;

typedef struct s_player {
	float	x;
	float	y;
	float	angle;
	int		turndir;
	int		walkdir;
	float	turnspeed;
	float	walkspeed;
}	t_player;

typedef struct s_data {
	void	*mlx;
	void	*win;
}	t_data;

typedef struct s_cub {
	t_data		*data;
	t_player	*player;
}	t_cub;

// ----------------------------  PARSING  ---------------------------- //
void	parsing(char *str);
void	file_checker(char *str);
void	initialize(t_cub *cub);
void	setup(t_cub *cub);

// -----------------------------  EXITS  ----------------------------- //
void	exit_str(char *str);
void	exit_success(char *str);
void	exit_error(char *str, char *err);
void	exit_strerr(char *str, int err);

// ---------------------------  RENDERING  --------------------------- //
void	render_map(t_cub *cub);
void	render_player(t_cub *cub);
void	render_line(t_cub *cub, int beginx, int beginy,
			int endx, int endy, int color);

// -----------------------------  UTILS ------------------------------ //
int		distroy_event(int keycode, t_cub *cub);
void	my_pixel_put(t_img *img, int x, int y, int color);
void	my_mlx_pixel_put(t_img *img, int x, int y, int color);

// -----------------------------  HOOKS ------------------------------ //
int		key_hook(int keycode, t_cub *cub);
int		loop_hook(t_cub *cub);
int		set_defeult(int keycode, t_cub *cub);
int		is_onempty(t_cub *cub, float x, float y);
void	move_player(t_cub *cub);

#endif
