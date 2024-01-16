/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_game.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcot <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/14 13:57:32 by gcot              #+#    #+#             */
/*   Updated: 2023/06/14 14:09:42 by gcot             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int size_square = SIZE_SQUARE;
int size_line = 1;

void change_size(int i)
{
	if (size_square + i >= 1)
		size_square += i;
}

int mouse_win3(int x,int y, t_data *data)
{
	if (!data->start)
	{
		printf("Mouse moving in Win3, at %dx%d.\n",x,y);
		if (data->draw)
			data->map[(y-50)/(size_square + size_line)][(x-50)/(size_square + size_line)] = 1;
		else if (data->clear)
			data->map[(y-50)/(size_square + size_line)][(x-50)/(size_square + size_line)] = 0;
	}
	return (0);
}

int mouse_win(int button,int x,int y, t_data *data)
{
	if (!data->start)
	{
		if (button == 1)
		{
			if (data->draw)
				data->draw = 0;
			else
				data->draw = 1;
			if (data->clear)
				data->clear = 0;
		}
		else if (button == 3)
		{
			if (data->clear)
				data->clear = 0;
			else
				data->clear = 1;
			if (data->draw)
				data->draw = 0;
		}
		printf("Mouse in Win1, button %d at %dx%d.\n",button,x,y);
	}
	return (0);
}

void draw_line(t_data *data)
{
	int x;
	int y = 49;
	while (y <= HEIGHT - 49)
	{
		x = 49;
		while (x <= WIDTH - 49)
		{
			img_pix_put(&data->img, x, y, 0x606060);
			x++;
		}
		y += size_square + size_line;
	}	
	x = 49;
	while (x <= WIDTH - 49)
	{
		y = 49;
		while (y <= HEIGHT - 49)
		{
			img_pix_put(&data->img, x, y, 0x606060);
			y++;
		}
		x += size_square + size_line;
	}
}

void draw_plate(t_data *data)
{
	int y = 50 + data->move_y;
	int size = size_square + size_line;
	int color;
	while (y < HEIGHT - 50)
	{
		int x = 50 + data->move_x;
		while (x < WIDTH - 50)
		{
			if (data->map[(y - 50)/size][(x - 50)/size] == 0)
				
				color = 0xffffff;
			else
				color = 0x000000;
			for (int g = y; g < y + size_square && g <= HEIGHT - 50; g++)
			{
				for (int l = x; l < x + size_square && l <= WIDTH - 50; l++)
					img_pix_put(&data->img, l, g, color);
			}
			x+=size;
		}
		y+=size;
	}
}

void game(t_data *data)
{
	int y = 0;
	while (y < (HEIGHT - 100) / 2)
	{
		int x = 0;
		while (x < (WIDTH - 100) / 2)
		{
			int neigh = 0;
			if (x > 0 && data->map[y][(x - 1)])
				neigh++;
			if (x < ((WIDTH - 100) / 2 - 1) && data->map[y][x + 1])
				neigh++;
			if (y > 0 && data->map[y - 1][x])
				neigh++;
			if (y < ((HEIGHT - 100) / 2 - 1) && data->map[y + 1][x])
				neigh++;
				
			if (x > 0 && y > 0 && data->map[y - 1][x - 1])
				neigh++;
			if (x > 0 && y < ((HEIGHT - 100) / 2 - 1) && data->map[y + 1][x - 1])
				neigh++;
			if (x < ((WIDTH - 100) / 2 - 1) && y > 0 && data->map[y - 1][x + 1])
				neigh++;
			if (x < ((WIDTH - 100) / 2 - 1) && y < ((HEIGHT - 100) / 2 - 1) / 2 && data->map[y + 1][x + 1])
				neigh++;
	
			if ((data->map[y][x] == 0 && neigh == 3) || (data->map[y][x] == 1 && (neigh == 2 || neigh == 3)))
				data->new_map[y][x] = 1;
			else
				data->new_map[y][x] = 0;
			x++;
		}
		y++;
	}
	for(y = 0; y < (HEIGHT - 100) / 2; y++)
	{
		for(int x = 0; x < (WIDTH - 100) / 2; x++)
			data->map[y][x] = data->new_map[y][x];
	} 
}
