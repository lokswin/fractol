/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drafe <drafe@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/25 17:32:09 by drafe             #+#    #+#             */
/*   Updated: 2019/09/07 21:24:18 by drafe            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

/*
** **************************************************************************
**	int main(int argc, char **argv)
**	Function to store five types of fractols
**	Mandelbrot, Julia,
**	0 - zoom
**	1 - move_x
**	2 - move_y
** **************************************************************************
*/

void		ft_init_arr_fractols(t_w *new_w)
{
	double	fractols[5][3];
	int		i;
	int		j;

	i = 0;
	fractols[0][0] = 1;
	fractols[0][1] = -0.5;
	fractols[0][2] = 0;
	while (i < 3)
	{
		j = 0;
		while (j < 3)
		{
			new_w->fractols[i][j] = fractols[i][j];
			j++;
		}
		i++;
	}
}

/*
** **************************************************************************
**	int main(int argc, char **argv)
**	Function to get user map
** **************************************************************************
*/

int			main(int argc, char **argv)
{
	t_w		new_w;

	if ((argc != 1) || (argv[1] != NULL))
	{
		ft_putstr("usage: ./fractol\n");
		exit(1);
	}
	ft_new_win(&new_w);
	ft_init_arr_fractols(&new_w);
	mlx_key_hook(new_w.win_p, ft_ui_keys, &new_w);
	mlx_loop(new_w.mlx_p);
	ft_draw(&new_w);
	printf("start");
	exit(0);
}
