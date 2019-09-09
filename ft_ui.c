/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ui.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drafe <drafe@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/25 17:32:09 by drafe             #+#    #+#             */
/*   Updated: 2019/09/09 21:24:28 by drafe            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

/*
** **************************************************************************
**	int ft_zoom(int x, int y)
**	Function to  mouse input
** **************************************************************************
*/
static void		ft_zoom(t_w *w, int *x, int *y)
{
	int			a;
	int			b;
	
	a = w->height / 2;
	b = w->width / 2;
	w->mv_x = a - *x;
	w->mv_y = b - *y;
}


/*
** **************************************************************************
**	int ft_ui_mouse(int key, int x, int y, void *param)
**	Function to handle mouse input
** **************************************************************************
*/

int			ft_ui_mouse(int key, int x, int y, void *param)
{
	t_w		*new_w;

	new_w = (t_w*)param;
	printf("\nkey=%d, x=%d, y=%d\n", key, x, y);
	ft_putnbr(key);
	if ((key == 5) || (key == 4))
	{
		ft_putstr("\nZooming...");
		if (key == 5)
			new_w->zm += 1;
		else
			new_w->zm -= 1;
		ft_draw(new_w);
		printf("%fdone!", new_w->zm);
	}
	if (key == 99)
		ft_zoom(new_w, &x, &y);

	return ((int)param);
}

/*
** **************************************************************************
**	int ft_ui_keys(int key, void *param)
**	Function to handle key_input
** **************************************************************************
*/

int		ft_ui_keys(int key, void *param)
{
	t_w		*new_w;

	new_w = (t_w*)param;
	ft_putnbr(key);
	if (key == 49)
	{
		ft_init_arr_fractols(new_w);
		ft_draw(new_w);
	}

	if (key == 53)
		exit(0);
	return ((int)param);
}

	/*if (key == 123)
	{
		new_w->mv_x -= new_w->zm / 10;
		ft_putnbr(new_w->zm);
		ft_draw(new_w);
	}
	if (key == 124)
	{
		new_w->mv_x += new_w->zm / 10;//0.1;
		ft_draw(new_w);
	}
	if (key == 125)
	{
		new_w->mv_y += new_w->zm / 10;//0.1;
		ft_draw(new_w);
	}
	if (key == 126)
	{
		new_w->mv_y -= new_w->zm / 10;//0.1;
		ft_draw(new_w);
	}*/
	
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
