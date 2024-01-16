/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcot <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/05 11:08:25 by gcot              #+#    #+#             */
/*   Updated: 2023/04/05 12:31:04 by gcot             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# define HEIGHT 2000
# define WIDTH 3000
# define SIZE_SQUARE 2

# include "minilibx/mlx.h"
# include <unistd.h>
# include <stdio.h>
# include <X11/X.h>
# include <X11/keysym.h>
# include <fcntl.h>
# include <stdlib.h>


typedef struct s_controls
{
	int		x;
	int		y;
	int		cut;
	float	zoom;
}	t_controls;

typedef struct s_img
{
	void	*mlx_img;
	char	*addr;
	int		height;
	int		width;
	int		bpp;
	int		line_len;
	int		endian;
}	t_img;

typedef struct s_data
{
	void		*mlx;
	void		*win;
	t_img		img;
	int			cur_img;
	int		**map;
	int		**new_map;
	int		start;
	int		move_y;
	int		move_x;
	int		draw;
	int		clear;
	t_controls	controls;
}	t_data;
;
void	set_controls(t_controls *controls);
void	draw_line(t_data *data);
void	img_pix_put(t_img *img, int x, int y, int color);
void	size_win(int width, int height, t_img *img);
void	draw_plate(t_data *data);
void	change_size(int i);
void	game(t_data *data);
int		close_win(t_data *data);
int		handle_keypress(int keysym, t_data *data);
int		mouse_win(int button,int x,int y, t_data *data);
int		mouse_win3(int x,int y, t_data *data);

#endif
