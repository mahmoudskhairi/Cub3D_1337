/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   projection_3D.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmarzouk <rmarzouk@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/15 10:16:43 by rmarzouk          #+#    #+#             */
/*   Updated: 2024/11/20 16:43:23 by rmarzouk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "game.h"

void	dda(t_data *data, t_coor a, t_coor b, int color, mlx_image_t *img)
{
	int step;
	double dx;
	double dy;

	double xinc;
	double yinc;

	dy = b.y - a.y;
	dx = b.x - a.x;
	if (fabs(dx) > fabs(dy))
		step = fabs(dx);
	else
		step = fabs(dy);
	xinc = dx / step;
	yinc = dy / step;
	int i = 0;
	while (i <= step)
	{
		my_mlx_put_pixel(data, img,(t_coor){a.x , a.y}, color);
		a.x += xinc;
		a.y += yinc;
		i++;
	}
}

t_coor	first_v_inter(double angle, t_coor player)
{
	t_coor first_v;

	if (angle >= M_PI / 2 && angle <= 1.5 * M_PI)//left
		first_v.x = (int)(player.x / TILE_SIZE) * TILE_SIZE - 0.00000001;
	else if (angle >= 1.5 * M_PI || angle <= M_PI / 2)// right
		first_v.x = (int)(player.x / TILE_SIZE) * TILE_SIZE + TILE_SIZE;
	
	first_v.y = player.y + tan(angle) * (first_v.x - player.x);
	return (first_v);
}

t_coor	first_h_inter(double angle, t_coor player)
{
	t_coor first_h;
	
	angle = ft_normalizer(angle);
	if (angle >= 0 && angle <= M_PI)// down
		first_h.y = floor(player.y / TILE_SIZE) * TILE_SIZE + TILE_SIZE;
	else if (angle > M_PI && angle < 2 * M_PI) // up
		first_h.y = floor(player.y / TILE_SIZE) * TILE_SIZE - 0.00000001;
	first_h.x = (first_h.y - player.y) / tan(angle) + player.x;
	return (first_h);
}

t_coor h_wall_detect(t_map map, t_coor hit, double angle)
{
	int i;
	int	x;
	int y;

	angle = ft_normalizer(angle);
	i = 0;
	while (i <= map.heigth)
	{
		x = (int)(hit.x / TILE_SIZE);
		y = (int)(hit.y / TILE_SIZE);
		if (x >= 0 && y >= 0 && x < map.width && y < map.heigth && map.grid[y][x] == '1')
			return (hit);
		if (angle >= 0 && angle < M_PI)// down
		{
			hit.y += TILE_SIZE;
			hit.x += (TILE_SIZE) / tan(angle);
		}
		else // up
		{
			hit.y -= TILE_SIZE;
			hit.x -= TILE_SIZE / tan(angle);
		}
		i++;
	}
	return (hit);
}

t_coor v_wall_detect(t_map map, t_coor hit, double angle)
{
	int i;
	int	x;
	int y;

	i = 0;
	while (i <= map.width)
	{
		x = (int)(hit.x / TILE_SIZE);
		y = (int)(hit.y / TILE_SIZE);
		if (x >= 0 && x < map.width && y >= 0 && y < map.heigth && map.grid[y][x] == '1')
			return (hit);
		if (angle > M_PI / 2 && angle < 1.5 * M_PI) // left
		{
			hit.x -= TILE_SIZE;
			hit.y -= TILE_SIZE * tan(angle);
		}
		else //if (angle > 1.5 * M_PI || angle < M_PI / 2) // right
		{
			hit.x += TILE_SIZE;
			hit.y += TILE_SIZE * tan(angle);
		}
		i++;
	}
	return (hit);
}

t_coor	ft_compare(t_coor player, t_coor h, t_coor v, t_ray *ray)
{
	double PH;
	double PV;


	PH = sqrt(pow(h.y - player.y, 2)+ pow(h.x - player.x, 2));
	PV = sqrt(pow(v.y - player.y, 2)+ pow(v.x - player.x, 2));

	if (PV < PH)
	{
		ray->distance = PV;
		ray->flag = 'v';
		return (v);
	}
	else
	{
		ray->distance = PH;
		ray->flag = 'h';
		return (h);
	}
}
int gett_rgba(uint8_t *color)
{
    return (color[0] << 24 | color[1] << 16 | color[2] << 8 | color[3]);
}

void textures(t_data *data,t_ray *ray, mlx_image_t *img, int flag)
{
	double x_texture;
	double y_texture;
	int i;
	int color;

	// x_of_texture = 0;
	// x_texture = (ray->Wall_hit.y / TILE_SIZE - floor(ray->Wall_hit.y / TILE_SIZE)) * data->img1->height;
	i = ray->top;
	if (ray->flag == 'h')
		x_texture = (ray->Wall_hit.x / TILE_SIZE - floor(ray->Wall_hit.x / TILE_SIZE)) * img->width;
	else if (ray->flag == 'v')
		x_texture = (ray->Wall_hit.y / TILE_SIZE - floor(ray->Wall_hit.y / TILE_SIZE)) * img->width;
	while(i < ray->bottom)
	{
		y_texture = ((i - ray->top) / (ray->bottom - ray->top)) * img->height;
		// printf("x-->%d\n", img->width);
		// printf("y-->%f\n", y_texture);
		if (i >= 0 && i < HEIGHT)
		{
			if ((int)y_texture * img->width + (int)x_texture <= img->height * img->width)
			{
                if (!flag)
                {
                        color = gett_rgba(&img->pixels[(((int)y_texture * img->width + (img->width - (int)x_texture))) * 4]);
                }
                else
                    color = gett_rgba(&img->pixels[(((int)y_texture * img->width + (int)x_texture)) * 4]);
                    
				mlx_put_pixel(data->ft_3D, data->x_projection  , i, color);
			}
			// mlx_put_pixel(data->ft_3D,data->x_projection , i, get_rgba(255,255,255,255));
		}
		i++;
	}
}
void	draw_columns(t_data *data, t_ray *ray, double angle)
{
    double	projection_column;
	double	projection_distance;
	ray->distance *= cos(data->player.angle - angle);
	projection_distance = WIDTH / 2 * tan(FOV / 2);
	projection_column = ((TILE_SIZE * projection_distance) / ray->distance) * 2;
	ray->top = (HEIGHT / 2) - (projection_column / 2);
	ray->bottom = (HEIGHT / 2) + (projection_column / 2);
    // if(mlx_is_key_down(data->mlx, MLX_KEY_DOWN))// wach 3atmsah hadxi ??
    // {
    //     ray->top = 0;
    //     ray->bottom = HEIGHT / 2;
    // }
    // if(mlx_is_key_down(data->mlx, MLX_KEY_UP))
    // {
    //     ray->top = HEIGHT / 2;
    //     ray->bottom = HEIGHT;
    // }
    // if (mlx_is_key_down(data->mlx, MLX_KEY_DOWN))
    // {
    //     printf("hello\n");
    //     while(i <= N_RAYS)
    //     {
    //         ray->top-= 10;
    //         ray->bottom+= 10;
    //         i++;
    //     }
    // }
    // else if (mlx_is_key_down(data->mlx, MLX_KEY_UP))
    // {
    //     printf("hello\n");
    //     while(i <= N_RAYS)
    //     {
    //         ray->top+= 10;
    //         ray->bottom-= 10;
    //         i++;
    //     }
    // }
	if ((sin(angle) <= 0 && ray->flag == 'h'))//----->top
		textures(data, ray, data->img1, 1);
	if ((sin(angle) >= 0 && ray->flag == 'h'))//buttom
		textures(data, ray, data->img2, 0);
	if ((cos(angle) >= 0 && ray->flag == 'v'))// ----->right
		textures(data, ray, data->img3, 1);
	if (cos(angle) <= 0  && ray->flag == 'v')// ----->left
		textures(data, ray, data->img4, 0);
}



void	projection_3D(t_data *data)
{
	t_coor first_h;
	t_coor first_v;
	data->rays = malloc(N_RAYS * sizeof(t_ray));
	if (!data->rays)
	{
		printf ("malloc failed");
		return;
	}
	double angle = data->player.angle - FOV / 2;
	int i = 0;
	data->x_projection = 0;
	while (i < N_RAYS)// casting rays depened of player angle
	{
		first_h = first_h_inter(angle, data->player.coor);
		first_v = first_v_inter(angle, data->player.coor);
		t_coor hit_h = h_wall_detect(data->map, first_h, angle);
		t_coor hit_v = v_wall_detect(data->map, first_v, angle);

		data->rays[i].Wall_hit = ft_compare(data->player.coor, hit_h, hit_v, &(data->rays[i]));
		// dda(data, data->player.coor, data->rays[i].Wall_hit, get_rgba(255, 10, 10, 255), data->ft_3D);// cast ray
		draw_columns(data, &data->rays[i], angle);
		data->x_projection++;
		angle += RAY_ANGLE_INC;
		i++;
	}
	free(data->rays);
}


