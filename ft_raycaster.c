/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_raycaster.c                                   .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: gruocco <marvin@le-101.fr>                 +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/10/25 13:17:32 by gruocco      #+#   ##    ##    #+#       */
/*   Updated: 2018/10/25 13:17:37 by gruocco     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "ft_include.h"

void 	ft_wall_typeAndCoord(t_data *data)
{
	/**
	 * The variable texNum is the value of the current map square minus 1, the reason is that there exists a texture 0,
	 * but map tile 0 has no texture since it represents an empty space.
	 * To be able to use texture 0 anyway, substract 1 so that map tiles with value 1 will give texture 0, etc...
	 *
	 * The value wall_x represents the exact value where the wall was hit, not just the integer coordinates of the wall.
	 * This is required to know which x-coordinate of the texture we have to use.
	 * This is calculated by first calculating the exact x or y coordinate in the world, and then substracting the
	 * integer value of the wall off it.
	 *
	 * Note that even if it's called wall_x, it's actually an y-coordinate of the wall if side==1, but it's always
	 * the x-coordinate of the texture.
	 *
	 * Finally, texX is the x-coordinate of the texture, and this is calculated out of wall_x.
	 */
	/**
	 * calculate value of wall_x, where exactly the wall was hit
	 **/
	if (data->side == 0)
		data->wall_x = data->pos_y + data->wall_dist * data->raydir_y;
	else
		data->wall_x = data->pos_x + data->wall_dist * data->raydir_x;
	data->wall_x -= floor(data->wall_x);

	/**
	 * x coordinate on the texture
	 **/
	data->tex_x = (int)(data->wall_x * (double)text_w);
	if(data->side == 0 && data->raydir_x > 0)
		data->tex_x = text_w - data->tex_x - 1;
	if(data->side == 1 && data->raydir_y < 0)
		data->tex_x = text_w - data->tex_x - 1;

	if (data->side == 0)
		data->text_n = data->raydir_x < 0 ? 0 : 1;
	else
		data->text_n = data->raydir_y < 0 ? 2 : 3;

}

void 	ft_stripe_height(t_data *data)
{
	/**
	 * After the DDA, we have to calculate the distance ray-wall, to calculate how high the wall has to be drawn.
	 * We don't use the Euclidean distance however, but instead only the distance perpendicular to the camera
	 * plane (projected on the camera direction), to avoid the fisheye effect.
	 *
	 * This part of the code isn't "fisheye correction", such a correction isn't needed for the way of raycasting
	 * used here, the fisheye effect is simply avoided by the way the distance is calculated here.
	 * It's even easier to calculate this perpendicular distance than the real distance, we don't even need to
	 * know the exact location where the wall was hit.
	 *
	 * First of all, (1-step_x)/2 is 1 if step_x = -1 and 0 if step_x is +1 :
	 * this is needed because we need to add 1 to the length when raydir_x < 0, for the same reason why 1.0 was added to
	 * the initial value of side_dist_x in one case but not in the other.
	 *
	 * The distance is then calculated as follows:
	 * - if an x-side is hit, mapX-pos_x+(1-step_x)/2) is the number of squares the ray has crossed in X direction
	 * - if the ray is perpendicular on the X side, this is the correct value already, but because the direction
	 * of the ray is different most of the times, its real perpendicular distance will be larger, so we divide it
	 * through the X coordinate of the rayDir vector.
	 *
	 * Something similar is done in case an y-side is hit.
	 * The calculated distance is never negative, since mapX-pos_x will be negative only if raydir_x is negative,
	 * and we divide these two through each other.
	 */
	if (data->side == 0)
		data->wall_dist = (data->mapX - data->pos_x + (1 - data->step_x) / 2) / data->raydir_x;
	else
		data->wall_dist = (data->mapY - data->pos_y + (1 - data->step_y) / 2) / data->raydir_y;
	/**
	 * Calculate the height of the line that has to be drawn on screen:
	 * the inverse of wall_dist, multiplied by h (the height in pixels of the screen), to bring it to pixel coordinates.
	 *
	 * It can be multiplied with another value, for example 2*h, to set the walls to be higher or lower.
	 * The value of h will make the walls look like cubes with equal height, width and depth, while large values
	 * will create higher boxes (depending on the monitor).
	 */
	data->line_h = (int) (win_h / data->wall_dist);
	/**
	 * Lowest and highest pixel to fill in current stripe: the start and end position of where we
	 * should really draw are calculated out of the lineHeight (the height of the vertical line to drawn),
	 */
	data->draw_start = -data->line_h / 2 + win_h / 2;
	data->draw_end = data->line_h / 2 + win_h / 2;
	/**
	 * The center of the wall should be at the center of the screen, and if these points lie outside the screen,
	 * they're capped to 0 or h-1.
	 */
	if (data->draw_start < 0)
		data->draw_start = 0;
	if (data->draw_end >= win_h)
		data->draw_end = win_h - 1;
	ft_wall_typeAndCoord(data);

}

