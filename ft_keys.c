/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_keys.c                                        .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: gruocco <marvin@le-101.fr>                 +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/10/24 10:07:45 by gruocco      #+#   ##    ##    #+#       */
/*   Updated: 2018/11/01 13:05:12 by gruocco     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "ft_include.h"

int		ft_check_sides_to_forward(t_data *data)
{
	double sidedx_x;
	double sidedx_y;
	double sidesx_x;
	double sidesx_y;
	double factor;

	factor = 1 / 3;
	sidedx_x = data->dir_y * data->speed * factor;
	sidedx_y = -data->dir_x * data->speed * factor;
	sidesx_x = -data->dir_y * data->speed * factor;
	sidesx_y = data->dir_x * data->speed * factor;

	/*if ((data->map[(int)(data->pos_x + sidedx_x) +
	(int)(data->pos_y + sidedx_y) * data->cols] == 0) &&
	(data->map[(int)(data->pos_x + sidesx_x) +
	(int)(data->pos_y + sidesx_y) * data->cols] == 0))*/
	if ((data->map[(int)(data->pos_x + sidedx_x) + ((int) data->pos_y) * data->cols] == 0) &&
		(data->map[(int)(data->pos_x) + (int)(data->pos_y + sidedx_y) * data->cols] == 0) &&
		(data->map[(int)(data->pos_x + sidesx_x) + ((int) data->pos_y) * data->cols] == 0) &&
		(data->map[(int)(data->pos_x) + (int)(data->pos_y + sidesx_y) * data->cols] == 0))
		return(1);
	return(0);
}


/**
* If the up arrow is pressed, the player will move forward: add dir_x to pos_x, and dir_y to pos_y.
* This assumes that dir_x and dir_y are normalized vectors (their length is 1), but they were initially
* set like this, so it's ok.
*
* There's also a simple collision detection built in: if the new position will be inside a wall, you won't move.
* This can be improved however, for example by checking if a circle around the player won't go inside the wall
* instead of just a single point.
*
* The same is done if you press the down arrow, but then the direction is subtracted instead.
*
* To rotate, if the left or right arrow is pressed, both the direction vector and plane vector are rotated by
* using the formulas of multiplication with the rotation matrix (and over the angle rotSpeed).
*/

int     ft_move_straight(int keycode, t_data *data)
{

    double front_x;
    double front_y;

	front_x = keycode == 126 ? data->dir_x + 0.05 : -data->dir_x * data->speed;
	front_y = keycode == 126 ? data->dir_y + 0.05 : -data->dir_y * data->speed;

	/*if ((data->map[(int) (data->pos_x + front_x) + ((int) (data->pos_y)) * data->cols] == 0) &&
	(data->map[(int) (data->pos_x) + ((int) (data->pos_y + front_y)) * data->cols] == 0) &&
	ft_check_sides_to_forward(data))*/
	if ((data->map[(int) (data->pos_x + front_x) + ((int) (data->pos_y + front_y)) * data->cols] == 0) &&
	ft_check_sides_to_forward(data))
	{
		data->pos_x += front_x / 3;
		data->pos_y += front_y / 3;
		ft_redraw(data);
	}
	return (1);
}

int     ft_move_side (int keycode, t_data *data)
{
    double side_x;
    double side_y;

    side_x = keycode == 123 ? data->dir_y * data->speed : - data->dir_y * data->speed;
    side_y = keycode == 123 ? - data->dir_x * data->speed : data->dir_x * data->speed;
	/*if (data->map[(int)(data->pos_x + side_x) + (int)(data->pos_y + side_y) * data->cols] == 0)*/
	if ((data->map[(int)(data->pos_x + side_x) + ((int) data->pos_y) * data->cols] == 0) &&
            (data->map[(int)(data->pos_x) + (int)(data->pos_y + side_y) * data->cols] == 0))
    {
        data->pos_x += side_x / 2;
        data->pos_y += side_y / 2;
        ft_redraw(data);
    }
    return 1;
}

/**
* both camera direction and camera plane must be rotated
*/
int     ft_rotate(int keycode, t_data *data)
{
    double cos_speed;
    double sin_speed;
    double olddir_x;
    double oldPlaneX;

    cos_speed = keycode == 2 ?
                cos(-data->rotSpeed) :
                cos(data->rotSpeed);
    sin_speed = keycode == 0 ?
                sin(-data->rotSpeed) :
                sin(data->rotSpeed);

	data->sin_speed = sin_speed;
    olddir_x = data->dir_x;
    data->dir_x = data->dir_x * cos_speed - data->dir_y * sin_speed;
    data->dir_y = olddir_x * sin_speed + data->dir_y * cos_speed;
    oldPlaneX = data->planeX;
    data->planeX = data->planeX * cos_speed - data->planeY * sin_speed;
    data->planeY = oldPlaneX * sin_speed + data->planeY * cos_speed;
    ft_redraw(data);
    return (1);
}

int		ft_key_press(int keycode, t_data *data)
{
	if (keycode == 0 || keycode == 2)
        ft_rotate(keycode, data);
    else if (keycode == 126 || keycode == 125)
        ft_move_straight(keycode, data);
    else if(keycode == 123 || keycode == 124)
        ft_move_side(keycode, data);
    else if (keycode == 53)
    {
        mlx_destroy_image(data->ptr, data->img.img_ptr);
        mlx_destroy_window(data->ptr, data->win);
		free(data->map);
		exit(0);
    }
    return (1);
}
