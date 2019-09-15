/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_mandelbrot.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drafe <drafe@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/25 17:32:09 by drafe             #+#    #+#             */
/*   Updated: 2019/09/15 20:41:24 by drafe            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void			ft_mandelbrot(t_pxl *pxl)
{
	int			i;
	double		re;
	double		im;
	double		x;
	double		y;

	i = 0;
	x = 0.0;
	y = 0.0;
	//printf("\n-------ft_mandelbrot start-px1=%d py1=%d-\n", pxl->px, pxl->py);
	ft_crds_scale(pxl->w, pxl->px, pxl->py);
	while ((x*x + y*y <= 2*2)  &&  (i < pxl->w->max_i))
	{
		re = x;
		im = y;
		x = (re * re) - (im * im) + pxl->w->x_scl;
 		y = (2 * re * im) + pxl->w->y_scl;
		i++;
	}
	ft_color_iter(i, pxl->w->max_i);
	ft_img_pxl_put(pxl->w, pxl->px, pxl->py, i);
	//printf("\n-------ft_mandelbrot end-------\n");
}
