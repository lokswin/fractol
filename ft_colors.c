/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_colors.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drafe <drafe@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/11 19:09:08 by drafe             #+#    #+#             */
/*   Updated: 2019/09/21 18:22:23 by drafe            ###   ########.fr       */
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

	//printf("\n-------ft_img_pxl_put start-------\n");
	t = (double)i / (double)w->max_i;
	j = (x * (w->bitspp / 8)) + (y * w->ln_sz);
	tmp1 = (int)((w->b_clr) * (1 - t) * pow(t, 3) * 255);
	if (w->lsd == 1)
	{
		w->img[j] = (int)((w->b_clr + 9) * (1 - t) * pow(t, 3) * 255);//Blue
		w->img[++j] = (int)((w->g_clr + 15) * pow((1 - t), 2) * pow(t, 2) * 255) >> 8;//Green
		w->img[++j] = (int)((w->r_clr + 8.5) * pow((1 - t), 3) * t * 255) >> 16;//Red
		w->img[++j] = 0;
	}
	else
	{
		w->img[j] = (int)(w->b_clr * t);
		w->img[++j] = (int)(w->g_clr * t);
		w->img[++j] = (int)(w->r_clr * t);
		w->img[++j] = 0;
	}
	//printf("\n-------ft_img_pxl_put end-------\n");
}

/*
** **************************************************************************
**	void ft_draw_man(t_w *w)
**	Function for draw man
** **************************************************************************
*/

void			ft_draw_man(t_w *w)
{
	char		*out_str;

	if (((int)w->zm < 2147483647) || ((int)w->zm < -2147483647))
	{
		out_str = ft_strjoin("zoom = ", ft_itoa((int)w->zm));
		out_str = ft_strjoin(out_str, "iter = ");
		out_str = ft_strjoin(out_str, ft_itoa((int)w->max_i));
		out_str = ft_strjoin(out_str, " threads = ");
		out_str = ft_strjoin(out_str, ft_itoa((int)w->w_threads));
		mlx_string_put(w->mlx_p, w->win_p, 5, W_HEIGHT - 20, 0x000000, out_str);
		ft_strdel(&out_str);
	}

}
