/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initializing.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omanar <omanar@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/15 20:23:10 by omanar            #+#    #+#             */
/*   Updated: 2022/10/11 23:37:48 by omanar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3D.h>

void	initialize(t_cub *cub)
{
	if (!cub)
		exit_strerr("malloc", errno);
	cub->img = malloc(sizeof(t_img));
	cub->cub = malloc(sizeof(t_img));
	cub->data = malloc(sizeof(t_data));
	cub->player = malloc(sizeof(t_player));
	cub->mlxdata = malloc(sizeof(t_mlxdata));
	cub->data->map = ft_calloc(1, sizeof(char *));
	if (!cub->img || !cub->cub || !cub->data
		|| !cub->player || !cub->data->map || !cub->mlxdata)
		exit_strerr("malloc", errno);
	init_data(cub);
	player_config(cub);
}

void	init_data(t_cub *cub)
{
	cub->data->no = NULL;
	cub->data->so = NULL;
	cub->data->we = NULL;
	cub->data->ea = NULL;
	cub->data->floor = -1;
	cub->data->ceiling = -1;
	cub->data->width = 0;
	cub->data->height = 0;
	cub->data->map[0] = NULL;
}

void	player_config(t_cub *cub)
{
	cub->player->x = -1;
	cub->player->y = -1;
	cub->player->angle = 0;
	cub->player->turndir = 0;
	cub->player->walkdir = 0;
	cub->player->movedir = 0;
	cub->player->turnspeed = 5 * (M_PI / 180);
	cub->player->walkspeed = 10;
}
