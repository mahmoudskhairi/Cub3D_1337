/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmarzouk <rmarzouk@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/16 18:19:17 by rmarzouk          #+#    #+#             */
/*   Updated: 2024/11/20 16:43:01 by rmarzouk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "game.h"

void mini_map(t_data *data)
{
	double x;
	double y;

	int i = 0;
	int j = 0;
	y = data->player.coor.y - 5 * TILE_SIZE;
	while (j < MINI_HEIGHT)
	{ 
		x = data->player.coor.x - 10 * TILE_SIZE;
		i = 0;
		while (i < MINI_WIDTH)
		{
			if (x >= 0 && x < (data->map.width * TILE_SIZE) && y >= 0 && y < (data->map.heigth * TILE_SIZE))
			{
				if (data->map.grid[(int)(y / TILE_SIZE)][(int)(x / TILE_SIZE)] == '1')
					my_mlx_put_pixel(data, data->ft_3D, (t_coor){i , j}, get_rgba(0, 0, 0, 255));
				if (data->map.grid[(int)(y / TILE_SIZE)][(int)(x / TILE_SIZE)] == '0'
				|| ft_strchr("NSEW", data->map.grid[(int)(y / TILE_SIZE)][(int)(x / TILE_SIZE)]))
					my_mlx_put_pixel(data, data->ft_3D, (t_coor){i , j}, get_rgba(246, 230, 203, 255));
			}
			x++;
			i++;
		}
		y++;
		j++;
	}
	draw_player(data, (t_coor){10 * TILE_SIZE, 5 * TILE_SIZE}, data->ft_3D);
}
// void mini_map(t_data *data)
// {
// 	double x;
// 	double y;

// 	y = data->player.coor.y / TILE_SIZE;
// 	x = data->player.coor.x / TILE_SIZE;
// 	double a = y + 5;
// 	y -= 5;
// 	while (y < a)
// 	{ 
// 		x = data->player.coor.x / TILE_SIZE;
// 		double z = x + 10;
// 			x -= 10;
// 		while (x < z)
// 		{
// 			if (x >= 0 && x < data->map.width && y >= 0 && y < data->map.heigth)
// 				draw_tile(data, (x + 10) * TILE_SIZE - data->player.coor.x,
// 					(y + 5)* TILE_SIZE - data->player.coor.y, data->map.grid[(int)y][(int)x], data->ft_3D);
// 			x++;
// 		}
// 		y++;
// 	}
// 	draw_player(data, (t_coor){10 * TILE_SIZE + fmod (data->player.coor.x, TILE_SIZE),
// 		5 * TILE_SIZE + fmod (data->player.coor.y, TILE_SIZE)}, data->ft_3D);
//