void 	ft_hit_wall(t_data *data)
{
	/**
	 * Determines when the next loop may be ended: was there a wall hit?
	 **/
	data->hit = 0;
	/**
	 * The actual DDA starts: a loop that increments the ray with 1 square every time, until a wall is hit.
	 * Each time, either it jumps a square in the x-direction (step_x) or in the y-direction (step_y).
	 * If an x-side was hit, side is set to 0, if an y-side was hit, side will be 1.
	 **/
	while (data->hit == 0)
	{
		/**
		 * If the ray's direction would be the x-direction, the loop will only have to jump a square in the x-direction
		 * everytime, because the ray will never change its y-direction.
		 *
		 * If the ray is a bit inclined to the y-direction, then every so many jumps in the x-direction, the ray
		 * will have to jump one square in the y-direction.
		 *
		 * If the ray is exactly the y-direction, it never has to jump in the x-direction, etc...
		 *
		 * side_dist_x and side_dist_y get incremented with delta_dist_x with every jump in their direction, and mapX
		 * and mapY get incremented with step_x and step_y respectively.
		 */
		if (data->side_dist_x < data->side_dist_y)
		{
			data->side_dist_x += data->delta_dist_x;
			data->mapX += data->step_x;
			data->side = 0;
		}
		else
		{
			data->side_dist_y += data->delta_dist_y;
			data->mapY += data->step_y;
			data->side = 1;
		}
		/**
		 * When the ray hits a wall, the loop ends, and then we'll know whether an x-side or y-side of a wall
		 * was hit in the variable "side", and what wall was hit with mapX and mapY.
		 * We don't know yet where the wall was hit however.
		 */
		data->point = data->map[data->mapX + data->mapY * data->cols];
		if (data->point > 0)
			data->hit = 1;
	}
}

