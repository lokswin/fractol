/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new_win.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drafe <drafe@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/25 17:32:09 by drafe             #+#    #+#             */
/*   Updated: 2019/09/06 20:57:08 by drafe            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

static void		w_layout(t_w *new_w)
{
	int			w;
	int			h;
	int			max;

	printf("\n-------w_layout start-------\n");
	new_w->width = 2500;
	new_w->height = 1300;
	printf("-------w_layout end-------\n");
}

/*
** **************************************************************************
**	int fdf_new_win(t_w *new_w, int p_nb, char *source_f)
**	Function to initialize window and image in struct t_w new_w
** **************************************************************************
*/

void		new_win(t_w *new_w)
{
	printf("\n-------new_win start-------\n");
	new_w->iso_p = 0;
	new_w->angle = 0.46373398;//0.523599;
	fdf_w_layout(new_w);
	if (!(new_w->mlx_p = mlx_init()))
	{
		ft_putstr_fd("mlx error", 2);
		exit (1);
	}
	new_w->img_p = mlx_new_image(new_w->mlx_p, new_w->width, new_w->height);
	new_w->color = mlx_get_color_value(new_w->mlx_p, 0xFFFFFF);
	new_w->win_p = fdf_ui(new_w, 1);
	if (!new_w->mlx_p || !new_w->win_p || !new_w->img_p)
	{
		ft_putstr_fd("mlx error", 2);
		exit(1);
	}
	new_w->img = mlx_get_data_addr(new_w->img_p, \
	&new_w->bitspp, &new_w->ln_sz, &new_w->endi);
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
