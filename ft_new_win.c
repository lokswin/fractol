/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_new_win.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drafe <drafe@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/25 17:32:09 by drafe             #+#    #+#             */
/*   Updated: 2019/10/10 22:16:48 by drafe            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

/*
** **************************************************************************
**	static void ft_w_layout_p1(t_w *w)
**	Function to set standart params
** **************************************************************************
*/

static void		ft_w_layout_p1(t_w *w)
{
	w->lsd = 1;
	w->b_clr = 0XFFFFFF;
	w->g_clr = 0XFFFFFF;
	w->r_clr = 0XFFFFFF;
	if (w->f_type == 3)
	{
		w->max_i = 200;
		w->zm = 0.000368;
		w->mv_x = 9000000000;
		w->mv_y = 9000000000;
	}
	if (w->f_type == 4)
	{
		w->max_i = 50;
		w->zm = 0.5;
		w->mv_x = 0.9;
		w->mv_y = 0;
	}
	if (w->f_type == 6)
	{
		w->mv_x = 0;
		w->j_cre = 0.102;
		w->j_cim = -0.04;
	}
	if (w->f_type == 7)
	{
		w->zm = 2;
		w->max_i = 30;
		w->j_cre = -1.25;
		w->j_cim = 1.5;
		w->cycle = 1;
	}
}

/*
** **************************************************************************
**	void ft_w_layout(t_w *w)
**	Function to set standart params
** **************************************************************************
*/

void			ft_w_layout(t_w *w)
{
	w->lsd = 0;
	w->b_clr = 0X000000;
	w->g_clr = 0X000000;
	w->r_clr = 0X000000;
	w->max_i = 50;
	w->zm = 1;
	w->mv_y = 0;
	w->mv_x = 0;
	if (w->f_type > 2)
		ft_w_layout_p1(w);
	if (w->f_type == 0)
		w->mv_x = -0.5;
	if (w->f_type == 1)
	{
		w->mv_x = 0;
		w->j_cre = -0.7;
		w->j_cim = 0.27015;
	}
	if (w->f_type == 2)
	{
		w->lsd = 1;
		w->zm = 0.8;
		w->j_cre = -1.2;
		w->j_cim = -0.6;
	}
	if (w->f_type == 5)
	{
		w->mv_x = -0.5;
		w->mv_y = -0.5;
	}
}

/*
** **************************************************************************
**	void ft_new_win(t_w *w)
**	Function to initialize window and image in struct t_w w
** **************************************************************************
*/

void			ft_new_win(t_w *w)
{
	ft_w_layout(w);
	w->threads = 16;
	if (!(w->mlx_p = mlx_init()))
	{
		ft_putstr_fd("mlx_init error", 2);
		exit (1);
	}
	w->img_p = mlx_new_image(w->mlx_p, W_WIDTH, W_HEIGHT);
	w->win_p = mlx_new_window(w->mlx_p, W_WIDTH, W_HEIGHT, "Fractol");
	ft_ui();
	if (!w->mlx_p || !w->win_p || !w->img_p)
	{
		ft_putstr_fd("mlx error", 2);
		exit(1);
	}
	w->img = mlx_get_data_addr(w->img_p, \
	&w->bitspp, &w->ln_sz, &w->endi);
}
