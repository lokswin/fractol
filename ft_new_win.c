/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_new_win.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drafe <drafe@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/25 17:32:09 by drafe             #+#    #+#             */
/*   Updated: 2019/10/15 20:55:01 by drafe            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

/*
** **************************************************************************
**	static void ft_w_layout_exp(t_w *w)
**	Third function to set standart params 6,7,8,9
** **************************************************************************
*/

static char		*ft_w_layout_exp_p2(t_w *w)
{
	if (w->f_type == 6)
	{
		w->mv_x = 0.9;
		return ("Henon");
	}
	if (w->f_type == 7)
	{
		w->mv_x = -0.5;
		w->mv_y = -0.5;
		return ("Burning ship");
	}
	if (w->f_type == 8)
	{
		w->j_cre = 0.102;
		w->j_cim = -0.04;
		return ("Random walk");
	}
	if (w->f_type == 9)
	{
		w->zm = 2;
		w->j_cre = -1.25;
		w->j_cim = 1.5;
		return ("Self call");
	}
	return (" ");
}

/*
** **************************************************************************
**	static void ft_w_layout_exp(t_w *w)
**	Second function to set standart params
** **************************************************************************
*/

static char		*ft_w_layout_exp(t_w *w)
{
	w->mv_x = 0;
	w->cycle = 1;
	if (w->f_type > 5)
		return (ft_w_layout_exp_p2(w));
	if (w->f_type == 4)
	{
		w->max_i = 6;
		w->zm = 0.75;
		w->j_cre = -1.2;
		w->j_cim = -0.6;
		return ("Carpet");
	}
	w->lsd = 1;
	w->b_clr = 0XFFFFFF;
	w->g_clr = 0XFFFFFF;
	w->r_clr = 0XFFFFFF;
	if (w->f_type == 5)
	{
		w->max_i = 30;
		w->zm = 0.0001;
		w->mv_x = 99999999999;
		w->mv_y = 99999999999;
		return ("Sierpinski carpet");
	}
	return (" ");
}

/*
** **************************************************************************
**	void ft_w_layout(t_w *w)
**	First function to set all standart fractol params
** **************************************************************************
*/

char			*ft_w_layout(t_w *w)
{
	w->lsd = 0;
	w->b_clr = 0X000000;
	w->g_clr = 0X000000;
	w->r_clr = 0X000000;
	w->max_i = 50;
	w->zm = 1;
	w->mv_y = 0;
	w->mv_x = -0.5;
	if (w->f_type >= 4)
		return (ft_w_layout_exp(w));
	if (w->f_type == 0)
		return ("Mandelbrot set");
	if (w->f_type == 1)
	{
		w->mv_x = 0;
		w->j_cre = -0.7;
		w->j_cim = 0.27015;
		return ("Julia set");
	}
	if (w->f_type == 2)
		return ("Fish");
	if (w->f_type == 3)
		return ("Tricorn");
	return (" ");
}

/*
** **************************************************************************
**	void ft_new_win(t_w *w)
**	Function to initialize window and image
** **************************************************************************
*/

void			ft_new_win(t_w *w)
{
	char		*head;

	head = ft_strjoin("Fractol - ", ft_w_layout(w));
	w->threads = 16;
	w->mlx_p = mlx_init();
	if (!w->mlx_p)
	{
		ft_putstr_fd("mlx_init error", 2);
		exit(1);
	}
	w->win_p = mlx_new_window(w->mlx_p, W, H, head);
	free(head);
	head = NULL;
	w->img_p = mlx_new_image(w->mlx_p, W, H);
	ft_ui();
	if (!w->mlx_p || !w->win_p || !w->img_p)
	{
		ft_putstr_fd("mlx error", 2);
		exit(1);
	}
	w->img = mlx_get_data_addr(w->img_p, \
	&w->bitspp, &w->ln_sz, &w->endi);
}
