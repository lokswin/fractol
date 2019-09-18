/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_julia.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drafe <drafe@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/25 17:32:09 by drafe             #+#    #+#             */
/*   Updated: 2019/09/18 20:49:01 by drafe            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

/*
** **************************************************************************
**	int static void pxl_analyze(t_w *w, int px, int py)
**	Function to draw Julia set
** **************************************************************************
*/

void		ft_julia(t_w *w, int px, int py)
{
	int			i;
	double		re;
	double		im;
	double		x;
	double		y;

	i = 0;
	//printf("\n-------ft_mandelbrot start-px1=%d py1=%d-\n", w->px, w->py);
	ft_crds_scale(w, px, py);
	x = w->x_scl;
	y = w->y_scl;
	while ((x*x + y*y <= 2*2)  &&  (i < w->max_i))
	{
		re = x;
		im = y;
		x = (re * re) - (im * im) + w->j_cRe;
 		y = (2 * re * im) + w->j_cIm;
		i++;
	}
	ft_img_pxl_put(w, px, py, i);
	//printf("\n-------ft_pxl_analyze end-------\n");
}
