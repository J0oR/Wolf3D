/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_texture.c                                     .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: gruocco <marvin@le-101.fr>                 +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/11/05 13:26:13 by gruocco      #+#   ##    ##    #+#       */
/*   Updated: 2018/11/05 13:26:15 by gruocco     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "ft_include.h"

void	ft_load_bmp_file(char *filename, int *text)
{
	int 	i;
	int 	j;
	FILE *inptr = fopen(filename, "r"); /** // open input file */
	/*if (inptr == NULL)
	{
		ft_putstr("Could not open ");
		ft_putstr(filename);
		return;
	}*/
	t_bmpfileheader bf;
	fread(&bf, sizeof(t_bmpfileheader), 1, inptr); /** read infile's BITMAPFILEHEADER */
	t_bmpinfoheader bi;
	fread(&bi, sizeof(t_bmpinfoheader), 1, inptr); /** // read infile's BITMAPINFOHEADER */
	/* // ensure infile is (likely) a 24-bit uncompressed BMP 4.0
	 * if (bf.bfType != 0x4d42 || bf.bfOffBits != 54 || bi.biSize != 40 ||
		bi.biBitCount != 24 || bi.biCompression != 0)
	{

		fclose(inptr);
		fprintf(stderr, "Unsupported file format.\n");
		return;
	}*/
	int padding = (4 - (bi.bi_width * sizeof(t_rgbtriple)) % 4) % 4; /** // determine padding for scanlines */
	/*
	 * //printf("w = %i, h = %i \n", bi.biWidth, bi.biHeight);
	// iterate over infile's scanlines
	 * for (int i = 0, biHeight = abs(bi.biHeight); i < biHeight; i++)
	 * */
	i = -1;
	while (++i < text_h)
	{
		j = -1;
		// iterate over pixels in scanline
		while (++j < text_w)
		{
			int triple; /** temporary storage */
			fread(&triple, sizeof(t_rgbtriple), 1, inptr); /** // read RGB triple from infile */
			text[j + i * text_w] = triple;
		}
		fseek(inptr, padding, SEEK_CUR); /** // skip over padding, if any */
		/*
		 * // then add it back (to demonstrate how)
		 * for (int k = 0; k < padding; k++)
		{
			fputc(0x00, outptr);
		}*/
	}
	fclose(inptr); /** close infile */
}

void 	ft_texture_maker(t_data *data)
{
	int x;

	data->text = (int **) ft_memalloc(sizeof(int *) * 6);
	x = -1;
	while (++x < 6)
		data->text[x] = (int *) ft_memalloc(sizeof(int) * text_w * text_h);
	ft_load_bmp_file("./bmp/wall1.bmp", data->text[0]);
	ft_load_bmp_file("./bmp/wall3.bmp", data->text[1]);
	ft_load_bmp_file("./bmp/wall2.bmp", data->text[2]);
	ft_load_bmp_file("./bmp/wall4.bmp", data->text[3]);
	ft_load_bmp_file("./bmp/floor.bmp", data->text[4]);
	ft_load_bmp_file("./bmp/wall2.bmp", data->text[5]);
}
