/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_include.h                                     .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: gruocco <marvin@le-101.fr>                 +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/10/23 12:59:51 by gruocco      #+#   ##    ##    #+#       */
/*   Updated: 2018/10/23 12:59:57 by gruocco     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#ifndef FT_INCLUDE_H
# define FT_INCLUDE_H
# include <fcntl.h>
# include <unistd.h>
# include <stdlib.h>
# include "minilibx_macos/mlx.h"
# include "libft/libft.h"
# include <math.h>
# include <pthread.h>

/*
 ** todo remove
 */
# include <stdio.h>

# include "ft_bmp.h"

/*
 ** todo ?
 ** #include <string>#include <vector.>#include <iostream>#include "quickcg.h"
*/

# define text_w 	600
# define text_h 	600
# define win_h 	1400
# define win_w 	2000
# define mult 	4

typedef struct	s_img
{
    void		*img_ptr;
    int			*data;
    int			size_l;
    int			bpp;
    int			endian;
}				t_img;


/*
 ** 2D
 ** rgb[2] draw_start draw_end
*/

/*
 ** TEXTURE
 ** tex_x tex_y text_n
*/

/*
 ** MAP
 ** *map rows cols point color
*/


typedef struct	s_data
{
	
    void		*ptr;
    void		*win;
    t_img		img;
	
	int         rgb [2];
    int         draw_start;
    int         draw_end;
	
	int 		tex_x;
	int 		tex_y;
	int 		text_n;
	int         **text;
    
    int         *map;
    int	        rows;
    int	        cols;

    int         point;
    int         color;
    /*
     ** RAY
    */
    /*
     ** the time difference between the 2 can determinate how much you should move (to move a constant speed no matter
     ** how long the calculation of the frames takes), and for the FPS counter
    */
    double 		time;                   /**     time of the current frame       */
    double 		oldTime;                /**     time of the previous frame      */
    /*
     ** The speed modifiers use frameTime, and a constant value, to determinate the speed of the moving and rotating
    */
    double 		speed;                   /** the constant value is in squares/second */
    double 		rotSpeed;                /** the constant value is in radians/second */
    double 		frameTime;               /** frameTime is the time this frame has taken, in seconds */

    /*
     ** PLAYER
    */
    /*
     ** player's position vector
    */
    double 		pos_x;
    double		pos_y;
    /*
     ** player's direction
    */
    double 		dir_x;
    double 		dir_y;
    /*
     ** player's camera plane
    */
    double 		planeX;
    double 		planeY;
    /*
     ** the x-coord on camera plane represented by the current x-coord of the screen
    */
    double 		camera_x;
    /*
     ** ray direction
    */
    double 		raydir_x;
    double 		raydir_y;
    /*
     ** mapX and mapY represent the current square of the map the ray is in
    */
    int 		mapX;
    int 		mapY;
    /*
     ** if an x-side was hit, side is set to 0, if an y-side was hit, side will be 1
    */
    int 		side;
    /*	
     ** the distance the ray has to travel between x-sides or y-sides
    */
    double 		delta_dist_x;
    double 		delta_dist_y;
    /*
     ** will calculate the length of the ray
    */
    double 		wall_dist;
    /*
     ** The DDA will always jump 1 square each loop, either in the x-direction or in the y-direction.
     ** This fact will be stored in step_x and step_y: those are always either -1 or +1.
    */
    int 		step_x;
    int 		step_y;
    /*
     ** initial distance the ray has to travel from its start position to the first x-side and the first y-side.
     ** Later the length of ray from current position to next x or y-side
    */
    double 		side_dist_x;
    double 		side_dist_y;
    /*
     ** determinate whether or not the next loop may be ended: was there a wall hit?
    */
    int 		hit;
    /*
     ** the height of the line that has to be drawn on screen
    */
    int 		line_h;
	/*
	** where exactly the wall was hit
	*/
	double 		wall_x;
    /*
     ** FLOOR & CEILING
    */
	/*
	 ** x, y position of the floor texel at the bottom of the wall
	*/
	int 		floor_tex_x;
	int			floor_tex_y;
    double 		floor_x_wall;
    double 		floor_y_wall;
    double 		dist_wall;
    double 		dist_player;
    double 		current_dist;
	double 		weight;
	double 		current_floor_x;
	double 		current_floor_y;
	/*
	 ** MOVEMENT
	*/
	double 		sin_speed;
	/*
	** UTILITY
	*/
	int 		flag;
	int 		i;
	int 		j;

}				t_data;

/*
 ** CHECKS
*/
int				ft_checks(t_data *data, int ac, char **av, int fd);
/*
 ** MAP
*/
void			ft_array_filler(int fd, t_data *data);
void			ft_map_reader(t_data *data, char **av);
void			ft_texture_maker(t_data *data);
/*
 ** DRAW
*/
void			ft_redraw(t_data *data);
void			ft_raycaster(t_data *data);
int				ft_draw(t_data *data);
void			ft_instructions(t_data *data);
void			ft_floor_ceiling(t_data *data, int x);
void			ft_get_speed(t_data *data);
/*
 ** KEYS
*/
int				ft_x_close(t_data *data);
int				ft_key_press(int keycode, t_data *data);
int				ft_key_release(int keycode, t_data *data);
int				ft_keys(int keycode, t_data *data);

int				ft_check_front(t_data *data, int *map);
int				ft_check_back(t_data *data, int *map);
int				ft_check_left(t_data *data, int *map);
int				ft_check_right(t_data *data, int *map);
/*
 ** STUFF
*/
void			print_stuff (t_data *data);
void			ft_2d_map_print(t_data *data);
#endif
