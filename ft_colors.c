/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_colors.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drafe <drafe@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/11 19:09:08 by drafe             #+#    #+#             */
/*   Updated: 2019/09/11 21:21:10 by drafe            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

/*
** **************************************************************************
**	int ft_color_iter(t_w *w, int px, int py)
**	Function to set black or white
** **************************************************************************
*/

int		ft_color_iter(int i, int i_max)
{
	int			color;
	int			red;
	int			green;
	int			blue;
	double		t;
	
	//printf("\n-------ft_color_iter start-------\n");
	color = 0x000000;
	t = (double)i / (double)i_max;
	red = (int)(9 * (1 - t) * pow(t, 3) * 255);
	green = (int)(15 * pow((1 - t), 2) * pow(t, 2) * 255);
	blue = (int)(8.5 * pow((1 - t), 3) * t * 255);
	//printf("r%d,g%d,b%d",red, green, blue);
	return(color);
	if (i < i_max)
		return(0x000000);
	else
		return(0xFFFFFF);
	color = 0;
	//(i % 256, 255, 255 * (i < i_max)));
	//return(color);
	//printf("\n-------ft_color_iter end-------\n");
}

/*
** **************************************************************************
**	void ft_img_pxl_put(t_w *w, int px, int py)
**	Function to place one pixel into memory
** **************************************************************************
*/

void		ft_img_pxl_put(t_w *w, int x, int y, int i)
{
	int			j;
	double		t;

	//printf("\n-------ft_img_pxl_put start-------\n");
	//printf("x=%d, y=%d, bitspp=%d, ln_sz=%d\n", x, y, w->bitspp, w->ln_sz);
	t = (double)i / (double)w->max_i;
	j = (x * (w->bitspp / 8)) + (y * w->ln_sz);
	w->img[j] = (int)((w->b_clr + 9) * (1 - t) * pow(t, 3) * 255);//Blue
	w->img[++j] = (int)((w->g_clr + 15) * pow((1 - t), 2) * pow(t, 2) * 255) >> 8;//Green
	w->img[++j] = (int)((w->r_clr + 8.5) * pow((1 - t), 3) * t * 255) >> 16;//Red
	w->img[++j] = 0;
	//printf("\n-------ft_img_pxl_put end-------\n");
}

/*
** **************************************************************************
**	void ft_draw_man(t_w *w)
**	Function for draw man
** **************************************************************************
*/

void		ft_draw_man(t_w *w)
{
	char		*out_str;

	if (((int)w->zm < 2147483647) || ((int)w->zm < -2147483647))
	{
		out_str = ft_strjoin("zoom = ", ft_itoa((int)w->zm));
		out_str = ft_strjoin(out_str, " iter = ");
		out_str = ft_strjoin(out_str, ft_itoa((int)w->max_i));
		mlx_string_put(w->mlx_p, w->win_p, 5, w->height - 20, 0xFFFFFF, out_str);
		ft_strdel(&out_str);
	}

}



/*
** **************************************************************************
**	man /usr/share/man/man3/mlx.1
**	man /usr/share/man/man3/mlx_loop.1
**	man /usr/share/man/man3/mlx_new_image.1
**	man /usr/share/man/man3/mlx_new_window.1
**	man /usr/share/man/man3/mlx_pixel_put.1
** **************************************************************************
*/
