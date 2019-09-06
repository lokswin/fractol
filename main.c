/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drafe <drafe@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/25 17:32:09 by drafe             #+#    #+#             */
/*   Updated: 2019/09/06 21:28:06 by drafe            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

/*
** **************************************************************************
**	int static void ft_crds_scale(t_w *new_w, int px, int py)
**	Function to get
**	x0 = scaled x coord of pxl(scaled to lie in the Manbrt X scale(-2.5, 1));
**	y0 = scaled y coord of pxl(scaled to lie in the Manbrt Y scale(-1, 1));
** **************************************************************************
*/

static void ft_crds_scale(t_w *new_w, int px, int py)
{

}

/*
** **************************************************************************
**	int static void ft_pxl_analize(t_w *new_w, int px, int py)
**	Function to place one pixel into memory
** **************************************************************************
*/

static void		ft_img_pxl_put(t_w *new_w, int x, int y)
{
	int			i;

	printf("\n-------img_pxl_put start-------\n");
	printf("x=%d, y=%d, bitspp=%d, ln_sz=%d\n", x, y, new_w->bitspp, new_w->ln_sz);
	i = (x * (new_w->bitspp / 8)) + (y * new_w->ln_sz);
	new_w->img[i] = new_w->color; // B — Blue
	new_w->img[++i] = new_w->color >> 8; // G — Green
	new_w->img[++i] = new_w->color >> 16; // R — Red
	new_w->img[++i] = 0;
	printf("\n-------img_pxl_put end-------\n");
}

/*
** **************************************************************************
**	int static void pxl_analyze(t_w *new_w, int px, int py)
**	Function to analyze one pixel
** **************************************************************************
*/

static void		ft_pxl_analyze(t_w *new_w, int px, int py)
{
	int			i;
	int			max_i;
	int			x_tmp;
	int			x0;
	int			y0;
	int			x;
	int			y;

	printf("\n-------pxl_analize start-px=%d py=%d-\n", px, py);
	i = 0;
	max_i = 50;
	ft_crds_scale(&new_w, px, py);
	x0 = new_w->x_scale;
	y0 = new_w->y_scale;
	x = 0.0;
	y = 0.0;
	while ((x*x + y*y <= 2*2)  &&  (i < max_i))
	{
		x_tmp = x * x - y * y + x0;
		y = 2 * x * y + y0;
		x = x_tmp;
 		i++;
	}
	new_w->color = 0xFFFFFF;
	ft_img_pxl_put(&new_w, px, py);
	printf("\n-------pxl_analize end-------\n");
}

/*
** **************************************************************************
**	int main(int argc, char **argv)
**	function to get user map
** **************************************************************************
*/

int				main(int argc, char **argv)
{
	t_w			new_w;
	int			i;
	int			j;

	i = 0;
	if ((argc != 1) || (argv[1] != NULL))
	{
		ft_putstr("usage: ./fractol\n");
		exit(1);
	}
	fdf_new_win(&new_w);
	while (i < new_w.width)
	{
		j = 0;
		while (j < new_w.height)
		{
			ft_pxl_analyze(&new_w, i, j);
			j++;
		}
		i++;
	}
	printf("start");
	exit(0);
}
