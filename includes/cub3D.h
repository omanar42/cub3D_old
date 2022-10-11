/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omanar <omanar@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/15 19:11:08 by omanar            #+#    #+#             */
/*   Updated: 2022/10/11 23:33:12 by omanar           ###   ########.fr       */
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
# include <get_next_line.h>

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

# define TWO_PI 6.28318530718

# define TILE_SIZE 64

# define FOV_ANGLE (60 * (M_PI / 180))

# define NUM_RAYS WINDOW_WIDTH

enum {
	TOKEN_NO,
	TOKEN_SO,
	TOKEN_WE,
	TOKEN_EA,
	TOKEN_F,
	TOKEN_C,
	TOKEN_MAP,
	TOKEN_ERROR,
}	e_type;

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
	int		movedir;
	float	turnspeed;
	float	walkspeed;
}	t_player;

typedef struct s_ray
{
	float	angle;
	float	wall_hit_x;
	float	wall_hit_y;
	float	distance;
	int		was_hit_vertical;
	int		is_ray_facing_up;
	int		is_ray_facing_down;
	int		is_ray_facing_left;
	int		is_ray_facing_right;
	int		wall_hit_content;
}	t_ray;

typedef struct s_mlxdata {
	void	*mlx;
	void	*win;
	void	*no_img;
	void	*so_img;
	void	*we_img;
	void	*ea_img;
}	t_mlxdata;


typedef struct s_data {
	char	*no;
	char	*so;
	char	*we;
	char	*ea;
	int		floor;
	int		ceiling;
	int		width;
	int		height;
	int		window_width;
	int		window_height;
	char	**map;
}	t_data;

typedef struct s_cub {
	t_img		*img;
	t_img		*cub;
	t_ray		*rays;
	t_data		*data;
	t_player	*player;
	t_mlxdata	*mlxdata;
}	t_cub;

// ----------------------------  PARSING  ---------------------------- //
void	parsing(t_cub *cub, char *str);
void	file_checker(char *str);
void	file_parsing(t_cub *cub, int fd);
int		line_parsing(t_cub *cub, char *line);
void	color_parsing(t_cub *cub, char *line, int token, int i);
void	texture_parsing(t_cub *cub, char *line, int token, int i);
void	map_parsing(t_cub *cub, char *line, int fd);

// --------------------------  PARSING UTILS ------------------------- //
void	skipe_spaces(char *s, int *i);
int		is_map(char *line);
int		check_name(char *name);
int		argslen(char **args);
void	free_loop(char **args);
char	**advanced_add(char **strs, char *arg);

// --------------------------  INITIALIZING  ------------------------- //
void	init_data(t_cub *cub);
void	initialize(t_cub *cub);
void	player_config(t_cub *cub);

// -----------------------------  SETUP  ----------------------------- //
void	setup(t_cub *cub);
void	set_hooks(t_cub *cub);
void	set_cub(t_cub *cub);
void	display_cub(t_cub *cub);

// ---------------------------  RENDERING  --------------------------- //
void	render_line(t_cub *cub, int beginx, int beginy,
			int endx, int endy, int color);
void	set_all_rays(t_cub *cub);
void	cast_ray(t_cub *cub, float ray_angle, int ray);
void	set_map(t_cub *cub);
void	set_player(t_cub *cub);
void	render_cub(t_cub *cub);
void	next_display(t_cub *cub);
void	generate_3d_projection(t_cub *cub);
void	rendering_3d(t_cub *cub, int i,
			int wall_strip_height);

// -----------------------------  HOOKS ------------------------------ //
int		key_press(int keycode, t_cub *cub);
int		key_release(int keycode, t_cub *cub);
int		loop_hook(t_cub *cub);
int		distroy_event(int keycode, t_cub *cub);

// -----------------------------  UTILS ------------------------------ //
void	my_pixel_put(t_img *img, int x, int y, int color);
void	my_mlx_pixel_put(t_img *img, int x, int y, int color);
int		is_onempty(t_cub *cub, float x, float y, float dx, float dy);
int		is_his_vertical(float ray_angle);
float	get_distance(t_cub *cub, float ray_angle);

// -----------------------------  EXITS  ----------------------------- //
void	exit_str(char *str);
void	exit_success(char *str);
void	exit_error(char *str, char *err);
void	exit_strerr(char *str, int err);

#endif
