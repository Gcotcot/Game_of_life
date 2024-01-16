/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   controls.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcot <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/28 10:08:56 by gcot              #+#    #+#             */
/*   Updated: 2023/04/28 10:08:59 by gcot             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	close_win(t_data *data)
{
	mlx_destroy_window(data->mlx, data->win);
	data->win = NULL;
	return (0);
}

int	handle_keypress(int keysym, t_data *data)
{
	//int x = 0;
	//int y = 0;
	if (keysym == 65307)
		return (close_win(data));
	else if (keysym == 65451)
		change_size(1);
	else if (keysym == 65453)
		change_size(-1);
	else if (keysym == 65361)
		data->move_x += 5;
	else if (keysym == 65363)
		data->move_x -= 5;
	else if (keysym == 65362)
		data->move_y += 5;
	else if (keysym == 65364)
		data->move_y -= 5;
	else if (keysym == 65421)
	{
		if (!data->start)
			data->start = 1;
		else
		{
			for(int y = 0; y < (HEIGHT - 100) / 2; y++)
			{
				for(int x = 0; x < (WIDTH - 100) / 2; x++)
					data->map[y][x] = 0;
			} 
			data->start = 0;
		}
	}
	printf("%i\n", keysym);
	return (0);
}
