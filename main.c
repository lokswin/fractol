/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drafe <drafe@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/25 17:32:09 by drafe             #+#    #+#             */
/*   Updated: 2019/09/06 19:58:33 by drafe            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void	pxl_analize()
For each pixel (Px, Py) on the screen, do:
{
  x0 = scaled x coordinate of pixel (scaled to lie in the Mandelbrot X scale (-2.5, 1))
  y0 = scaled y coordinate of pixel (scaled to lie in the Mandelbrot Y scale (-1, 1))
  x = 0.0
  y = 0.0
  iteration = 0
  max_iteration = 1000
  while (x*x + y*y <= 2*2  AND  iteration < max_iteration) {
    xtemp = x*x - y*y + x0
    y = 2*x*y + y0
    x = xtemp
    iteration = iteration + 1
  }
  color = palette[iteration]
  plot(Px, Py, color)
}

/*
** **************************************************************************
**	int main(int argc, char **argv)
**	function to get user map
** **************************************************************************
*/

int				main(int argc, char **argv)
{
	int			i;

	i = 0;
	if (argc != 1 || (argv[1] != NULL))
	{
		ft_putstr("usage: ./fractol\n");
		exit(1);
	}
	while
	printf("start");
	exit(0);
}
