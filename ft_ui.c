/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ui.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drafe <drafe@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/25 17:32:09 by drafe             #+#    #+#             */
/*   Updated: 2019/10/16 12:55:29 by drafe            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

/*
** **************************************************************************
**	static void ft_zoom(t_w *w, int *x, int *y)
**	Function to zoom with mouse
** **************************************************************************
*/

static void	ft_zoom(t_w *w, int *x, int *y)
{
	double	offs_x;
	double	offs_y;

	offs_x = 1.5 * (*x - W / 2) / (0.5 * w->zm * W) + w->mv_x;
	offs_y = (*y - H / 2) / (0.5 * w->zm * H) + w->mv_y;
	w->mv_x = offs_x;
	w->mv_y = offs_y;
	w->zm *= pow(1.001, 1000);
}

/*
** **************************************************************************
**	int ft_ui_mouse(int key, int x, int y, void *param)
**	Function to handle mouse coordinates
** **************************************************************************
*/

int			ft_ui_mouse(int key, int x, int y, void *param)
{
	t_w		*w;

	w = (t_w*)param;
	if (w->f_type == 1)
	{
		w->m_x = x;
		w->m_y = y;
	}
	if ((key == 5) || (key == 4))
	{
		if (key == 5)
			ft_zoom(w, &x, &y);
		else
			w->zm /= pow(1.001, 1000);
		ft_draw(w);
	}
	return ((int)param);
}

/*
** **************************************************************************
**	static void ft_ui_keys_exp(t_w *w, int key)
**	Second function to handle key input
** **************************************************************************
*/

static void	ft_ui_keys_exp(t_w *w, int key)
{
	if ((key == MIN_KEY) && ((w->max_i - 2) >= 0))
		w->max_i -= 2;
	if ((key == PL_KEY) && ((w->max_i + 2) < 2000))
		w->max_i += 2;
	if (key == SPACE)
	{
		if (w->f_type == 11)
			w->f_type = 1;
		ft_w_layout(w);
	}
	ft_draw(w);
}

/*
** **************************************************************************
**	int ft_ui_keys(int key, void *param)
**	First function to handle key input
** **************************************************************************
*/

int			ft_ui_keys(int key, void *param)
{
	t_w		*w;

	w = (t_w*)param;
	if ((key == PL_KEY) || (key == MIN_KEY) || (key == SPACE) || (key == O_KEY))
		ft_ui_keys_exp(w, key);
	if ((key == A_KEY) && (w->f_type == 1))
		w->f_type = 11;
	if ((key == S_KEY) && (w->f_type == 11))
		w->f_type = 1;
	if ((key == R_KEY) || (key == G_KEY) || (key == B_KEY) || (key == C_KEY))
		ft_change_color(w, key);
	if ((key == ARROW_U) || (key == ARROW_D) || (key == ARROW_R) \
	|| (key == ARROW_L))
		ft_move_sh(w, key);
	if ((key == NUM_2) || (key == NUM_4) || (key == NUM_6) || (key == NUM_8) \
	|| (key == I_KEY) || (key == P_KEY))
		ft_change_sh(w, key);
	if ((key == A_KEY) && (w->f_type == 1))
		w->f_type = 11;	
	return ((int)param);
}

/*
** **************************************************************************
**	void ft_ui(void)
**	Function to print UI instruction
** **************************************************************************
*/

void		ft_ui(void)
{	
	pid_t	pid;

	pid = getpid();
	ft_putstr("\nFractol man:\n\n\
	ESC : quit\n\
	SPACE - reset to default\n\
	1 - print help\n\
	NUM(+) - add 2 iterations\n\
	NUM(-) - remove 2 iterations\n\
	R - change red color\n\
	G - change green color\n\
	B - change blue color\n\
	C - rainbow\n\
	A - Julia mouse vary ON;\n\
	S - Julia mouse vary OFF;\n\
	NUM2 / NUM8 - Julia, Self call, Carpet vary Y (+ / -)\n\
	NUM6 / NUM4 - Julia, Self call, Carpet vary X (+ / -)\n\
	I - Self call param -;\n\
	P - Self call param +;\n\
	O - redraw;\n\
	pid:");
	ft_putnbr(pid);
	ft_putstr("\n");
}
