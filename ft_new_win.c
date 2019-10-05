/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_new_win.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drafe <drafe@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/25 17:32:09 by drafe             #+#    #+#             */
/*   Updated: 2019/10/05 22:16:07 by drafe            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

/*
** **************************************************************************
**	void ft_w_layout(t_w *w)
**	Function to set standart params
** **************************************************************************
*/

void		ft_w_layout(t_w *w)
{
	printf("\n-------w_layout start-------\n");
	w->lsd = 0;
	w->b_clr = 0X000000;//0XFFFFFF;
	w->g_clr = 0X000000;//0XFFFFFF;
	w->r_clr = 0X000000;//0XFFFFFF;
	w->max_i = 50;
	w->zm = 1;
	w->mv_y = 0;
	w->threads = 16;
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
		w->zm = 1;
		w->b_clr = 2147483647 / 7;
		w->g_clr = 2147483647 / 7;
		w->r_clr = 2147483647 / 7;
		w->mv_x = -0.5;
		w->mv_y = 0;
		w->j_cre = 1;
		w->j_cim = 0.1;
		w->c = 10;
	}/**/
	if (w->f_type == 5)
	{
		w->mv_x = -0.5;
		w->mv_y = -0.5;
	}
	if (w->f_type == 3)
	{
		w->max_i = 10;
		w->lsd = 1;
		w->b_clr = 0XFFFFFF;
		w->g_clr = 0XFFFFFF;
		w->r_clr = 0XFFFFFF;
		//w->mv_y = 0;
	}
	if (w->f_type == 6)
	{
		w->mv_x = 0;
		w->j_cre = 0.102;
		w->j_cim = -0.04;
	}

	printf("-------w_layout end-------\n");
}

/*
** **************************************************************************
**	int fdf_new_win(t_w *w, int p_nb, char *source_f)
**	Function to initialize window and image in struct t_w w
** **************************************************************************
*/

void			ft_new_win(t_w *w)
{
	printf("\n-------new_win start-------\n");
	ft_w_layout(w);
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
	printf("-------new_win end-------\n");
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
