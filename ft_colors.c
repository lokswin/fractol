/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_colors.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drafe <drafe@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/11 19:09:08 by drafe             #+#    #+#             */
/*   Updated: 2019/10/04 19:26:30 by drafe            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

/*
** **************************************************************************
**	void ft_img_pxl_put(t_w *w, int px, int py)
**	Function to place one pixel into memory
** **************************************************************************
*/

void			ft_img_pxl_put(t_w *w, int x, int y, int i)
{
	int			j;
	double		t;
	int			tmp1;
	int			col;

	//printf("\n-------ft_img_pxl_put start---x=%d y=%d \n", x, y);
	t = (double)i / (double)w->max_i;
	j = (x * (w->bitspp / 8)) + (y * w->ln_sz);
	tmp1 = (int)((w->b_clr) * (1 - t) * pow(t, 3) * 255);
	if (w->lsd == 1)
	{
		w->img[j] = (int)((w->b_clr + 9) * (1 - t) * pow(t, 3) * 255);
		w->img[++j] = (int)((w->g_clr + 15) * pow((1 - t), 2) * pow(t, 2) * 255) >> 8;
		w->img[++j] = (int)((w->r_clr + 8.5) * pow((1 - t), 3) * t * 255) >> 16;
		w->img[++j] = 0;
	}
	else 
	{
		if (i < w->max_i)
			col = 0XFFFFFF;
		else
			col = 0X000000;
		w->img[j] = col;
		w->img[++j] = (w->g_clr + col) >> 8;
		w->img[++j] = (w->r_clr + col) >> 16;
		w->img[++j] = 0;
	}
	//printf("\n-------ft_img_pxl_put end-------\n");
}

/*
** **************************************************************************
**	void ft_change_color(t_w *w, int key)
**	Function to change color
** **************************************************************************
*/

void		ft_change_color(t_w *w, int key)
{
	if (key == R_KEY)
		w->r_clr += INT32_MAX / 20;
	if (key == G_KEY)
		w->g_clr += INT32_MAX / 20;
	if (key == B_KEY)
		w->b_clr += INT32_MAX / 20;
	if (key == C_KEY)
		w->lsd = 1;
	ft_draw(w);
}

/*
** **************************************************************************
**	void ft_putman(void)
**	Function for print man
** **************************************************************************
*/

void		ft_putman(void)
{
	ft_putstr("usage: ./fractol [fractol number]\n\n\
	0 - Mandelbrot set;\n\
	1 - Julia set;\n\
	2 - Koch snowflake;\n\
	3 - Sierpinski carpet;\n\
	4 - Attractor;\n\
	5 - Burning ship;\n\
	\n");
}

/*
** **************************************************************************
**	void ft_draw_iter(t_w *w)
**	Function for draw iter zoom and threads
** **************************************************************************
*/

void			ft_draw_iter(t_w *w)
{
	char		*out_str;

	if (((int)w->zm < INT32_MAX) || ((int)w->zm < INT32_MIN))
	{
		out_str = ft_strjoin("zoom = ", ft_itoa((int)w->zm));
		out_str = ft_strjoin(out_str, " iter = ");
		out_str = ft_strjoin(out_str, ft_itoa((int)w->max_i));
		mlx_string_put(w->mlx_p, w->win_p, 5, W_HEIGHT - 20, 0x9C4CC4, out_str);
		ft_strdel(&out_str);
	}
}
