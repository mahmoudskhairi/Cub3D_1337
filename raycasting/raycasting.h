/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmarzouk <rmarzouk@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/13 13:31:46 by rmarzouk          #+#    #+#             */
/*   Updated: 2024/10/15 10:24:38 by rmarzouk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RAYCASTING_H
#define RAYCASTING_H


#include "../cub3D.h"

void	init_mlx_elements(t_data *data);
void	my_mlx_put_pixel(t_data *data, t_coor coor, u_int32_t color);
int		get_rgba(int r, int g, int b, int a);
void	draw_box(t_data *data, int	x, int y, char c);

void	keyhooks(mlx_key_data_t	keydata, void *dataa);
double	ft_normalizer(double angle);
void	ft_dda(t_data *data);
#endif