/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_floor_ceiling.c                               .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: gruocco <marvin@le-101.fr>                 +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/01/13 18:41:07 by gruocco      #+#   ##    ##    #+#       */
/*   Updated: 2019/01/13 18:41:11 by gruocco     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "ft_include.h"

/*
 ** The loop draws the floor from draw_end to the screen bottom. It calculates
 ** the current distance, out of:
*/
/*
 ** weight, exact position of the floor and texel coordinate on the texture.
 ** With this infos, both a floor and a ceiling pixel can be drawn.
*/
/*
 ** The floor is made darker. To resize floor and ceiling textures (i.e. to make
 ** them 4 times larger), modify the tex_x/y part of the code.
*/
/*
 ** The last 2 lines: floor and ceiling (symmetrical).
*/

void	ft_drawer(int x, int y, t_data *data)
{
	while (++y < win_h)
	{
		data->current_dist = win_h / (2.0 * y - win_h);
		data->weight = (data->current_dist - data->dist_player) /
				(data->wall_dist - data->dist_player);
		data->current_floor_x = data->weight * data->floor_x_wall +
				(1.0 - data->weight) * data->pos_x;
		data->current_floor_y = data->weight * data->floor_y_wall +
				(1.0 - data->weight) * data->pos_y;
		data->tex_x = (int)(data->current_floor_x * text_w / 4) % text_w;
		data->tex_y = (int)(data->current_floor_y * text_h / 4) % text_h;
		data->img.data[x + y * win_w] = (data->text[4][text_w * data->tex_y +
												data->tex_x] >> 1) & 8355711;
		data->img.data[(win_h - y) * win_w + x] =
				data->text[5][text_w * data->tex_y + data->tex_x];
	}
}

/*
 ** The position of the floor right in front of the wall is calculated.
 ** There are 4 cases: a north, east, south or west side of a wall could be hit.
*/
/*
 ** After this position and the distances are set, it starts loop in the y dir
 ** that goes from the pixel below the wall until the bottom of the screen.
*/
/*
 ** Note: y becomes < 0 when the integer overflows
*/

void	ft_floor_ceiling(t_data *data, int x)
{
	int y;

	if (data->side == 0)
	{
		data->floor_x_wall = data->raydir_x > 0 ? data->mapX : data->mapX + 1.0;
		data->floor_y_wall = data->mapY + data->wall_x;
	}
	else if (data->side == 1)
	{
		data->floor_x_wall = data->mapX + data->wall_x;
		data->floor_y_wall = data->raydir_y > 0 ? data->mapY : data->mapY + 1.0;
	}
	data->dist_player = 0.0;
	y = data->draw_end > 0 ? data->draw_end : win_h;
	ft_drawer(x, y, data);
}
