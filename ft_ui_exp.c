/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ui_exp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drafe <drafe@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/25 17:32:09 by drafe             #+#    #+#             */
/*   Updated: 2019/10/06 21:00:34 by drafe            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

int			ft_keyrelease(int keycode, t_w *w)
{
	if (keycode == ESC)
	{
		mlx_destroy_image(w->mlx_p, w->img_p);
		mlx_destroy_window(w->mlx_p, w->win_p);
		exit(1);
	}
	if (keycode == KEY_1)
	{
		ft_ui();
		ft_putman();
	}
	return (0);
}
/*
** **************************************************************************
**	void ft_move(t_w *w, int key)
**	Function to move pic with arrows
** **************************************************************************
*/

void		ft_move_shape(t_w *w, int key)
{
	if (key == ARROW_L)
		w->mv_x -= 0.0003 * (1000 / w->zm);
	if (key == ARROW_R)
		w->mv_x += 0.0003 * (1000 / w->zm);
	if (key == ARROW_D)
		w->mv_y += 0.0003 * (1000 / w->zm);
	if (key == ARROW_U)
		w->mv_y -= 0.0003 * (1000 / w->zm);
	ft_draw(w);
}

/*
** **************************************************************************
**	void ft_change_shape(t_w *w, int key)
**	Function to change Julia with keys
** **************************************************************************
*/

void		ft_change_shape(t_w *w, int key)
{
	if ((w->f_type == 1) || (w->f_type == 11))
	{
		
		if (key == NUM_6)
			w->j_cre += 0.0002 * (1000 / w->zm);
		if (key == NUM_4)
			w->j_cre -= 0.0002 * (1000 / w->zm);
		if (key == NUM_2)
			w->j_cim += 0.0002 * (1000 / w->zm);
		if (key == NUM_8)
			w->j_cim -= 0.0002 * (1000 / w->zm);/**/
		ft_draw(w);
	}
	if (w->f_type == 2)
	{
		if (key == NUM_6)
			w->j_cre += 1;
		if (key == NUM_4)
			w->j_cre -= 0.1;
		if (key == NUM_2)
			w->c += 1;
		if (key == NUM_8)
			w->c -= 1;
			//w->j_cim -= 0.1;
		ft_draw(w);
	}
}

int			ft_mouse_mv(int x, int y, void *param)
{
	t_w		*w;

	w = (t_w*)param;
	if (w->f_type == 11)
	{
		if (y > 0)
			w->j_cim += 0.005 / w->zm;
		if (y < 0)
			w->j_cim -= 0.005 / w->zm;
		if (x > 0)
			w->j_cre += 0.005 / w->zm;
		if (x < 0)
			w->j_cre -= 0.005 / w->zm;
		ft_draw(w);
	}
	return (0);
}
