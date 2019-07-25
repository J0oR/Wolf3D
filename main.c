/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   main.c                                           .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: gruocco <marvin@le-101.fr>                 +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/10/23 13:20:15 by gruocco      #+#   ##    ##    #+#       */
/*   Updated: 2018/10/23 13:20:17 by gruocco     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "ft_include.h"

/**
 * The first 2 parameters are the 2D map colors.
 *
 * The camera plane must be perpendicular to the direction, the length can be changed.
 *
 * The ratio between the length of the direction and the camera plane sets the FOV.
 * Here the direction vector is a bit longer than the camera plane, so the FOV will be smaller than 90°:
 * 2 * atan(0.66/1.0)=66° (perfect for a first person shooter game).
 *
 * When rotating with the input keys, the values of dir and plane will change,
 * but they'll always remain perpendicular and keep the same length.
 */

void	param_filler(t_data *data)
{
	data->rgb[0] = 0x000000;
	data->rgb[1] = 0xc20000;
	data->planeX = 0;
	data->planeY = -0.66;
	data->dir_x = -1;
	data->dir_y = 0;
	data->pos_x = 22;
	data->pos_y = 22;
}

/**
 * Used to clean before ft_raycaster call, with:
 * // int x = -1;
 * //while (++x < win_w * win_h)
 * //	data->img.data[x] = 0x000000;
 */

void	ft_redraw(t_data *data)
{
	ft_raycaster(data);
	mlx_put_image_to_window(data->ptr, data->win, data->img.img_ptr, 0, 0);
	ft_2d_map_print(data);
	ft_instructions(data);
}

void	ft_map_reader(t_data *data, char **av)
{
	int fd;

	data->map = (int *)ft_memalloc(sizeof(int) * data->cols * data->rows);
	fd = open(av[1], O_RDONLY);
	ft_array_filler(fd, data);
	close(fd);
	ft_texture_maker(data);
	ft_redraw(data);
}

int		main(int ac, char **av)
{
	int			fd;
	t_data		data;

	param_filler(&data);
	fd = open(av[1], O_RDONLY);
	if (ft_checks(&data, ac, av, fd))
		return (0);
	close(fd);
	ft_map_reader(&data, av);
	ft_instructions(&data);
	mlx_hook(data.win, 2, 0, &ft_key_press, &data);
	mlx_hook(data.win, 17, 0, &ft_x_close, &data);
	mlx_loop(data.ptr);
	return (0);
}
