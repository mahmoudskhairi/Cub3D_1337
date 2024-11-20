/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouvements.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmarzouk <rmarzouk@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/15 10:06:49 by rmarzouk          #+#    #+#             */
/*   Updated: 2024/11/20 15:39:42 by rmarzouk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "game.h"

int	collision_detected(t_map map, t_coor p_coor)
{
	t_coor coor = p_coor;
	coor.y = p_coor.y - 2;
	while (coor.y < p_coor.y + 2)
	{
		coor.x = p_coor.x - 2;
		while (coor.x < p_coor.x + 2)
		{
			if (map.grid[(int)(coor.y / TILE_SIZE)] 
			&& map.grid[(int)(coor.y / TILE_SIZE)][(int)(coor.x / TILE_SIZE)] 
			&& map.grid[(int)(coor.y / TILE_SIZE)][(int)(coor.x / TILE_SIZE)] == '1')
			return (1);
			coor.x++;	
		}
		coor.y++;	
	}
	return (0);
}

void	key(t_data *data)
{
	t_coor next;
	next = data->player.coor;
    // mlx_get_mouse_pos(data->mlx, &data->mouse_position.x, &data->mouse_position.y);
    // if (!(data->mouse_position.x >=0 && data->mouse_position.x <= WIDTH) || !(data->mouse_position.y >=0 && data->mouse_position.y <= HEIGHT))
    //     mlx_set_mouse_pos(data->mlx, WIDTH / 2, HEIGHT / 2);
	if ((mlx_is_key_down(data->mlx, MLX_KEY_RIGHT) || data->tmp_p_mouse <= data->mouse_position.x - 10))//(data->mouse_position.x >=0 && data->mouse_position.x <= WIDTH) && (data->mouse_position.y >=0 && data->mouse_position.y <= HEIGHT) 
	{
		data->player.angle = ft_normalizer(data->player.angle + DEGREE);
        // data->tmp_p_mouse = data->mouse_position.x;
	}
	if ((mlx_is_key_down(data->mlx, MLX_KEY_LEFT) || data->tmp_p_mouse >= data->mouse_position.x + 10))//(data->mouse_position.x >=0 && data->mouse_position.x <= WIDTH) && (data->mouse_position.y >=0 && data->mouse_position.y <= HEIGHT)
	{
		data->player.angle = ft_normalizer(data->player.angle - DEGREE);
        // data->tmp_p_mouse = data->mouse_position.x;
	}
	if (mlx_is_key_down(data->mlx, MLX_KEY_W) || mlx_is_key_down(data->mlx, MLX_KEY_UP))
	{
		
		// up(&next, data->player.angle);
		next.x += cos(data->player.angle) * SPEED;
		next.y += sin(data->player.angle) * SPEED;
	}
	if (mlx_is_key_down(data->mlx, MLX_KEY_S) || mlx_is_key_down(data->mlx, MLX_KEY_DOWN))
	{
		next.x -= cos(data->player.angle) * SPEED;
		next.y -= sin(data->player.angle) * SPEED;
	}
	if (mlx_is_key_down(data->mlx, MLX_KEY_A))
	{
		next.x += cos(data->player.angle - DEGREE_90) * SPEED;
		next.y += sin(data->player.angle - DEGREE_90) * SPEED;
	}
	if (mlx_is_key_down(data->mlx, MLX_KEY_D))
	{
		next.x += cos(data->player.angle + DEGREE_90) * SPEED;
		next.y += sin(data->player.angle + DEGREE_90) * SPEED;
	}
	if (mlx_is_key_down(data->mlx, MLX_KEY_ESCAPE))
	{
		printf("exit\n");
		exit(EXIT_SUCCESS);
	}
	if (!collision_detected(data->map, next))
		data->player.coor = next;
}

void	ft_loop(void *dataa)
{
	t_data *data;
	data = (t_data *) dataa;
	cast_rays(data);
	key(dataa);
	// mouse hook;
}
