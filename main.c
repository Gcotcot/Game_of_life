/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcot <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/05 11:05:37 by gcot              #+#    #+#             */
/*   Updated: 2023/04/05 11:27:10 by gcot             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	img_pix_put(t_img *img, int x, int y, int color)
{
	char	*pixel;
	int		i;

	if ((y >= 0 && x >= 0) && (y < HEIGHT && x < WIDTH))
	{
		i = img->bpp - 8;
		pixel = img->addr + (y * img->line_len + x * (img->bpp / 8));
		while (i >= 0)
		{
			if (img->endian != 0)
				*pixel++ = (color >> i) & 0xFF;
			else
				*pixel++ = (color >> (img->bpp - 8 - i)) & 0xFF;
			i -= 8;
		}
	}
}

void	render_background(t_img *img, int color, int heigth, int width)
{
	int	i;
	int	j;

	i = 0;
	while (i < width)
	{
		j = 0;
		while (j < heigth)
		{
			img_pix_put(img, j, i, color);
			j++;
		}
		i++;
	}
}

int	render(t_data *data)
{
	//usleep(refresh);
	if (data->win == NULL)
		return (1);
	//render_background(&data->img, 0x000000, WIDTH, HEIGHT);
	if (data->start)
		game(data);
	draw_plate(data);
	draw_line(data);
	mlx_put_image_to_window(data->mlx, data->win, data->img.mlx_img, 0, 0);
	return (0);
}

int	begin(t_data *data)
{
	data->win = mlx_new_window(data->mlx, WIDTH, HEIGHT, "Game of life");
	if (data->win == NULL)
	{
		free(data->win);
		return (1);
	}
	data->map = malloc(sizeof(*data->map) * (HEIGHT - 100) / 2);
	data->new_map = malloc(sizeof(*data->new_map) * (HEIGHT - 100) / 2);
	for (int i = 0; i < (HEIGHT - 100) / 2; i++)
	{
		data->map[i] = malloc(sizeof(**data->map) * (WIDTH - 100) / 2);
		data->new_map[i] = malloc(sizeof(**data->new_map) * (WIDTH - 100) / 2);
	}
	data->start = 0;
	data->move_x = 0;
	data->move_y = 0;
	data->draw = 0;
	data->clear = 0;
	return (0);
}

int	main(void)
{
	t_data	data;

	data.mlx = mlx_init();
	if (data.mlx == NULL)
		return (1);
	begin(&data);
	data.img.mlx_img = mlx_new_image(data.mlx, WIDTH, HEIGHT);
	data.img.addr = mlx_get_data_addr(data.img.mlx_img, &data.img.bpp, &data.img.line_len, &data.img.endian);
	mlx_loop_hook(data.mlx, &render, &data);
	//mlx_hook(data.win, KeyPress, KeyPressMask, &handle_keypress, &data);
	mlx_hook(data.win, 2, 1, &handle_keypress, &data);
	mlx_mouse_hook(data.win, &mouse_win, &data);
	mlx_hook(data.win, MotionNotify, PointerMotionMask, mouse_win3, &data);
	mlx_hook(data.win, 17, 1, &close_win, &data);
	mlx_loop(data.mlx);
	mlx_destroy_image(data.mlx, data.img.mlx_img);
	mlx_destroy_display(data.mlx);
	for (int i = 0; i < (HEIGHT - 100) / 2; i++)
	{
		free(data.new_map[i]);
		free(data.map[i]);
	}
	free(data.map);
	free(data.new_map);
	free(data.mlx);
	return (0);
}
