/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_hooks.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mskhairi <mskhairi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/15 10:06:49 by rmarzouk          #+#    #+#             */
/*   Updated: 2024/11/18 15:25:36 by mskhairi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "raycasting.h"


int	collision_detected(t_map map, t_coor p_coor)
{
	if (map.grid[(int)(p_coor.y / TILE_SIZE)]
	&& map.grid[(int)(p_coor.y / TILE_SIZE)][(int)(p_coor.x / TILE_SIZE)] 
	&& map.grid[(int)(p_coor.y / TILE_SIZE)][(int)(p_coor.x / TILE_SIZE)] == '1')
		return (1);
	return (0);
}

void	key(t_data *data)
{
	t_coor next;
	next = data->player.coor;
    mlx_get_mouse_pos(data->mlx, &data->mouse_position.x, &data->mouse_position.y);
    if (!(data->mouse_position.x >=0 && data->mouse_position.x <= WIDTH) || !(data->mouse_position.y >=0 && data->mouse_position.y <= HEIGHT))
        mlx_set_mouse_pos(data->mlx, WIDTH / 2, HEIGHT / 2);
	if ((mlx_is_key_down(data->mlx, MLX_KEY_RIGHT) || data->tmp_p_mouse <= data->mouse_position.x - 10))//(data->mouse_position.x >=0 && data->mouse_position.x <= WIDTH) && (data->mouse_position.y >=0 && data->mouse_position.y <= HEIGHT) 
	{
		data->player.angle = ft_normalizer(data->player.angle + DEGREE);
        data->tmp_p_mouse = data->mouse_position.x;
        // printf("x_------>%d\n", x_);
		// printf("angle = %f\n", data->player.angle);
	}
	if ((mlx_is_key_down(data->mlx, MLX_KEY_LEFT) || data->tmp_p_mouse >= data->mouse_position.x + 10))//(data->mouse_position.x >=0 && data->mouse_position.x <= WIDTH) && (data->mouse_position.y >=0 && data->mouse_position.y <= HEIGHT)
	{
		data->player.angle = ft_normalizer(data->player.angle - DEGREE);
        data->tmp_p_mouse = data->mouse_position.x;
		// printf("angle = %f\n", data->player.angle);
	}
	if (mlx_is_key_down(data->mlx, MLX_KEY_W) || mlx_is_key_down(data->mlx, MLX_KEY_UP))
	{

		
		next.x = data->player.coor.x + cos(data->player.angle) * SPEED ;
		next.y = data->player.coor.y + sin(data->player.angle) * SPEED ;
	}
	if (mlx_is_key_down(data->mlx, MLX_KEY_S) || mlx_is_key_down(data->mlx, MLX_KEY_DOWN))
	{
		next.x = data->player.coor.x - cos(data->player.angle) * SPEED ;
		next.y = data->player.coor.y - sin(data->player.angle) * SPEED ;
	}
	if (mlx_is_key_down(data->mlx, MLX_KEY_A))
	{
		next.x = data->player.coor.x + cos(data->player.angle - DEGREE_90) * SPEED ;
		next.y = data->player.coor.y +  sin(data->player.angle - DEGREE_90) * SPEED ;
	}
	if (mlx_is_key_down(data->mlx, MLX_KEY_D))
	{
		next.x = data->player.coor.x + cos(data->player.angle + DEGREE_90) * SPEED ;
		next.y = data->player.coor.y + sin(data->player.angle + DEGREE_90) * SPEED ;
	}
	if (mlx_is_key_down(data->mlx, MLX_KEY_ESCAPE))
	{
		printf("exit\n");
		exit(EXIT_SUCCESS);
	}
	if (!collision_detected(data->map, next))
		data->player.coor = next;
}
// printf("x = %f, y = %f\n", data->player.coor.x, data->player.coor.y);

void	ft_loop(void *dataa)
{
	t_data *data;
	data = (t_data *) dataa;
	cast_rays(data);
	key(dataa);
}
