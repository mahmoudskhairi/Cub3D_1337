/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_player.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmarzouk <rmarzouk@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/13 13:38:51 by rmarzouk          #+#    #+#             */
/*   Updated: 2024/11/20 16:38:09 by rmarzouk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "game.h"

void	draw_player(t_data *data, t_coor coor, mlx_image_t *img)
{
	int	i;
	int	j;

	i = 0;
	while( i < 4)
	{
		j = 0;
		while (j < 4)
		{
			my_mlx_put_pixel(data, img, (t_coor){coor.x + i - 2, coor.y + j - 2}, get_rgba(96, 86, 120, 255));
			dda(data, coor , (t_coor) {coor.x + cos(data->player.angle) * 10, coor.y + sin(data->player.angle) * 10}, get_rgba(96, 86, 120, 255), data->ft_3D);
			j++;
		}
		i++;
	}
}
