/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ui.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drafe <drafe@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/25 17:32:09 by drafe             #+#    #+#             */
/*   Updated: 2019/09/07 21:31:11 by drafe            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

/*
** **************************************************************************
**	void ft_ui(t_w *new_w)
**	Function to create win_p
** **************************************************************************
*/

int		ft_ui_keys(int key, void *param)
{
	t_w		*new_w;
	int		zm;

	new_w = (t_w *)param;
	zm = new_w->fractols[new_w->f_type][0];
	ft_putnbr(key);
	if (key == 18)
	{
		new_w->fractols[new_w->f_type][0] += 1;
		ft_draw(new_w);
	}
	if (key == 19)
	{
		new_w->fractols[new_w->f_type][0] -= 1;
		ft_draw(new_w);
	}
	if (key == 49)
	{
		ft_init_arr_fractols(new_w);
		ft_draw(new_w);
	}
	if (key == 123)
	{
		new_w->fractols[new_w->f_type][1] -= 0.1;
		ft_draw(new_w);
	}
	if (key == 124)
	{
		new_w->fractols[new_w->f_type][1] += 0.1;
		ft_draw(new_w);
	}
	if (key == 125)
	{
		new_w->fractols[new_w->f_type][2] += 0.1;
		ft_draw(new_w);
	}
	if (key == 126)
	{
		new_w->fractols[new_w->f_type][2] -= 0.1;
		ft_draw(new_w);
	}
	if (key == 53)
		exit(0);
	return ((int)param);
}

/*
** **************************************************************************
**	void ft_ui(t_w *new_w)
**	Function to create win_p
** **************************************************************************
*/

void		ft_ui(t_w *new_w)
{
	printf("\n-------ft_ui start-------\n");
	new_w->win_p = mlx_new_window(new_w->mlx_p, new_w->width, new_w->height, "Fractol");
	ft_putstr("Fractol man:\n\
	ESC : quit Fractol");
	printf("-------ft_ui end-------\n");
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
