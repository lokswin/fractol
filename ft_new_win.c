/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_new_win.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drafe <drafe@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/25 17:32:09 by drafe             #+#    #+#             */
/*   Updated: 2019/09/11 21:12:27 by drafe            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

static void		ft_w_layout(t_w *w)
{
	printf("\n-------w_layout start-------\n");
	w->width = 1350;
	w->height = 1350;
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
	w->max_i = 50;
	ft_w_layout(w);
	if (!(w->mlx_p = mlx_init()))
	{
		ft_putstr_fd("mlx error", 2);
		exit (1);
	}
	w->img_p = mlx_new_image(w->mlx_p, w->width, w->height);
	//w->color = mlx_get_color_value(w->mlx_p, 0xFFFFFF);
	ft_ui(w);
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
