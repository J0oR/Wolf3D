/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_tools.c                                       .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: gruocco <marvin@le-101.fr>                 +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/11/22 12:15:40 by gruocco      #+#   ##    ##    #+#       */
/*   Updated: 2018/11/22 12:15:43 by gruocco     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "ft_include.h"

void ft_calc_pos_print(t_data *data)
{
	int y;
	int x;

	y = -1;
	while (++y < mult)
	{
		x = -1;
		while (++x < mult)
			data->img.data[((int) data->pos_x + mult * (int) data->pos_x + x) +
			((int) data->pos_y + mult * (int) data->pos_y + y) * win_w] = 0xfcfeff;
	}
	data->img.data[((int)data->dir_x) + ((int)data->dir_y) * win_w] = 0xfcfeff;
	mlx_put_image_to_window(data->ptr, data->win, data->img.img_ptr, 0, 0);
}

void ft_2d_map_print(t_data *data)
{
    int point;
    int x;
	int y;
	int i;
	int j;

    i = -1;
    while (++i < data->rows)
    {
		j = -1;
        while (++j < data->cols)
        {
            if ((point = data->map[j + (i * data->cols)]) != 2)
			{
				y = -1;
				while (++y <= mult)
				{
					x = -1;
					while (++x <= mult)
						data->img.data[(j + mult * j + x) +
						(i + mult * i + y) * win_w] = data->rgb[point];
				}
			}
       }
    }
    ft_calc_pos_print(data);
}

void	ft_instructions(t_data *data)
{
	mlx_string_put(data->ptr, data->win, win_w - 250, 0,
				   0xc20000, "----------------------");
	mlx_string_put(data->ptr, data->win, win_w - 250, 20,
				   0xc20000, "| Move    : arrows   |");
	mlx_string_put(data->ptr, data->win, win_w - 250, 40,
				   0xc20000, "| Rotate  : A D      |");
	mlx_string_put(data->ptr, data->win, win_w - 250, 60,
				   0xc20000, "| ESC     : Exit     |");
	mlx_string_put(data->ptr, data->win, win_w - 250, 80,
				   0xc20000, "----------------------");
}

int		ft_x_close(t_data *data)
{
	mlx_destroy_image(data->ptr, data->img.img_ptr);
	mlx_destroy_window(data->ptr, data->win);
	free(data->map);
	exit(0);
}

void 	ft_get_speed(t_data *data)
{
	/**
	 * After the raycasting loop is done:
	 * - the time of the current and the previous frame are calculated
	 * - the FPS (frames per second) can be calculated (1.0 / frameTime)
	 *
	 * The speed modifiers use frameTime, and a constant value, to determinate the speed of the moving and rotating
	 * of the input keys.
	 * Thanks to using the frameTime, we can make sure that the moving and rotating speed is independent of the
	 * processor speed.
	 */
	data->time = (double)clock();
	data->frameTime = (data->time - data->oldTime) / CLOCKS_PER_SEC;
	data->speed = data->frameTime * 15.0;       //the constant value is in squares/second
	data->rotSpeed = data->frameTime * 3.0;     //the constant value is in radians/second
}

/*void print_stuff (t_data *data)
{

    printf ("MAP\n");
    printf("rows = %i\n", data->rows);
    printf("cols = %i\n", data->cols);
    printf("pos_x = %f\n", data->pos_x);
    printf("pos_y = %f\n", data->pos_y);
    printf("mapX = %d\n", data->mapX);
    printf("mapY = %d\n\n", data->mapY);

    printf ("RAY\n");
    printf("planeX = %f\n", data->planeX);
    printf("planeY = %f\n", data->planeY);
    printf("step_x = %d\n", data->step_x);
    printf("step_y = %d\n", data->step_y);
    printf("dir_x = %f\n", data->dir_x);
    printf("dir_y = %f\n", data->dir_y);

    printf("\ncameraX = %f\n", data->cameraX);
    printf("raydir_x = %f\n", data->raydir_x);
    printf("raydir_y = %f\n", data->raydir_y);
    printf("side = %i\n", data->side);

    printf("\nside_dist_x = %f\n", data->side_dist_x);
    printf("side_dist_y = %f\n", data->side_dist_y);
    printf("delta_dist_x = %f\n", data->delta_dist_x);
    printf("delta_dist_y = %f\n", data->delta_dist_y);
    printf("wall_dist = %f\n", data->wall_dist);
    printf("hit = %i\n", data->hit);

    printf ("\nDATA\n");
    printf("lineHeight = %d\n\n\n", data->lineHeight);

    //printf ("MAP_STRING\n");
    //ft_2D_map_print(data);
}*/
