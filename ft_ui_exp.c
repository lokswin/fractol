/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ui_exp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drafe <drafe@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/25 17:32:09 by drafe             #+#    #+#             */
/*   Updated: 2019/10/16 18:20:47 by drafe            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

/*
** **************************************************************************
**	int ft_keyrelease(int key, t_w *w)
**	Function to catch when key release
** **************************************************************************
*/

int				ft_keyrelease(int key, t_w *w)
{
	if (key == ESC)
	{
		mlx_destroy_image(w->mlx_p, w->img_p);
		mlx_destroy_window(w->mlx_p, w->win_p);
		exit(0);
	}
	if (key == KEY_1)
	{
		ft_putman();
		ft_ui();
	}
	return (0);
}

/*
** **************************************************************************
**	void ft_move_sh(t_w *w, int key)
**	Function to move pic with arrows
** **************************************************************************
*/

void			ft_move_sh(t_w *w, int key)
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
**	Function to change with keys part two
** **************************************************************************
*/

static void		ft_change_sh_p2(t_w *w, int key)
{
	if (w->f_type == 9)
	{
		if ((key == P_KEY) && (w->cycle < 100))
			w->cycle += 1;
		if ((key == I_KEY) && (w->cycle > 1))
			w->cycle -= 1;
	}
}

/*
** **************************************************************************
**	void ft_change_sh(t_w *w, int key)
**	Function to change Julia with keys
** **************************************************************************
*/

void			ft_change_sh(t_w *w, int key)
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
			w->j_cim -= 0.0002 * (1000 / w->zm);
	}
	if ((w->f_type == 9) || (w->f_type == 4))
	{
		ft_change_sh_p2(w, key);
		if (key == NUM_6)
			w->j_cre += 0.1;
		if (key == NUM_4)
			w->j_cre -= 0.1;
		if (key == NUM_2)
			w->j_cim += 0.1;
		if (key == NUM_8)
			w->j_cim -= 0.1;
	}
	ft_draw(w);
}

/*
** **************************************************************************
**	int ft_mouse_mv(int x, int y, void *param)
**	Function to catch mouse move
** **************************************************************************
*/

int				ft_mouse_mv(int x, int y, void *param)
{
	t_w			*w;

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