void 	ft_calculator(t_data *data, int x)
{
	/**
	 * CameraX is the x-coordinate on the camera plane that the current x-coordinate of the screen represents, done this way so that:
	 * - the right side of the screen gets coordinate 1
	 * - the center of the screen gets coordinate 0,
	 * - the left side of the screen gets coordinate -1.
	 */
	data->camera_x = 2 * x / (double) win_w - 1;
	/**
	 * The ray's direction can be calculated as: direction vector + part of the plane vector
	 * Since vectors are added by adding their x and their y, this has to be done both for the x and y coordinate.
	 */
	data->raydir_x = data->dir_x + data->planeX * data->camera_x;
	data->raydir_y = data->dir_y + data->planeY * data->camera_x;
	/**
	 * The ray starts at the position of the player (pos_x, pos_y): a floating point number that contains both info about
	 * in which map square and where in that square we are.
	 *
	 * mapX and mapY are only the coordinates of that square: the current square of the map the ray is in.
	 **/
	data->mapX = (int) data->pos_x;
	data->mapY = (int) data->pos_y;
	/**
	 * delta_dist_x and delta_dist_y are the distance the ray has to travel between x-sides or y-sides.
	 *
	 * When deriving delta_dist_x or delta_dist_y with Pythagoras, you get a formula that can be simplified.
	 *
	 * delta_dist_x = sqrt(1 + (raydir_y * raydir_y) / (raydir_x * raydir_x)) ==> abs(1 / raydir_x)
	 * delta_dist_y = sqrt(1 + (raydir_x * raydir_x) / (raydir_y * raydir_y)) ==> abs(1 / raydir_y)
	 */
	data->delta_dist_x = fabs(1 / data->raydir_x);
	data->delta_dist_y = fabs(1 / data->raydir_y);
	/**
	 * The DDA algorithm will always jump exactly 1 square each loop, either in the x- or in the y-direction.
	 *
	 * If it has to go in the negative/positive x/y-direction, it will depend on the direction of the ray.
	 *
	 * This fact will be stored in step_x and step_y: always either -1 or +1.
	 *
	 * Now, before the actual DDA can start, step_x, step_y and the initial side_dist_x and side_dist_y have to be calculated.
	 *
	 * If the ray direction has a negative x-component, step_x is -1.
	 * If the ray direction has a positive x-component it's +1.
	 * If the x-component is 0, it doesn't matter what value step_x has since it'll then be unused.
	 *
	 * The same goes for the y-component.
	 */
	data->step_x = data->raydir_x < 0 ? -1 : 1;
	data->step_y = data->raydir_y < 0 ? -1 : 1;
	/**
	 * side_dist_x and side_dist_y are initially the distance the ray has to travel from its start position to the
	 * first x-side and the first y-side.
	 *
	 * Later, their meaning will slightly change: length of ray from current position to next x or y-side.
	 *
	 * If the ray direction has a negative x-component, side_dist_x is the distance from the ray starting position
	 * to the first side to the left.
	 * If it has a positive x-component, the first side to the right is used instead.
	 *
	 * The same goes for the y-component, but now with the first side above or below the position.
	 *
	 * For these values, the integer value mapX is used and the real position subtracted from it, and 1.0 is added
	 * in some of the cases depending if the side to the left or right, of the top or the bottom is used.
	 * Then you get the perpendicular distance to this side, so multiply it with delta_dist_x or delta_dist_y
	 * to get the real Euclidean distance.
	 */
	data->side_dist_x = data->raydir_x < 0 ?
					  (data->pos_x - data->mapX) * data->delta_dist_x :
					  (data->mapX + 1.0 - data->pos_x) * data->delta_dist_x;
	data->side_dist_y = data->raydir_y < 0 ?
					  (data->pos_y - data->mapY) * data->delta_dist_y :
					  (data->mapY + 1.0 - data->pos_y) * data->delta_dist_y;
}

