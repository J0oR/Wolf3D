/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   bmp.h                                            .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: gruocco <marvin@le-101.fr>                 +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/11/05 11:12:44 by gruocco      #+#   ##    ##    #+#       */
/*   Updated: 2018/11/05 11:12:50 by gruocco     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#ifndef FT_BMP_H
# define FT_BMP_H
# include <stdint.h>

/*
 ** BMP-related data types based on Microsoft's own.
*/

/*
 ** Adapted from https://msdn.microsoft.com/en-us/library/cc230309.aspx.
 ** See http://en.wikipedia.org/wiki/Stdint.h for more on stdint.h.
*/

typedef	uint8_t		t_byte;
typedef	uint32_t	t_dword;
typedef	int32_t		t_long;
typedef	uint16_t	t_word;

/*
 ** BITMAPFILEHEADER : contains info about type, size and layout of a file that
 ** contains a DIB [device-independent bitmap].
*/

/*
 ** https://msdn.microsoft.com/en-us/library/dd183374(v=vs.85).aspx.
*/

typedef	struct	s_bmpfileheader
{
	t_word	bf_type;
	t_dword	bf_size;
	t_word	bf_reserved1;
	t_word	bf_reserved2;
	t_dword	bf_off_bits;
}				t_bmpfileheader;

/*
 ** BITMAPINFOHEADER: contains info about dimensions and color format of a
 ** DIB [device-independent bitmap].
*/

/*
 ** https://msdn.microsoft.com/en-us/library/dd183376(v=vs.85).aspx.
*/

typedef struct	s_bmpinfoheader
{
	t_dword	bi_size;
	t_long	bi_width;
	t_long	bi_height;
	t_word	bi_planes;
	t_word	bi_bit_count;
	t_dword	bi_compression;
	t_dword	bi_size_image;
	t_long	bi_xpels_per_meter;
	t_long	bi_ypels_per_meter;
	t_dword	bi_clr_used;
	t_dword	bi_clr_important;
}				t_bmpinfoheader;

/*
 ** RGBTRIPLE
 ** https://msdn.microsoft.com/en-us/library/dd162939(v=vs.85).aspx.
*/

typedef struct	s_rgbtriple
{
	t_byte rgbt_blue;
	t_byte rgbt_green;
	t_byte rgbt_red;
}				t_rgbtriple;

#endif
