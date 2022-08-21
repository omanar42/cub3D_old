/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omanar <omanar@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/15 19:11:08 by omanar            #+#    #+#             */
/*   Updated: 2022/08/21 02:58:20 by omanar           ###   ########.fr       */
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

typedef struct s_data {
	void	*mlx;
	void	*win;
}	t_data;

typedef struct s_cub {
	t_data	*data;
}	t_cub;

t_cub	g_cub;

void	parsing(char *str);

void	exit_str(char *str);
void	exit_error(char *str, char *err);
void	exit_strerr(char *str, int err);

#endif