void	ft_raycaster(t_data *data)
{
	int 		d_end;
	/*
	 int 		line_h;
	 int 		n;
	 */
	int 		x;
	int 		d;

	data->oldTime = (double)clock();
	x = -1;
	while (++x < win_w)
	{
		ft_calculator(data, x);
		ft_hit_wall(data);
		ft_stripe_height(data);
		d_end = data->draw_end;
		/*
		 * n = data->text_n;line_h = data->line_h;
		 * */
		while (d_end > data->draw_start)
		{
			/**
			 * Now that we know the x-coordinate of the texture, we know that this coordinate will remain the same, because we
			 * stay in the same vertical stripe of the screen.
			 * Now we need a loop in the y-direction to give each pixel of the vertical stripe the correct y-coordinate of the
			 * texture, called texY.
			 *
			 * The value of texY is calculated with integer math for more speed, but all the values that will be divided through
			 * a value are multiplied by 256 first, and afterwards it's divided through 256 again, for more precision.
			 * Otherwise some pretty ugly effects show up.
			 *
			 * The color of the pixel to be drawn is then gotten from texture[texNum][texX][texY]: the correct texel of the correct texture.
			 * */
			d = d_end * 256 - win_h * 128 + data->line_h * 128;  //256 and 128 factors to avoid floats
			data->tex_y = (d * text_h / data->line_h) / 256;
			data->color = data->text[data->text_n][text_h * data->tex_y + data->tex_x];
			/**
			* We make the color value darker if an y-side of the wall was hit, like there is a sort of lighting.
			* However, because the color value doesn't exist out of a separate R, G and B value, but these 3 bytes sticked
			* together in a single integer, a not so intuitive calculation is used.
			*
			* The color is made darker by dividing R, G and B through 2. Dividing a decimal number through 10, can be done by
			* removing the last digit (e.g. 300/10 is 30: the last zero is removed).
			* Similarly, dividing a binary number through 2, which is what is done here, is the same as removing the last bit.
			* This can be done by bitshifting it to the right with >>1.
			* But, here we're bitshifting a 24-bit integer (actually 32-bit, but the first 8 bits aren't used).
			* Because of this, the last bit of one byte will become the first bit of the next byte, and that screws up the
			* color values!
			* So after the bitshift, the first bit of every byte has to be set to zero, and that can be done by binary "AND-ing"
			* the value with the binary value 011111110111111101111111, which is 8355711 in decimal.
			*
			* So the result of this is indeed a darker color.
			* Finally, the current buffer pixel is set to this color, and we move on to the next y.
			*       for(int y = draw_start; y<draw_end; y++)
			*/
			if(data->side == 1)
				data->color = (data->color >> 1) & 8355711;
			data->img.data[x + d_end-- * win_w] = data->color;
		}
		ft_floor_ceiling(data, x);
	}
	ft_get_speed(data);
}

/**
 * multi-threaded
 * */
/*
void 	*ft_stripe(void *arg)
{
    t_thread	*stripe;
	int 		x;
	int 		n;
	int 		d_end;
	int 		line_h;

	stripe = (t_thread *)arg;
    pthread_mutex_lock(stripe->lock);


	ft_calculator(stripe->data, stripe->x);
    ft_hit_wall(stripe->data);
    ft_stripe_height(stripe->data);


	x = stripe->x;
	d_end = stripe->data->draw_end;
	n = stripe->data->text_switcher;
	line_h = stripe->data->lineHeight;
    while (d_end > stripe->data->draw_start)
	{
		int d = d_end * 256 - h_win * 128 + line_h * 128;  //256 and 128 factors to avoid floats
		stripe->data->tex_y = ((d * text_h) / line_h) / 256;
		stripe->data->color = stripe->data->text[n][text_h * stripe->data->tex_y + stripe->data->tex_x];

		if(stripe->data->side == 1)
			stripe->data->color = (stripe->data->color >> 1) & 8355711;
		stripe->data->img.data[x + d_end-- * w_win] = stripe->data->color;
	}
	ft_floor_ceiling(stripe->data, stripe->x);
    pthread_mutex_unlock(stripe->lock);
    return NULL;
}

void	ft_raycaster(t_data *data)
{

    int				    x;
    pthread_t		    threads_id[data->win_w];
    t_thread	        thread_arg[data->win_w];

    if (pthread_mutex_init(&data->lock, NULL) != 0)
    {
        printf("\n mutex init failed\n");
        return ;
    }

    x = -1;
    data->oldTime = (double)clock();

    while (++x < data->win_w)
    {
        thread_arg[x].x = x;
        thread_arg[x].data = data;
        thread_arg[x].lock = &data->lock;
    }

    x = -1;
    while (++x < data->win_w)
        pthread_create(&threads_id[x], NULL, ft_stripe, (void *)&thread_arg[x]);
    x = -1;
    while (++x < data->win_w)
        pthread_join(threads_id[x], NULL);

    ft_get_speed(data);
    pthread_mutex_destroy(&data->lock);
}
 */