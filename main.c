/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drafe <drafe@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/25 17:32:09 by drafe             #+#    #+#             */
/*   Updated: 2019/10/16 20:05:25 by drafe            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

/*
** **************************************************************************
**	static void ft_main_err(void)
**	Function to print usage
** **************************************************************************
*/

static void		ft_main_err(void)
{
	ft_putman();
	exit(1);
}

/*
** **************************************************************************
**	static void ft_win_start(t_w *w)
**	Function for handle windows
** **************************************************************************
*/

static void		ft_win_start(t_w *w)
{
	ft_new_win(w);
	ft_draw(w);
	mlx_hook(w->win_p, 3, 1L << 1, ft_keyrelease, (void*)w);
	mlx_hook(w->win_p, 2, 1L << 0, ft_ui_keys, (void*)w);
	mlx_mouse_hook(w->win_p, ft_ui_mouse, (void*)w);
	mlx_hook(w->win_p, 6, 1L << 6, ft_mouse_mv, (void*)w);
}

/*
** **************************************************************************
**	int main(int argc, char **argv)
**	Function to get user map
** **************************************************************************
*/

int				main(int argc, char **argv)
{
	t_w			new_w;
	t_w			sec_new_w;

	if ((argc != 2) && (argc != 3))
		ft_main_err();
	if ((new_w.f_type = ft_atoi(argv[1])) > 9)
		ft_main_err();
	if (new_w.f_type < 0)
		ft_main_err();
	if (!(new_w.mlx_p = mlx_init()))
	{
		ft_putstr_fd("mlx_init error", 2);
		exit(1);
	}
	sec_new_w.mlx_p = new_w.mlx_p;
	if ((argc == 3) && ((sec_new_w.f_type = ft_atoi(argv[2])) > 9))
		ft_main_err();
	else if (sec_new_w.f_type < 0)
		ft_main_err();
	else if (argc == 3)
		ft_win_start(&sec_new_w);
	ft_win_start(&new_w);
	ft_ui();
	mlx_loop(new_w.mlx_p);
	exit(0);
}
