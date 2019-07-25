/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_checks.c                                      .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: gruocco <marvin@le-101.fr>                 +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/10/23 13:26:22 by gruocco      #+#   ##    ##    #+#       */
/*   Updated: 2018/10/23 13:26:24 by gruocco     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "ft_include.h"

void		ft_array_filler(int fd, t_data *data)
{
	char		*line;

	data->i = -1;
	while (get_next_line(fd, &line) && ++data->i < data->rows)
	{
		data->j = -1;
		data->flag = 0;
		while (++data->j < data->cols && line[data->j])
		{
			if (line[data->j] != ' ')
			{
				data->map[data->j + data->i * data->cols] = 1;
				data->flag = 1;
			}
			else
				data->map[data->j + data->i * data->cols] =
						data->flag == 1 ? 0 : 2;
		}
		while (data->j < data->cols)
			data->map[data->j++ + data->i * data->cols] = 2;
	}
	free(line);
}

static int	ft_columns_counter(char *s, char split)
{
	int	cols_num;
	int	i;

	cols_num = 0;
	i = 0;
	while (s[i])
	{
		while (s[i] == split && s[i++])
			cols_num++;
		if (s[i])
			cols_num++;
		while (s[i] != split && s[i])
			i++;
	}
	return (cols_num);
}

int			ft_map_size_reader(int fd, t_data *data, int len)
{
	char	*line;
	int		rows;
	int		cols;
	int		flag;

	rows = 0;
	flag = 0;
	while (get_next_line(fd, &line))
	{
		if (flag++ == 0)
			len = ft_columns_counter(line, ' ');
		cols = ft_columns_counter(line, ' ');
		if (len < cols)
			len = cols;
		rows++;
		free(line);
	}
	data->rows = rows;
	data->cols = len;
	return (1);
}

int			ft_checks(t_data *data, int ac, char **av, int fd)
{
	if (ac != 2)
	{
		ft_putendl("Usage : ./wolf3d <filename>");
		return (1);
	}
	if (fd < 0)
	{
		ft_putstr("No file ");
		ft_putendl(av[1]);
		return (1);
	}
	if (!ft_map_size_reader(fd, data, 0))
	{
		ft_putendl("Invalid map. Exiting.");
		return (1);
	}
	if (!(data->ptr = mlx_init())
	|| !(data->win = mlx_new_window(data->ptr, win_w, win_h, "wolf3d"))
	|| !(data->img.img_ptr = mlx_new_image(data->ptr, win_w, win_h))
	|| !(data->img.data = (int*)mlx_get_data_addr(data->img.img_ptr,
			&data->img.bpp, &data->img.size_l, &data->img.endian)))
		return (1);
	return (0);
}
